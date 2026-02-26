# Éléments de réponse – Latence, jitter et déterminisme

Réponses pour les [scénarios Latence, jitter, déterminisme](../scenarios/latence-jitter-determinisme.md).

---

## Scénario 1 : malloc dans une boucle de régulation

### Analyse (ce qu'il faut comprendre)

- **Le problème** : Le temps d'exécution de `malloc()` et `free()` est **imprévisible** : il dépend de l'état du tas (heap), du nombre de blocs déjà alloués, de la **fragmentation**. La boucle de régulation n'a donc plus un temps d'exécution **borné** d'une période à l'autre.
- **La conséquence** : **Jitter** important : une fois la boucle prend 0,2 ms, une autre fois 1,5 ms. Le **déterminisme** est perdu. Les algorithmes de régulation (PID, etc.) supposent une **période fixe** ; un jitter fort dégrade la stabilité voire la sécurité.
- **Le risque** : Après plusieurs heures, la **fragmentation** du heap peut faire échouer un `malloc()` (plus de bloc contigu suffisant) → la boucle ne peut plus s'exécuter correctement, le système peut planter ou perdre le contrôle.

### La solution

- **Remplacer** l'allocation dynamique par un **buffer statique** (global ou `static`) ou un **pool de blocs de taille fixe** alloués au démarrage.
- **Garantir** un **WCET** (pire temps d'exécution) borné pour la boucle : pas de malloc/free, pas de boucles dont le nombre d'itérations dépend de données non bornées.
- En **temps réel dur**, les standards (ex. MISRA, certification aéronautique) interdisent ou restreignent fortement l'usage de malloc dans les parties critiques.

### Un autre piège : boucles non bornées

Même sans malloc, une **boucle d'attente** dont la condition dépend d'un **événement externe** (capteur, réseau) sans **timeout** peut ne jamais terminer. Le WCET de la tâche n'est plus borné → impossible de garantir les échéances. **Toujours** prévoir un timeout ou un nombre max d'itérations dans les parties critiques.

---

## Scénario 2 : Attente sur un flag sans timeout

### Analyse

- **Le problème** : La tâche **bloque indéfiniment** si `flag_capteur_pret` n'est jamais mis à 1 (capteur déconnecté, ISR non déclenchée, bug). La boucle `while (!flag_capteur_pret)` est une **attente active** (busy-wait) **non bornée**.
- **La conséquence** : La tâche consomme **100 % du CPU** (ou, si on ajoutait un délai dans la boucle, elle ne ferait plus jamais rien d'utile). Les autres tâches peuvent être **affamées**. Le **WCET** de cette tâche n'est pas borné (il peut être « infini »).
- **Le risque** : **Perte de déterminisme** et **indéterminisme** : on ne peut plus garantir aucun délai de réponse pour le reste du système. En cas de défaillance du capteur, tout le système peut sembler gelé.

### La solution

- **Ne jamais** attendre sur une condition externe **sans timeout** dans une tâche temps réel. Utiliser par exemple :
  - Un **timeout** : attendre le flag pendant au plus X ms, puis vérifier l'état du capteur (défaut) et remonter une erreur.
  - En RTOS : **bloquer** sur un sémaphore ou une file avec **timeout** (ex. `xQueueReceive(..., timeout_ms)`), au lieu de busy-wait.
- **Détecter** la défaillance du capteur (absence de mise à jour du flag pendant un délai anormal) et passer en mode dégradé ou signaler l'erreur.

### Un autre piège : désactiver les interruptions trop longtemps

Pour « protéger » la lecture du flag, un développeur désactive les interruptions autour de `if (flag_capteur_pret) { ... }`. Si la section critique est longue, la **latence** de toutes les autres interruptions augmente et le **jitter** aussi. Les sections critiques doivent rester **très courtes** (lire/écrire une variable atomique, pas un traitement).

---

**Retour** : [Scénarios – Latence, jitter, déterminisme](../scenarios/latence-jitter-determinisme.md) · [Leçon 2](../02-latence-jitter-determinisme.md)
