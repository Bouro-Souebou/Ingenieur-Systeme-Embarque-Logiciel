# Concepts RTOS et FreeRTOS – Vue d'ensemble

Ce sous-dossier contient le cours **Concepts RTOS et FreeRTOS** : pourquoi utiliser un RTOS, entités de base (tâches, files, sémaphores, mutex), et présentation de FreeRTOS.

---

## Objectifs pédagogiques

À l'issue de ce cours, l'étudiant sera capable de :

- Expliquer **pourquoi** un RTOS par rapport à une super-loop.
- Décrire les **entités** de base : tâche, file d'attente, sémaphore, mutex.
- Situer **FreeRTOS** dans l'écosystème (open source, portable, configurable).
- Comprendre le principe de l'**ordonnancement** préemptif et du **tick**.

---

## Ordre de lecture recommandé

| N° | Leçon | Contenu |
|----|--------|---------|
| 1 | [Pourquoi un RTOS ?](01-pourquoi-rtos.md) | Limites de la super-loop, besoins temps réel |
| 2 | [Tâches : unité d'exécution](02-taches-unite-execution.md) | Définition, priorité, stack, point d'entrée |
| 3 | [Files d'attente (queues)](03-files-attente.md) | Échange de messages, producteur/consommateur |
| 4 | [Sémaphores et mutex : vue d'ensemble](04-semaphores-mutex-vue-ensemble.md) | Signal, compteur, exclusion mutuelle |
| 5 | [FreeRTOS en bref](05-freertos-en-bref.md) | Open source, portable, configurable, intégration |

---

## Public et prérequis

- **Public** : débutants (étudiants, autodidactes).
- **Prérequis** : module **02 – Microcontrôleurs** (interruptions, ISR, notion de priorité). Module **01 – Fondements** (temps réel, boucle vs RTOS) recommandé.

---

**Tester sa compréhension** : [Scénarios](scenarios/README.md) et [Réponses](reponses/README.md).

---

**Commencer par** : [01 – Pourquoi un RTOS ?](01-pourquoi-rtos.md)
