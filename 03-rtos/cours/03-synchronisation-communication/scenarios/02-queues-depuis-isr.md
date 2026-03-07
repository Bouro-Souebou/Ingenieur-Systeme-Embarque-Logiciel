# Scénario – Queues depuis une ISR

Pour la leçon [02 – Queues depuis une ISR](../02-queues-depuis-isr.md).

---

## Scénario 1 : xQueueSend en ISR (interdit)

L'ISR UART utilise **xQueueSend(q, &byte, portMAX_DELAY)** pour envoyer l'octet reçu à une tâche.

**Questions** : Quel est le problème (blocage en ISR) ? Quelle API utiliser (FromISR) ? Que faire après l'envoi (portYIELD_FROM_ISR) ?

---

## Scénario 2 : Réveil d'une tâche prioritaire après SendFromISR

L'ISR envoie avec **xQueueSendFromISR** et reçoit **pxHigherPriorityTaskWoken**. Elle ne fait rien avec cette variable.

**Questions** : À quoi sert pxHigherPriorityTaskWoken ? Que doit faire l'ISR avant de sortir si la valeur est pdTRUE ? Que se passe-t-il si on n'appelle pas portYIELD_FROM_ISR (latence) ?

---

**Réponse** : [../reponses/02-queues-depuis-isr.md](../reponses/02-queues-depuis-isr.md) · **Retour** : [Vue d'ensemble](../README.md)
