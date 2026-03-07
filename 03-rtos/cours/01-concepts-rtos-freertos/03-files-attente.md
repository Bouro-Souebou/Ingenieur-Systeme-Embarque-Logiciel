# Leçon 3 – Files d'attente (queues)

## Objectif de la leçon

Comprendre le rôle des **files d'attente** (queues) : échanger des **messages** (données) entre tâches ou entre une **ISR** et une tâche, avec blocage optionnel (attendre un message si la file est vide).

---

## 1. Problème : passer des données entre tâches

Une **ISR** reçoit un octet sur l'UART ; une **tâche** doit le traiter (parsing, affichage). Si on utilise uniquement un **flag** (variable volatile), on sait qu'un événement s'est produit mais on ne connaît pas la **valeur** (l'octet). Il faudrait un buffer partagé et des indices, avec risque de **race condition** si on ne protège pas les accès.

Une **file d'attente** (queue) est une structure gérée par le RTOS : une tâche (ou une ISR) **envoie** un élément (un octet, une structure), une autre tâche **reçoit** un élément. Si la file est vide, la tâche qui reçoit peut **bloquer** jusqu'à ce qu'un élément soit disponible (ou jusqu'à un timeout). Le RTOS gère la synchronisation et la cohérence.

---

## 2. Création et taille

À la **création**, on fixe :

- Le **nombre d'éléments** (ex. 5 ou 10).
- La **taille** de chaque élément (ex. `sizeof(uint8_t)` pour des octets, ou `sizeof(ma_structure)` pour des messages structurés).

Exemple (FreeRTOS) :

```c
QueueHandle_t q_uart = xQueueCreate(16, sizeof(uint8_t));   /* 16 octets */
```

La file contient au plus 16 éléments ; chaque élément fait 1 octet. Si on envoie 17 éléments sans que personne ne consomme, le 17e envoi peut bloquer (ou échouer selon les options).

---

## 3. Envoi et réception (côté tâche)

- **xQueueSend(queue, &data, timeout)** : envoyer un élément. Si la file est **pleine**, la tâche peut **bloquer** jusqu'à `timeout` (ou `portMAX_DELAY` pour attendre indéfiniment).
- **xQueueReceive(queue, &buf, timeout)** : recevoir un élément dans `buf`. Si la file est **vide**, la tâche peut bloquer jusqu'à `timeout`.

Une tâche **producteur** envoie des données ; une tâche **consommateur** les reçoit et les traite. Typique : ISR UART envoie les octets reçus dans une queue ; une tâche « traitement UART » fait xQueueReceive et parse les commandes.

---

## 4. Depuis une ISR : versions FromISR

Une **ISR** ne doit **jamais** bloquer (pas d'attente avec timeout long). FreeRTOS fournit des versions **FromISR** :

- **xQueueSendFromISR(queue, &data, &wake)** : envoyer un élément depuis l'ISR. Si une tâche était bloquée en attente d'un message, le paramètre `wake` peut être mis à `pdTRUE` ; il faut alors appeler **portYIELD_FROM_ISR(wake)** pour que l'ordonnanceur passe éventuellement à cette tâche dès la sortie de l'ISR.
- **xQueueReceiveFromISR** : réception depuis l'ISR (peu fréquent ; en général l'ISR envoie, la tâche reçoit).

---

## Points clés à retenir

- **Queue** = file d'éléments (taille et nombre fixés à la création) ; permet d'**échanger des données** entre tâches ou ISR ↔ tâche.
- **xQueueSend** / **xQueueReceive** (côté tâche) peuvent **bloquer** si la file est pleine ou vide.
- **ISR** : utiliser **xQueueSendFromISR** (et **portYIELD_FROM_ISR** si indiqué) ; ne jamais bloquer.

---

## Tester sa compréhension

→ [Scénario – Files d'attente](scenarios/03-files-attente.md) · [Réponse](reponses/03-files-attente.md)

---

**Suite** : [Leçon 4 – Sémaphores et mutex : vue d'ensemble](04-semaphores-mutex-vue-ensemble.md)
