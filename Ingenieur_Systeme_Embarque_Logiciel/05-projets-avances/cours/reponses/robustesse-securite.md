# Éléments de réponse – Robustesse et sécurité

Réponses pour les [scénarios Robustesse et sécurité](../scenarios/robustesse-securite.md).

---

## Scénario 1 : Blocage sur une attente

### Analyse

- **Le problème** : Une attente **sans limite de temps** (polling sur un flag, attente d’acquittement I2C, prise de mutex) peut rester **bloquée indéfiniment** si le périphérique ne répond pas (panne, bus coupé, bug). Le thread ou la boucle principale ne progresse plus ; le système peut sembler figé.
- **La conséquence** : Perte de réactivité, watchdog qui déclenche un reset (si configuré), ou blocage total.
- **Le risque** : En contexte critique (commande, sécurité), un blocage peut être inacceptable.

### La solution

Introduire un **timeout** pour toute attente bloquante : attente d’acquittement I2C avec un délai max (ex. timer ou compteur basé sur une horloge), réception UART avec timeout, prise de mutex avec timeout (ex. `xSemaphoreTake(..., timeout_ms)` en FreeRTOS). En cas de **timeout** : log, retour d’erreur à l’appelant, reset partiel (réinit du périphérique) ou global (watchdog), et passage à un état connu (machine à états). Règle : **pas d’attente infinie** ; toujours une issue (timeout + gestion d’erreur).

### Un autre piège : watchdog

Un **watchdog** matériel (timer qui reset le MCU si non « nourri » périodiquement) détecte les boucles infinies et les deadlocks : le logiciel doit appeler régulièrement une fonction de refresh. À combiner avec des timeouts dans le code pour éviter de masquer un bug en « nourrissant » le watchdog alors qu’une partie du système est bloquée.

---

## Scénario 2 : Commande reçue par UART

### Analyse

- **Le problème** : Utiliser **strcpy()** sans limiter la longueur permet un **buffer overflow** si la chaîne reçue est plus longue que le buffer. Un attaquant ou une trame corrompue peut envoyer une longue chaîne et écraser de la mémoire (adresses de retour, variables), ce qui peut mener à prise de contrôle ou crash. De plus, l’absence de **validation** (longueur, caractères, plages de valeurs) peut faire accepter des commandes invalides ou dangereuses.
- **La conséquence** : Comportement imprévisible, crash, ou faille de sécurité.
- **Le risque** : Élevé si l’UART est exposé (interface utilisateur, connexion réseau, mise à jour firmware).

### La solution

- **Limiter les copies** : utiliser **snprintf** / **strncpy** avec une taille max, ou des fonctions « safe » (strlcpy si disponible) pour ne jamais dépasser la taille du buffer. Définir une **longueur max** pour une commande et refuser (ou tronquer) au-delà.
- **Valider les entrées** : vérifier la longueur avant traitement, rejeter les caractères non autorisés, valider les plages de valeurs (ex. param entre 0 et 100). Parser de façon défensive (états d’erreur, retour à un état connu).
- **Machine à états** : pour un protocole plus complexe, utiliser une machine à états explicite avec états d’erreur et réinitialisation.

### Un autre piège : mise à jour firmware

Lors de mises à jour par UART (ou autre), vérifier **signature** ou **checksum** du firmware, séparer zone de boot et zone d’application, et prévoir un **rollback** en cas d’échec pour éviter de bricker le système.

---

**Retour** : [Scénarios – Robustesse et sécurité](../scenarios/robustesse-securite.md) · [5.3 – Sécurité et robustesse](../03-securite-robustesse.md)
