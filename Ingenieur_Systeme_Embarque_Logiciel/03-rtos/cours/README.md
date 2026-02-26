# Cours – Module RTOS (FreeRTOS)

Les cours du module **03 – RTOS** sont organisés en **sous-dossiers** : chaque thème est détaillé en plusieurs leçons progressives, adaptées aux **débutants** et réutilisables pour des **étudiants**.

---

## Structure des cours

| Dossier | Contenu | Nombre de leçons |
|---------|---------|-------------------|
| [**01-concepts-rtos-freertos**](01-concepts-rtos-freertos/README.md) | Concepts RTOS et FreeRTOS (pourquoi RTOS, tâches, queues, sémaphores/mutex, FreeRTOS) | 5 leçons |
| [**02-taches-ordonnancement**](02-taches-ordonnancement/README.md) | Tâches et ordonnancement (xTaskCreate, états, vTaskDelay, priorité, stack) | 5 leçons |
| [**03-synchronisation-communication**](03-synchronisation-communication/README.md) | Synchronisation et communication (queues, FromISR, sémaphores, mutex, bonnes pratiques) | 5 leçons |

---

## Ordre recommandé

1. **Concepts RTOS et FreeRTOS** → comprendre pourquoi un RTOS et les entités de base.
2. **Tâches et ordonnancement** → créer des tâches, états, délais, priorité, stack.
3. **Synchronisation et communication** → queues, sémaphores, mutex, et usage depuis les ISR.

Chaque sous-dossier contient un **README** (vue d'ensemble, objectifs, ordre des leçons) et des fichiers **.md** numérotés à lire dans l'ordre.

---

## Prérequis

Avoir validé le module **02 – Microcontrôleurs** (interruptions, registres, startup). Le module **01 – Fondements** (temps réel, boucle vs RTOS) est recommandé.
