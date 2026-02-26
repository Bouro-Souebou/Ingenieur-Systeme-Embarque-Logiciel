# Leçon 1 – Queues : création, envoi et réception

## Objectif de la leçon

Savoir **créer** une file d'attente FreeRTOS, **envoyer** des éléments (depuis une tâche) et **recevoir** des éléments (avec blocage optionnel et timeout). Comprendre les paramètres de création (nombre d'éléments, taille d'un élément).

---

## 1. Création : xQueueCreate

```c
QueueHandle_t xQueueCreate(UBaseType_t uxQueueLength, UBaseType_t uxItemSize);
```

- **uxQueueLength** : nombre **maximum** d'éléments dans la file (ex. 5, 10, 16).
- **uxItemSize** : taille en **octets** de chaque élément (ex. `sizeof(uint8_t)` pour des octets, `sizeof(ma_structure)` pour des messages structurés).

La file est **FIFO** (First In, First Out) : le premier élément envoyé est le premier reçu. Retour : un **handle** (QueueHandle_t) ou **NULL** si l'allocation a échoué (manque de heap).

Exemple :

```c
QueueHandle_t q = xQueueCreate(10, sizeof(uint8_t));
if (q != NULL) {
    /* utiliser q */
}
```

---

## 2. Envoi : xQueueSend

```c
BaseType_t xQueueSend(QueueHandle_t xQueue, const void *pvItemToQueue, TickType_t xTicksToWait);
```

- **pvItemToQueue** : pointeur vers l'élément à **copier** dans la file (taille = uxItemSize à la création).
- **xTicksToWait** : si la file est **pleine**, attendre au plus **xTicksToWait** ticks (ou **portMAX_DELAY** pour attendre indéfiniment, ou **0** pour ne pas bloquer).

Retour : **pdPASS** si l'élément a été envoyé, **errQUEUE_FULL** si timeout sans place disponible.

---

## 3. Réception : xQueueReceive

```c
BaseType_t xQueueReceive(QueueHandle_t xQueue, void *pvBuffer, TickType_t xTicksToWait);
```

- **pvBuffer** : pointeur vers une zone où **copier** l'élément reçu (au moins uxItemSize octets).
- **xTicksToWait** : si la file est **vide**, attendre au plus **xTicksToWait** ticks (ou **portMAX_DELAY**, ou **0** pour ne pas bloquer).

Retour : **pdPASS** si un élément a été reçu, **errQUEUE_EMPTY** si timeout sans donnée.

Exemple (tâche consommatrice) :

```c
uint8_t byte;
if (xQueueReceive(q_uart, &byte, pdMS_TO_TICKS(100)) == pdPASS) {
    traiter(byte);
}
```

---

## 4. Variantes : SendToBack, SendToFront

**xQueueSendToBack** = **xQueueSend** (comportement par défaut). **xQueueSendToFront** insère l'élément **en tête** de la file (priorité). Pour une file simple FIFO, utiliser **xQueueSend** (ou SendToBack).

---

## Points clés à retenir

- **xQueueCreate(length, itemSize)** : file de **length** éléments de **itemSize** octets.
- **xQueueSend** : envoyer (bloque si file pleine, selon timeout).
- **xQueueReceive** : recevoir (bloque si file vide, selon timeout).
- Utiliser **pdMS_TO_TICKS(ms)** pour des timeouts en millisecondes.

---

**Suite** : [Leçon 2 – Queues depuis une ISR (FromISR)](02-queues-depuis-isr.md)
