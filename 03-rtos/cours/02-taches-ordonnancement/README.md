# Tâches et ordonnancement – Vue d'ensemble

Ce sous-dossier contient le cours **Tâches et ordonnancement** : création et configuration des tâches FreeRTOS, états, tick, vTaskDelay, priorité et dimensionnement de la stack.

---

## Objectifs pédagogiques

À l'issue de ce cours, l'étudiant sera capable de :

- **Créer** des tâches avec `xTaskCreate` (priorité, stack, paramètre, nom).
- Décrire les **états** d'une tâche (Running, Ready, Blocked, Suspended) et l'**ordonnancement** préemptif.
- Utiliser **vTaskDelay** et **pdMS_TO_TICKS** pour des comportements périodiques.
- Comprendre les **priorités** et le risque d'**inversion de priorité** avec les mutex.
- **Dimensionner** la stack des tâches et éviter les overflow.

---

## Ordre de lecture recommandé

| N° | Leçon | Contenu |
|----|--------|---------|
| 1 | [Création de tâches (xTaskCreate)](01-creation-taches.md) | Paramètres, stack, priorité, handle |
| 2 | [États et ordonnancement préemptif](02-etats-ordonnancement.md) | Running, Ready, Blocked, Suspended ; préemption |
| 3 | [vTaskDelay et tick](03-vtaskdelay-tick.md) | Tick, pdMS_TO_TICKS, boucles périodiques |
| 4 | [Priorités et inversion de priorité](04-priorites-inversion.md) | Priorité FreeRTOS, mutex, héritage |
| 5 | [Dimensionnement de la stack](05-dimensionnement-stack.md) | Overflow, configCHECK, high water mark |

---

## Public et prérequis

- **Public** : débutants (étudiants, autodidactes).
- **Prérequis** : cours **01 – Concepts RTOS et FreeRTOS** (notion de tâche, vTaskStartScheduler).

---

**Tester sa compréhension** : [Scénarios](scenarios/README.md) et [Réponses](reponses/README.md).

---

**Commencer par** : [01 – Création de tâches (xTaskCreate)](01-creation-taches.md)
