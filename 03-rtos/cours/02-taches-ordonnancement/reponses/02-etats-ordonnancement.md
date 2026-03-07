# Réponse – États et ordonnancement

Voir [scénario](../scenarios/02-etats-ordonnancement.md).

---

## Réponse Scénario 1 : Deux tâches de même priorité

**Priorité égale** : Round-robin (tourniquet) à chaque tick ; les deux doivent s'exécuter. Si une ne « démarre » pas : elle est peut-être **Blocked** (ex. xQueueReceive avec portMAX_DELAY sur une file vide sans envoi).

**Solution** : Vérifier que la tâche n'est pas bloquée sans issue ; utiliser un timeout pour déboguer.

---

## Réponse Scénario 2 : Tâche qui reste Blocked

**État** : La tâche est **Blocked** (en attente sur la queue). Elle ne consomme pas de CPU ; l'ordonnanceur ne la sélectionne pas.

**Autres tâches** : Elles s'exécutent normalement (Ready → Running). Seule la tâche Blocked n'avance pas.

**Débloquer** : Une autre tâche (ou ISR) doit faire **xQueueSend** (ou SendFromISR) vers cette queue ; la tâche passe alors Ready. Sinon, utiliser un **timeout** : xQueueReceive(..., pdMS_TO_TICKS(100)) pour se réveiller toutes les 100 ms et pouvoir détecter l'absence de données (logging, erreur, secours).

---

**Retour** : [Scénarios](../scenarios/README.md) · [Leçon 2](../02-etats-ordonnancement.md)
