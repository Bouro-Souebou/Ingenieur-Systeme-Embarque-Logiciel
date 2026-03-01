# Cours – Module Périphériques

Les cours du module **04 – Périphériques** sont organisés en **sous-dossiers** : chaque thème est détaillé en plusieurs leçons progressives, adaptées aux **débutants** et réutilisables pour des **étudiants**.

## Structure des cours

| Dossier | Contenu | Leçons |
|---------|---------|--------|
| [**00-dma-principes**](00-dma-principes/README.md) | **Leçon commune** : principes du DMA (définition, paramètres, quand l'utiliser) | 1 |
| [**01-uart**](01-uart/README.md) | UART et communication série (config, polling, IT, DMA, RTOS) | 5 |
| [**02-spi-i2c**](02-spi-i2c/README.md) | SPI et I2C (config, échange, bonnes pratiques, comparaison) | 5 |
| [**03-timers-pwm**](03-timers-pwm/README.md) | Timers, PWM et capture (principe, SysTick, PWM, input capture) | 5 |
| [**04-adc-dma**](04-adc-dma/README.md) | ADC et DMA (principes, one-shot, continu/scan, DMA, bonnes pratiques) | 5 |

## Ordre recommandé

1. **UART** → debug et liaison série (base pour les TPs).
2. **SPI et I2C** → bus pour capteurs et mémoires.
3. **Timers et PWM** → génération de signaux et mesure de temps.
4. **ADC et DMA** → acquisition analogique.

**DMA** : la leçon [Principes du DMA](00-dma-principes/01-principes-dma.md) est **commune** ; il est conseillé de la lire **avant** les leçons [DMA avec UART](01-uart/04-dma-uart.md) et [DMA avec ADC](04-adc-dma/04-dma-adc.md), qui ne détaillent que les aspects spécifiques à chaque périphérique.

## Prérequis

Modules **02 – Microcontrôleurs** et **03 – RTOS**. Connaissances de base en électronique (niveaux logiques, pull-up) recommandées.
