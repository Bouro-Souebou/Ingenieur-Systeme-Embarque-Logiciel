# Réponse – Sémaphores

Voir [scénario](../scenarios/03-semaphores.md).

---

## Réponse Scénario 1 : Bouton vs N slots

**Bouton (réveil sans donnée)** : **Sémaphore binaire** – l'ISR fait GiveFromISR, la tâche fait Take (bloquant). Pas de queue (on ne transmet pas d'octet).

**N slots (ressources)** : **Sémaphore à compteur** (valeur 0 à N). Take = prendre un slot (décrémenter), Give = rendre un slot (incrémenter). Si compteur à 0, Take bloque.

---

## Réponse Scénario 2 : GiveFromISR sans réveil immédiat

**NULL** : En passant NULL, on ne peut pas savoir si une tâche **prioritaire** a été débloquée. Le noyau ne peut pas demander un **context switch** à la sortie de l'ISR.

**Pointeur** : Déclarer `BaseType_t xHigherPriorityTaskWoken = pdFALSE` ; passer **&xHigherPriorityTaskWoken** à GiveFromISR. Après l'appel : `if (xHigherPriorityTaskWoken == pdTRUE) portYIELD_FROM_ISR(pdTRUE);`.

Sans cela, la tâche débloquée peut attendre le prochain tick pour s'exécuter → **latence** inutile si elle est prioritaire.

---

**Retour** : [Scénarios](../scenarios/README.md) · [Leçon 3](../03-semaphores-binaires-compteur.md)
