# TP 2 – Blink LED (bare-metal)

**Objectif** : faire clignoter la LED LD2 (PA5) en accédant directement aux registres **RCC** et **GPIO**, sans HAL.

## Cible NUCLEO-F446RE

- LED LD2 = **PA5** (port A, broche 5).
- RCC : activer l’horloge du port A (RCC AHB1ENR, bit GPIOAEN).
- GPIOA : MODER (mode sortie pour la broche 5), ODR (niveau haut/bas).

## Fichiers

- **main.c** : à copier dans votre projet (remplacer le `main.c` généré), ou à intégrer dans le projet créé au TP 1.

## Étapes

1. Ouvrir (ou créer) un projet pour STM32F446RE (voir [TP 1](../01-outils-prise-en-main.md)).
2. Remplacer le contenu de `main.c` par celui fourni dans ce dossier.
3. Build, flash, run : la LED doit clignoter.
4. **Bonus** : modifier le délai (macro ou variable) pour changer la fréquence de clignotement.

## Références

- Cours 02 (registres, GPIO, MODER/ODR).
- Reference Manual STM32F446 : chapitres RCC (AHB1ENR), GPIO (MODER, ODR).

**Suite** : [TP 3 – Bouton + LED](../03-bouton-led/README.md) (lecture GPIO entrée, polling).
