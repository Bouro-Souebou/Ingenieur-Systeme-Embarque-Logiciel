# Scénario – Dimensionnement de la stack

Pour la leçon [05 – Dimensionnement stack](../05-dimensionnement-stack.md).

---

## Scénario 1 : HardFault après plusieurs heures

En production, après plusieurs heures, le MCU entre en **HardFault**. configCHECK_FOR_STACK_OVERFLOW était à 0.

**Questions** : Cause probable ? Comment détecter un overflow (config, hook) ? Comment dimensionner et vérifier (high water mark) ?

---

## Scénario 2 : Stack trop grande « au cas où »

Pour « être tranquille », le développeur donne **2048 words** (8 Ko) à chaque tâche. Le MCU a 32 Ko de RAM ; avec 5 tâches, la RAM est saturée.

**Questions** : Quel compromis (taille vs stabilité) ? Comment choisir une taille raisonnable (estimer appels + locales, utiliser uxTaskGetStackHighWaterMark après tests) ?

---

**Réponse** : [../reponses/05-dimensionnement-stack.md](../reponses/05-dimensionnement-stack.md) · **Retour** : [Vue d'ensemble](../README.md)
