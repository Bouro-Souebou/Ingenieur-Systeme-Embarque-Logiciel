# Template projet personnalisé

Structure type pour un projet embarqué complet.

## Dossiers proposés

```
projet-custom/
├── README.md           # Ce fichier : objectif, build, flash
├── doc/                # Schémas, spécifications
├── bsp/                # Board support : GPIO, clock, init
├── drivers/            # Pilotes périphériques (UART, I2C, capteur…)
├── app/                # Logique applicative (tâches, commandes)
├── config/             # board_config.h, FreeRTOSConfig.h
├── lib/                # Libs externes (FreeRTOS, middleware)
├── tests/              # Scripts ou code de test
└── build/              # Généré par le build (obj, elf, bin)
```

## Étapes

1. Copier ce dossier et le renommer (ex. `mon-datalogger`).
2. Définir l’objectif du projet (une phrase) et les fonctionnalités (liste courte).
3. Choisir la cible (carte + MCU) et créer le projet (CubeMX ou Makefile/CMake).
4. Implémenter par couches : BSP → drivers → app.
5. Documenter le build (`make` ou IDE), le flash et l’usage (commandes UART, etc.).
6. Ajouter des tests (scripts UART, ou tests unitaires sur PC pour la logique pure).

## Références

- Cours 5.1 (architecture), 5.2 (tests/débogage), 5.3 (robustesse/sécurité).
