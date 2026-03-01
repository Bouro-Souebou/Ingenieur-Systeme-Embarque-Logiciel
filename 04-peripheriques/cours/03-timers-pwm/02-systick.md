# Leçon 2 – SysTick

## Objectif de la leçon

Connaître le **SysTick** : timer 24 bits **intégré au cœur** ARM Cortex-M, souvent utilisé par **FreeRTOS** comme source de tick. Ne pas le réutiliser en conflit avec le RTOS.

## 1. Rôle du SysTick

Le **SysTick** est un timer **cœur** (pas un périphérique du fabricant). Il est simple (compteur 24 bits, une valeur de reload, une interruption). Il sert souvent de **base de temps** pour l'OS : à chaque overflow (ou quand le compteur atteint 0 en mode down), une **interruption** SysTick est générée. FreeRTOS utilise cette interruption pour incrémenter son **tick** et réveiller les tâches en attente de **vTaskDelay**.

## 2. Configuration typique

- **Reload value** = (freq_cpu / freq_tick_souhaitee) - 1. Ex. CPU 72 MHz, tick 1 kHz → reload = 71999.
- **Activer** le compteur et l'**interruption** SysTick.
- Le compteur **décrémente** de la valeur de reload jusqu'à 0, génère l'IRQ, recharge la valeur, et recommence.

## 3. Ne pas le réutiliser

Si ton projet utilise **FreeRTOS** (ou un autre RTOS qui prend le SysTick), **ne pas** reconfigurer le SysTick pour un autre usage (ex. délai custom) sans désactiver le RTOS. Sinon, l'ordonnanceur ne reçoit plus ses ticks et le système se bloque. Pour des timers applicatifs (PWM, capture, délais), utiliser les **timers périphériques** (TIM1, TIM2, etc.) du MCU.

**Suite** : [Leçon 3 – PWM : fréquence et rapport cyclique](03-pwm-frequence-rapport.md)
