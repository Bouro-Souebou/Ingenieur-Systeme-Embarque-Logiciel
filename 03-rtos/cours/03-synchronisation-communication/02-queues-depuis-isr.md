# Leçon 2 – Queues depuis une ISR (FromISR)

## Objectif de la leçon

Utiliser les **versions FromISR** des fonctions de queue depuis une **routine de service d'interruption** : xQueueSendFromISR (et éventuellement xQueueReceiveFromISR), et **portYIELD_FROM_ISR** pour déclencher un changement de tâche à la sortie de l'ISR.

---

## 1. Pourquoi des versions FromISR ?

Une **ISR** ne doit **jamais** bloquer (pas d'attente avec un long timeout). Les fonctions **normales** (xQueueSend, xQueueReceive) peuvent **bloquer** la tâche appelante si la file est pleine ou vide. En ISR, on ne peut pas bloquer : le noyau fournit des versions **FromISR** qui :
- **Ne bloquent pas** : si la file est pleine (SendFromISR) ou vide (ReceiveFromISR), elles retournent immédiatement avec un code d'erreur.
- **Signalent** si une tâche bloquée sur cette queue doit être réveillée ; dans ce cas, il faut appeler **portYIELD_FROM_ISR** pour que l'ordonnanceur puisse passer à cette tâche dès la sortie de l'ISR.

---

## 2. xQueueSendFromISR

```c
BaseType_t xQueueSendFromISR(QueueHandle_t xQueue, const void *pvItemToQueue, BaseType_t *pxHigherPriorityTaskWoken);
```

- **pvItemToQueue** : pointeur vers l'élément à envoyer (comme xQueueSend).
- **pxHigherPriorityTaskWoken** : pointeur vers un **BaseType_t**. Si une tâche était bloquée en attente d'un message et que cette tâche a une priorité **supérieure ou égale** à la tâche qui était en cours avant l'ISR, FreeRTOS met ***pxHigherPriorityTaskWoken = pdTRUE**. À la sortie de l'ISR, il faut appeler **portYIELD_FROM_ISR(*pxHigherPriorityTaskWoken)** (ou portYIELD_FROM_ISR(pdTRUE) si pdTRUE) pour que le changement de contexte ait lieu immédiatement.

Exemple (ISR UART qui envoie l'octet reçu dans une queue) :

```c
void USART1_IRQHandler(void) {
    BaseType_t wake = pdFALSE;
    if (USART1->SR & USART_SR_RXNE) {
        uint8_t byte = (uint8_t)(USART1->DR & 0xFF);
        xQueueSendFromISR(q_uart, &byte, &wake);
    }
    portYIELD_FROM_ISR(wake);
}
```

Si **wake** vaut **pdTRUE**, la tâche qui attend sur **q_uart** (et qui a une priorité suffisante) sera schedulée juste après l'ISR.

---

## 3. xQueueReceiveFromISR

Même principe pour la **réception** depuis une ISR : **xQueueReceiveFromISR(queue, &buf, &wake)**. Peu utilisé (en général l'ISR **envoie**, la tâche **reçoit**), mais disponible si besoin.

---

## 4. Règle : pas de blocage en ISR

En ISR, **ne jamais** appeler les fonctions **sans** suffixe FromISR pour les objets FreeRTOS (queues, sémaphores, mutex). Les versions normales peuvent bloquer et ne doivent être utilisées que depuis une **tâche**.

---

## Points clés à retenir

- **xQueueSendFromISR** (et ReceiveFromISR) : **non bloquant** ; utiliser depuis une ISR uniquement.
- **pxHigherPriorityTaskWoken** : si **pdTRUE**, appeler **portYIELD_FROM_ISR(wake)** pour réveiller une tâche prioritaire à la sortie de l'ISR.
- Ne **jamais** utiliser **xQueueSend** / **xQueueReceive** (bloquants) dans une ISR.

---

**Suite** : [Leçon 3 – Sémaphores binaires et à compteur](03-semaphores-binaires-compteur.md)
