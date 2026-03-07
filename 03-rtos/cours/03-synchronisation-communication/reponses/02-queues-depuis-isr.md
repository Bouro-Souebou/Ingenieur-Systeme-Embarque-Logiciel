# Réponse – Queues depuis une ISR

Voir [scénario](../scenarios/02-queues-depuis-isr.md).

---

## Réponse Scénario 1 : xQueueSend en ISR (interdit)

**Problème** : xQueueSend(..., portMAX_DELAY) peut **bloquer** si la file est pleine. Une **ISR ne doit jamais bloquer**.

**API** : **xQueueSendFromISR**(queue, &byte, &pxHigherPriorityTaskWoken). Elle retourne immédiatement (errQUEUE_FULL si pleine).

**Après l'envoi** : Appeler **portYIELD_FROM_ISR(pxHigherPriorityTaskWoken)** pour que la tâche réveillée (si priorité suffisante) s'exécute dès la sortie de l'ISR.

---

## Réponse Scénario 2 : Réveil d'une tâche prioritaire après SendFromISR

**pxHigherPriorityTaskWoken** : Sortie du noyau : si une tâche **bloquée** sur la queue a une priorité **supérieure** à la tâche qui s'exécutait avant l'ISR, le noyau met *pxHigherPriorityTaskWoken à **pdTRUE** pour indiquer qu'un **context switch** devrait avoir lieu à la sortie de l'ISR.

**ISR** : Si *pxHigherPriorityTaskWoken == pdTRUE, appeler **portYIELD_FROM_ISR(pdTRUE)** avant de quitter l'ISR. Ainsi la tâche prioritaire réveillée s'exécute immédiatement après l'ISR.

**Sans portYIELD_FROM_ISR** : Le context switch aura lieu au prochain tick ou à la prochaine primitive bloquante → **latence** accrue pour la tâche prioritaire (peut manquer une contrainte temps réel).

---

**Retour** : [Scénarios](../scenarios/README.md) · [Leçon 2](../02-queues-depuis-isr.md)
