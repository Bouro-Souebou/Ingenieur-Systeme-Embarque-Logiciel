# 04 – Périphériques

Mise en œuvre des blocs matériels courants : UART, SPI, I2C, PWM, ADC, DMA, timers.  
Les cours sont **détaillés en leçons progressives** dans des sous-dossiers, destinés aux **débutants** et utilisables pour des **étudiants**.

## Contenu des cours

Les cours se trouvent dans le dossier **[cours/](cours/)**. Chaque thème est découpé en plusieurs leçons (sous-dossiers) :

| Thème | Dossier | Description |
|-------|---------|-------------|
| **UART** | [cours/01-uart/](cours/01-uart/README.md) | 5 leçons : config, polling, interruption, DMA, RTOS |
| **SPI et I2C** | [cours/02-spi-i2c/](cours/02-spi-i2c/README.md) | 5 leçons : SPI config/échange, bonnes pratiques, I2C config/transactions, erreurs, comparaison |
| **Timers, PWM et capture** | [cours/03-timers-pwm/](cours/03-timers-pwm/README.md) | 5 leçons : timer, SysTick, PWM, input capture, bonnes pratiques |
| **ADC et DMA** | [cours/04-adc-dma/](cours/04-adc-dma/README.md) | 5 leçons : principes ADC, one-shot, continu/scan, DMA, bonnes pratiques |

→ **Index complet** : [cours/README.md](cours/README.md)

## Applications pratiques

- **tp/** : un TP par périphérique (terminal UART, capteur I2C/SPI, moteur PWM, acquisition ADC).
- **projet/** : système avec plusieurs périphériques (ex. datalogger, contrôle moteur).

## Prérequis

Modules **02** et **03** (MCU + RTOS). Connaissances de base en électronique (niveaux logiques, pull-up/pull-down).
