# Réponse – Intégration UART et RTOS

Voir [scénario](../scenarios/05-integration-rtos.md).

---

## Réponse Scénario 1 : Queue RX entre ISR et tâche

**Cause** : Si la **tâche** qui consomme la queue a une priorité **trop basse**, elle ne s'exécute pas assez souvent ; la queue **se remplit** (128 octets à 115200 baud arrive vite). SendFromISR retourne **errQUEUE_FULL** → octets **perdus**. Autre cause : **queue trop petite** (augmenter la taille).

**FromISR et Yield** : **xQueueSendFromISR** : API non bloquante pour l'ISR. **portYIELD_FROM_ISR(wake)** : si une tâche de priorité plus haute a été débloquée, le context switch a lieu à la sortie de l'ISR → la tâche de traitement s'exécute tout de suite, réduisant la latence et le risque de queue pleine.

**Timeout** : xQueueReceive(..., **pdMS_TO_TICKS(100)**) : la tâche se réveille au plus tard après 100 ms même si aucun octet n'arrive. Permet de faire des **vérifications périodiques** (watchdog, LED de vie), d'éviter un blocage infini si l'UART est coupé.

---

## Réponse Scénario 2 : Plusieurs tâches qui envoient

**Mélange** : Les deux tâches écrivent dans le **même registre DR** sans coordination ; les octets de l'une et de l'autre s'intercalent. Pas d'**exclusion mutuelle** sur la ressource « UART TX ».

**Mutex** : Une **tâche dédiée** « envoi UART » détient un **mutex** sur l'UART. Les autres tâches qui veulent envoyer mettent leur **message** (ou pointeur) dans une **queue** ; la tâche envoi fait Take(mutex), récupère un message de la queue, envoie octet par octet (ou par bloc), Give(mutex). Un seul expéditeur à la fois → pas de mélange.

**Queue TX** : Une **queue d'octets** (ou de messages) à envoyer ; une **tâche** (ou ISR TX) dépile et écrit dans DR. Les autres tâches font xQueueSend(q_tx, ...). Si plusieurs tâches envoient des messages multi-octets, il faut s'assurer qu'un message est envoyé en entier avant un autre (mutex ou un seul producteur de la queue).

---

**Retour** : [Scénarios](../scenarios/README.md) · [Leçon 5](../05-integration-rtos.md)
