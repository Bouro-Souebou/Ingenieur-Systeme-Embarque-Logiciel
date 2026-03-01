# Scénarios – Startup et interruptions

Pour le cours [Startup et interruptions](../README.md).

---

## Scénario 1 : L'ISR n'est jamais appelée

ISR déclarée (ex. `EXTI0_IRQHandler`), broche et EXTI configurés. Le bouton ne déclenche pas l’ISR. Quelle **étape d’activation** oublie-t-on souvent (côté contrôleur d’interruptions) ?

---

## Scénario 2 : HardFault au premier appui

Au premier appui sur le bouton, le processeur entre en **HardFault**. Causes classiques (table des vecteurs, nom ISR, stack) ? Où doit figurer l’adresse de l’ISR ?

---

**Réponses** : [../reponses/isr-activation.md](../reponses/isr-activation.md) · **Retour** : [Vue d’ensemble](../README.md)
