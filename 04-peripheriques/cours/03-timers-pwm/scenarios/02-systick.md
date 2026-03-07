# Scénario – SysTick

Pour la leçon [02 – SysTick](../02-systick.md).

---

## Scénario 1 : Configurer le tick FreeRTOS

Le CPU tourne à **48 MHz**. On veut un **tick** FreeRTOS à **1 kHz** (1 ms).

**Questions** : Quelle valeur de **reload** SysTick faut-il utiliser (formule : freq_cpu / freq_tick - 1) ? Le compteur SysTick **décrémente** de cette valeur jusqu'à 0 ; que se passe-t-il à 0 (interruption, rechargement) ?

---

## Scénario 2 : Réutiliser SysTick pour un délai

Le développeur veut un **délai logiciel** de 1 ms et configure le SysTick pour générer une interruption toutes les 1 ms, sans utiliser FreeRTOS pour ce délai. Le projet utilise **FreeRTOS** par ailleurs.

**Questions** : Quel risque (FreeRTOS utilise déjà SysTick pour son tick) ? Que se passe-t-il pour vTaskDelay et l'ordonnanceur si on change le SysTick ? Quelle alternative pour un délai ou un timer applicatif (timers périphériques TIMx) ?

---

**Réponse** : [../reponses/02-systick.md](../reponses/02-systick.md) · **Retour** : [Vue d'ensemble](../README.md)
