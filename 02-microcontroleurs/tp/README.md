# TP – Microcontrôleurs

## Fichiers

- **blink_bare_metal.c** : allumage d’une LED en accédant directement aux registres RCC et GPIO (template STM32F4). Adapter les adresses et les noms pour ta carte (voir Reference Manual du MCU).

## À faire

1. Créer un projet (STM32CubeIDE ou Makefile + arm-none-eabi-gcc) et inclure ce fichier comme `main.c` (ou l’intégrer à ton projet).
2. Vérifier la broche LED sur le schéma de la carte (souvent PA5 sur Nucleo).
3. Compiler, flasher, lancer : la LED doit clignoter.
4. **Bonus** : ajouter une interruption EXTI sur un bouton utilisateur ; dans l’ISR, inverser l’état de la LED (variable `volatile` + flag si tu fais le traitement dans `main`).

## Références

- Reference Manual du MCU : chapitres RCC, GPIO.
- Datasheet de la carte : numéro de broche de la LED et du bouton.
