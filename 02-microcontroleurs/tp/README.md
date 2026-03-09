# TP – Microcontrôleurs (STM32 NUCLEO F446RE)

Travaux pratiques progressifs : **prise en main des outils** puis programmation **bare-metal** sur NUCLEO-F446RE.

## Cible

- **MCU** : STM32F446RET6 (Cortex-M4). **LED LD2** : PA5. **Bouton B1** : PC13 (actif à 0).
- **Programmation** : ST-Link intégré (USB).

## Ordre des TP

| TP | Fichier / Dossier | Objectif |
|----|-------------------|----------|
| 1 | [01-outils-prise-en-main.md](01-outils-prise-en-main.md) | IDE, projet, build, flash, debug |
| 2 | [02-blink-led/](02-blink-led/) | Clignoter la LED (RCC, GPIO) |
| 3 | [03-bouton-led/](03-bouton-led/) | Lire le bouton, piloter la LED (polling) |
| 4 | [04-interruption-exti/](04-interruption-exti/) | Bouton en interruption (EXTI, ISR) |

Chaque TP réutilise le projet ou une copie du projet. L’ancien fichier **blink_bare_metal.c** à la racine de `tp/` reste disponible ; la version à jour pour la F446RE est **02-blink-led/main.c**.

## Chaîne de développement

Voir : [../../ressources/chaine-compilation-deploiement.md](../../ressources/chaine-compilation-deploiement.md)

## Références cours

- Cours 01 (architecture Cortex-M), 02 (registres, GPIO), 03 (startup, interruptions).
