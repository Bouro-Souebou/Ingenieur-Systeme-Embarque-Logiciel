# 03 – RTOS (FreeRTOS)

Tâches, files d'attente, sémaphores, mutex, gestion mémoire et bonnes pratiques pour le temps réel.  
Les cours sont **détaillés en leçons progressives** dans des sous-dossiers, destinés aux **débutants** et utilisables pour des **étudiants**.

## Contenu des cours

Les cours se trouvent dans le dossier **[cours/](cours/)**. Chaque thème est découpé en plusieurs leçons (sous-dossiers) :

| Thème | Dossier | Description |
|-------|---------|-------------|
| **Concepts RTOS et FreeRTOS** | [cours/01-concepts-rtos-freertos/](cours/01-concepts-rtos-freertos/README.md) | 5 leçons : pourquoi RTOS, tâches, queues, sémaphores/mutex, FreeRTOS |
| **Tâches et ordonnancement** | [cours/02-taches-ordonnancement/](cours/02-taches-ordonnancement/README.md) | 5 leçons : xTaskCreate, états, vTaskDelay, priorité, stack |
| **Synchronisation et communication** | [cours/03-synchronisation-communication/](cours/03-synchronisation-communication/README.md) | 5 leçons : queues, FromISR, sémaphores, mutex, bonnes pratiques |

→ **Index complet** : [cours/README.md](cours/README.md)

## Applications pratiques

- **tp/** : création de tâches, queues, sémaphores, mutex.
- **projet/** : application multi-tâches (ex. superviseur + pilotes UART/GPIO).

## Prérequis

Avoir validé le module **02 – Microcontrôleurs** (interruptions, registres, startup).
