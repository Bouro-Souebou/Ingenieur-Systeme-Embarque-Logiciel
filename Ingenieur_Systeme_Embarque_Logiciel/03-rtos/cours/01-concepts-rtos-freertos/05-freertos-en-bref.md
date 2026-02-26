# Leçon 5 – FreeRTOS en bref

## Objectif de la leçon

Situer **FreeRTOS** dans l'écosystème : licence, portabilité, configuration, et intégration dans un projet bare-metal (remplacer la boucle principale par `vTaskStartScheduler()`).

---

## 1. Open source et licence

**FreeRTOS** est un RTOS **open source**, sous licence **MIT** (utilisation commerciale et modification autorisées, avec conservation du copyright et de la licence). Il est très répandu dans l'industrie (automobile, aéronautique, objets connectés) et dans l'enseignement.

Amazon propose une distribution étendue (**FreeRTOS** avec librairies AWS pour le cloud) ; le **noyau** (kernel) reste le même (tâches, queues, sémaphores, timers). Nous parlons ici du **noyau** FreeRTOS.

---

## 2. Portabilité

FreeRTOS est **portable** : le code du noyau (ordonnanceur, queues, etc.) est indépendant du processeur. L'adaptation à une cible (MCU + compilateur) est faite par une **couche port** (port layer) : implémentation du changement de contexte (sauvegarde/restauration des registres), du tick (souvent SysTick), et des sections critiques (désactivation d'interruptions). Des ports existent pour ARM Cortex-M, RISC-V, Xtensa, etc.

En pratique : tu choisis le bon **port** pour ton MCU (ex. ARM_CM4F pour Cortex-M4 avec FPU) et tu compiles le noyau avec ton projet. Les APIs (xTaskCreate, xQueueSend, etc.) sont les mêmes quelle que soit la cible.

---

## 3. Configuration (FreeRTOSConfig.h)

Le comportement du noyau est réglé par un fichier **FreeRTOSConfig.h** : nombre de **priorités**, fréquence du **tick** (configTICK_RATE_HZ), activation des **hooks** (idle, stack overflow), taille des types (configUSE_16_BIT_TICKS ou non), options (co-routines, stream buffers, etc.). Chaque projet inclut ce fichier (souvent fourni par un template ou par CubeMX pour STM32).

Il est important de **vérifier** la taille des stacks des tâches et la fréquence du tick selon l'application (tick à 1 kHz = 1 ms de résolution pour vTaskDelay).

---

## 4. Intégration dans un projet

Dans un projet **bare-metal** (sans autre OS) :

1. **Initialiser** le matériel (horloges, GPIO, périphériques) comme d'habitude dans `main()`.
2. **Créer** les tâches avec `xTaskCreate()` (avant de démarrer l'ordonnanceur).
3. **Créer** les queues, sémaphores, mutex nécessaires.
4. Appeler **vTaskStartScheduler()**. Cette fonction **ne revient pas** en temps normal : le CPU est alors géré par l'ordonnanceur. La « boucle principale » devient l'alternance entre les tâches.
5. Une tâche **idle** (priorité 0) s'exécute quand aucune autre tâche n'est prête.

Si vTaskStartScheduler() retourne (manque de heap pour la tâche idle, ou erreur de config), il faut prévoir une boucle de secours ou un indicateur d'erreur.

---

## Points clés à retenir

- **FreeRTOS** : noyau RTOS open source (MIT), **portable** (port par MCU/compilateur).
- **FreeRTOSConfig.h** : priorités, tick, options ; à adapter au projet.
- **Intégration** : init hardware → créer tâches et objets → **vTaskStartScheduler()** (ne revient pas).

---

**Fin du cours Concepts RTOS et FreeRTOS.**  
Retour à la [vue d'ensemble](README.md) ou passage au cours [Tâches et ordonnancement](../../02-taches-ordonnancement/README.md).
