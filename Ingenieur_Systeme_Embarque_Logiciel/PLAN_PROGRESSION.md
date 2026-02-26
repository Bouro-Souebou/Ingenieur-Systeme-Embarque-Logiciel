# Plan de progression – Ingénieur électronique embarqué logiciel

Ce document détaille un planning type sur **environ 5 mois** (1 module = 3–4 semaines, à adapter selon ton rythme).

---

## Phase 1 : Fondements (semaines 1–4)

| Semaine | Contenu | Pratique |
|---------|---------|----------|
| 1 | Cours 1.1 – C pour l’embarqué | Exercice volatile/bits, types `stdint` |
| 2 | Cours 1.2 – Bus (UART, SPI, I2C) | Schémas de timing, choix de protocole |
| 3 | Cours 1.3 – Temps réel | Notions de latence, ISR courtes |
| 4 | Synthèse | Mini-projet : machine à états + parsing simple (sur PC ou cible) |

**Validation** : être à l’aise avec `volatile`, accès bits, et la différence entre UART/SPI/I2C.

---

## Phase 2 : Microcontrôleurs (semaines 5–8)

| Semaine | Contenu | Pratique |
|---------|---------|----------|
| 5 | Cours 2.1 – Architecture Cortex-M | Lire le manuel, identifier RCC/GPIO |
| 6 | Cours 2.2 – Registres | Blink bare-metal (LED) |
| 7 | Cours 2.3 – Startup, interruptions | ISR sur bouton, toggle LED |
| 8 | Synthèse | Projet : chrono ou compteur avec affichage (7 segments ou UART) |

**Validation** : faire clignoter une LED et réagir à un bouton sans HAL (registres uniquement si possible).

---

## Phase 3 : RTOS (semaines 9–12)

| Semaine | Contenu | Pratique |
|---------|---------|----------|
| 9 | Cours 3.1 – Concepts RTOS, FreeRTOS | Projet CubeMX + FreeRTOS, 2 tâches |
| 10 | Cours 3.2 – Tâches, ordonnancement | Priorités, vTaskDelay, stack |
| 11 | Cours 3.3 – Sync (queues, sémaphores, mutex) | Tâche UART + tâche LED avec queue |
| 12 | Synthèse | Projet : superviseur + 2–3 tâches (LED, UART, timer) |

**Validation** : une application multi-tâches avec au moins une queue et un mutex.

---

## Phase 4 : Périphériques (semaines 13–18)

| Semaine | Contenu | Pratique |
|---------|---------|----------|
| 13 | UART (cours 4.1) | Echo UART, puis commandes (LED ON/OFF) |
| 14 | SPI / I2C (cours 4.2) | Lire un capteur I2C ou SPI |
| 15 | Timers, PWM (cours 4.3) | PWM LED ou moteur, variation du duty |
| 16 | ADC, DMA (cours 4.4) | Acquisition continue, envoi par UART |
| 17–18 | Synthèse | Projet : datalogger (ADC + stockage/UART) ou petit contrôleur (PWM + UART) |

**Validation** : avoir utilisé au moins UART, un bus (I2C ou SPI), PWM et ADC sur la même cible.

---

## Phase 5 : Projets avancés (à partir de la semaine 19)

| Thème | Contenu | Livrable |
|-------|---------|----------|
| Architecture | Cours 5.1 | Projet structuré en BSP / drivers / app |
| Tests & débogage | Cours 5.2 | Tests sur PC (mocks), procédure de flash/débogage |
| Robustesse | Cours 5.3 | Timeouts, watchdog, gestion d’erreurs |
| Projet au choix | Bootloader, moteur, IoT… | Rapport court + code + README |

**Validation** : un projet complet documenté, avec build reproductible et au moins une stratégie de test ou de débogage décrite.

---

## Conseils généraux

- **Régularité** : 1–2 h par jour ou 2–3 séances de 2 h par semaine.
- **Matériel** : une carte STM32 Nucleo (ou équivalent) suffit pour tout le parcours ; ajouter un oscilloscope ou un analyseur logique si possible pour les bus.
- **Notes** : tenir un petit cahier ou un fichier « notes formation » pour les adresses, les pièges et les astuces par MCU.
- **Révision** : avant de passer au module suivant, refaire un exercice du module précédent pour ancrer les réflexes.

Bon courage.
