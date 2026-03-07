# Réponse – Tâches : unité d'exécution

Voir [scénario](../scenarios/02-taches-unite-execution.md).

---

## Réponse Scénario 1 : printf et mélange de sorties

**Mélange** : Une seule tâche est **Running** à la fois ; si une tâche fait printf puis est préemptée avant la fin, l'autre peut printf à son tour → sortie entremêlée. printf n'est pas thread-safe par défaut.

**Ralentissement** : printf est coûteux (buffer, formatage) ; si plusieurs tâches en abusent, le CPU passe beaucoup de temps dedans.

**Solution** : Protéger printf avec un **mutex** (Take avant, Give après) ; ou envoyer les messages dans une **queue** et une seule tâche dédiée fait les printf ; ou réduire/désactiver les printf en production.

---

## Réponse Scénario 2 : Variable partagée sans protection

**Cause** : L'incrémentation (lecture-modification-écriture) n'est pas **atomique** : une tâche peut être préemptée entre la lecture et l'écriture ; l'autre modifie la valeur → perte d'incréments.

**Unité d'exécution** : La tâche est une unité logique, mais l'ordonnanceur peut **préempter** à tout moment ; donc une variable partagée sans protection n'est pas sûre.

**Primitive** : **Mutex** (xSemaphoreCreateMutex) : Take avant lecture/écriture du compteur, Give après. Ou **section critique** (taskENTER_CRITICAL / taskEXIT_CRITICAL) pour une section très courte.

---

**Retour** : [Scénarios](../scenarios/README.md) · [Leçon 2](../02-taches-unite-execution.md)
