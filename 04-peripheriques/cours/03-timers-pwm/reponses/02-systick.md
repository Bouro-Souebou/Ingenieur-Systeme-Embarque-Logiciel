# Réponse – SysTick

Voir [scénario](../scenarios/02-systick.md).

---

## Réponse Scénario 1 : Configurer le tick FreeRTOS

**Reload** : reload = (48e6 / 1000) - 1 = **47999**. Le compteur démarre à 47999, décrémente à chaque cycle CPU ; à **0**, une **interruption** SysTick est générée et le compteur est **rechargé** à 47999. Ainsi une IRQ toutes les 1 ms → tick 1 kHz.

---

## Réponse Scénario 2 : Réutiliser SysTick pour un délai

**Risque** : **FreeRTOS** utilise le SysTick pour son **tick** (vTaskDelay, time slicing). Si on le reconfigure pour un autre usage, l'OS ne reçoit plus ses ticks → **vTaskDelay** ne se débloque plus, l'**ordonnanceur** ne tourne plus correctement → système **bloqué**.

**Alternative** : Utiliser un **timer périphérique** (TIM2, TIM3, etc.) pour le délai ou toute autre fonction applicative. Le SysTick reste dédié au RTOS.

---

**Retour** : [Scénarios](../scenarios/README.md) · [Leçon 2](../02-systick.md)
