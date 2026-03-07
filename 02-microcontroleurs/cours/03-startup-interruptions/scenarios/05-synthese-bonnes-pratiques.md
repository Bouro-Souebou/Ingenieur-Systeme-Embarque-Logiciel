# Scénario – Synthèse et bonnes pratiques

Pour la leçon [05 – Synthèse et bonnes pratiques](../05-synthese-bonnes-pratiques.md).

---

## Scénario 1 : Checklist interruptions

Avant de tester une nouvelle ISR, on veut vérifier la chaîne complète.

**Questions** : Quelles **étapes** côté logiciel (handler au bon nom, acquittement, activation dans le périphérique + NVIC) ? Pourquoi déclarer les **variables partagées** avec l'ISR en **volatile** (ou utiliser queue/sémaphore en RTOS) ? Que risque-t-on si l'ISR est **trop longue** (latence, perte de données) ?

---

## Scénario 2 : Piège « nom incorrect »

L'ISR est implémentée en C sous le nom **Exti0_IRQHandler** (E majuscule, i minuscule). Le bouton ne déclenche jamais l'ISR.

**Questions** : Pourquoi (le startup attend **EXTI0_IRQHandler**, casse différente) ? Quelle **version** est alors utilisée (le Weak du startup, souvent boucle infinie ou vide) ? Comment vérifier le nom exact (fichier startup, Reference Manual) ?

---

**Réponse** : [../reponses/05-synthese-bonnes-pratiques.md](../reponses/05-synthese-bonnes-pratiques.md) · **Retour** : [Vue d'ensemble](../README.md)
