# TP – RTOS (FreeRTOS)

## Fichiers

- **two_tasks_blink.c** : création de deux tâches (LED clignotante + worker). À intégrer dans un projet FreeRTOS existant ; fournir `led_on` / `led_off` (ou les remplacer par des appels HAL).

## À faire

1. Créer un projet FreeRTOS sur ta carte (CubeMX + FreeRTOS, ou template).
2. Implémenter `led_on` / `led_off` (GPIO) et appeler `create_demo_tasks()` avant `vTaskStartScheduler()`.
3. Compiler, flasher : la LED doit clignoter toutes les 500 ms.
4. **Bonus** : ajouter une queue ; une tâche envoie un message (ex. compteur), l’autre le reçoit et allume la LED uniquement quand le compteur est pair (exemple de communication inter-tâches).
