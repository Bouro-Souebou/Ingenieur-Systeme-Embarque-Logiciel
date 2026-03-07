# Leçon 5 – Bonnes pratiques et synthèse

## Objectif de la leçon

Récapituler les **bonnes pratiques** pour les queues, sémaphores et mutex (ISR, timeouts, dimensionnement), et faire la **synthèse** du module RTOS. Préparer la suite vers le module **04 – Périphériques**.

---

## 1. Depuis une ISR : uniquement FromISR

- **Queues** : **xQueueSendFromISR** / **xQueueReceiveFromISR** (pas xQueueSend/xQueueReceive).
- **Sémaphores** : **xSemaphoreGiveFromISR** (jamais xSemaphoreTake en ISR).
- **Mutex** : ne pas faire Take en ISR (bloquant). Donner un sémaphore ou envoyer un message pour qu'une **tâche** fasse le travail avec le mutex.
- Après un FromISR qui peut réveiller une tâche prioritaire : **portYIELD_FROM_ISR(pxHigherPriorityTaskWoken)**.

---

## 2. Timeouts

- **Éviter** **portMAX_DELAY** (attente infinie) quand c'est possible : utiliser un **timeout** fini (ex. pdMS_TO_TICKS(1000)) pour détecter les blocages (file vide trop longtemps, mutex jamais libéré) et réagir (erreur, reset, log).
- En **développement**, portMAX_DELAY peut simplifier le code ; en **production**, des timeouts permettent une meilleure robustesse.

---

## 3. Sections critiques (mutex) courtes

- Entre **Take** et **Give** du mutex : uniquement l'accès à la ressource partagée. Pas de **vTaskDelay**, pas de calcul lourd, pas d'appel à d'autres primitives qui pourraient bloquer longtemps. Sinon les autres tâches qui attendent le mutex subissent une **latence** élevée.

---

## 4. Dimensionnement des queues

- **Longueur** de la file : selon le **pic** de production (ex. burst de caractères UART). Si la tâche consommatrice est parfois lente, une file trop courte provoquera des **pertes** (Send qui échoue ou bloque).
- **Taille des éléments** : adapter au message (octet, structure). Éviter des structures très grandes si la fréquence d'envoi est élevée (copie coûteuse).

---

## 5. Synthèse du module RTOS

| Primitif | Usage principal | Depuis ISR |
|----------|------------------|------------|
| **Queue** | Passer des **données** (messages) entre tâches ou ISR ↔ tâche | SendFromISR, ReceiveFromISR |
| **Sémaphore binaire** | **Signal** (réveil tâche depuis ISR ou autre tâche) | GiveFromISR |
| **Sémaphore à compteur** | **Nombre de ressources** (slots, tokens) | GiveFromISR (Take en tâche) |
| **Mutex** | **Exclusion mutuelle** sur une ressource partagée | Pas de Take en ISR |

- **Tâches** : xTaskCreate, priorité, stack ; états Running/Ready/Blocked/Suspended ; vTaskDelay, tick.
- **Bonnes pratiques** : ISR courtes, FromISR uniquement en ISR, timeouts, sections critiques courtes, dimensionnement stack et queues.

---

## 6. Suite : module 04 – Périphériques

Avec le RTOS, tu peux structurer l'application en **tâches** (acquisition, commande, communication) et utiliser **queues** et **sémaphores** pour la synchronisation. Le module **04 – Périphériques** combine ces mécanismes avec les **pilotes** UART, SPI, I2C, PWM, ADC : une tâche par périphérique ou par fonction, des queues pour les données (ex. octets UART), des mutex pour les accès exclusifs (ex. bus SPI partagé).

---

## Tester sa compréhension

→ [Scénario – Bonnes pratiques](scenarios/05-bonnes-pratiques.md) · [Réponse](reponses/05-bonnes-pratiques.md)

---

**Fin du cours Synchronisation et communication.**  
Retour à la [vue d'ensemble](README.md) du module RTOS ou au [README principal](../../README.md) du parcours.  
→ **Module suivant** : [04 – Périphériques](../../../04-peripheriques/README.md).
