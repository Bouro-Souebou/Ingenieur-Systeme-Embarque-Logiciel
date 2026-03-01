# Formation Ingénieur Électronique Embarqué Logiciel

Parcours progressif pour devenir expert en systèmes embarqués (logiciel et interfaces électroniques).

## 🎯 Objectifs

- Maîtriser les **fondements** (C, électronique numérique, bus, temps réel).
- Programmer des **microcontrôleurs** (ARM Cortex-M, registres, interruptions).
- Utiliser un **RTOS** (FreeRTOS) et les bonnes pratiques.
- Piloter **périphériques** (UART, SPI, I2C, PWM, ADC, DMA).
- Concevoir des **projets complets** (architecture, tests, débogage).

## 📁 Organisation des dossiers

| Dossier | Contenu | Niveau |
|---------|---------|--------|
| `01-fondements/` | C embarqué, bus, notions temps réel | Débutant |
| `02-microcontroleurs/` | ARM Cortex-M, registres, startup, interruptions | Intermédiaire |
| `03-rtos/` | FreeRTOS, tâches, synchronisation, mémoire | Intermédiaire |
| `04-peripheriques/` | UART, SPI, I2C, PWM, ADC, DMA, timers | Avancé |
| `05-projets-avances/` | Projets complets, architecture, CI, tests | Expert |
| `ressources/` | Références, datasheets, liens, glossaire | — |

## 🗓 Plan de progression recommandé

1. **Semaines 1–4** : `01-fondements` (cours + exercices + mini-projets).
2. **Semaines 5–8** : `02-microcontroleurs` (cible : STM32 ou équivalent).
3. **Semaines 9–12** : `03-rtos` (FreeRTOS sur la même cible).
4. **Semaines 13–18** : `04-peripheriques` (un périphérique par semaine + TP).
5. **À partir de la semaine 19** : `05-projets-avances` (projets au choix).

## 📚 Comment utiliser cette formation

- Lire le **cours** (`.md`) de chaque module avant les TPs.
- Faire les **exercices** et **applications pratiques** dans l’ordre.
- Consulter `ressources/` pour approfondir (datasheets, normes, outils).
- Chaque module se termine par un **mini-projet** ou une **évaluation** pour valider le niveau.

## 🛠 Prérequis techniques

- Bases en **programmation** (variables, boucles, fonctions).
- Notions de **circuits** (tension, courant, masse) recommandées.
- **Matériel** conseillé pour la pratique : carte à base STM32 (ex. Nucleo) ou équivalent ARM Cortex-M.
- **Logiciels** : IDE (STM32CubeIDE ou VS Code + arm-none-eabi), oscilloscope/logic analyzer si possible.

---

*Dernière mise à jour : 2025*
