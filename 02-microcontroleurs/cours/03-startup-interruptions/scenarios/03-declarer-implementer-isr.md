# Scénario – Déclarer et implémenter une ISR

Pour la leçon [03 – Déclarer et implémenter une ISR](../03-declarer-implementer-isr.md).

---

## Scénario 1 : Nom et signature

On veut gérer l'interruption **EXTI ligne 0** (bouton sur PA0). Le fichier startup référence **EXTI0_IRQHandler**.

**Questions** : Quel **nom exact** doit avoir la fonction en C (casse, orthographe) ? Quelle **signature** (paramètres, type de retour) ? Pourquoi le linker « voit » notre fonction (il remplace le symbole Weak du startup) ?

---

## Scénario 2 : Acquittement et ISR courte

L'ISR EXTI0 met un flag à 1 mais ne fait rien d'autre. Après le premier appui, le processeur rappelle l'ISR en boucle et le programme ne sort plus de l'interruption.

**Questions** : Quelle **cause** probable (bit pending non effacé) ? Où acquitter (registre du périphérique, ex. EXTI->PR, écrire 1 pour clear) ? Que faire dans l'ISR et que faire **en dehors** (traitement lourd en tâche ou boucle principale) ?

---

**Réponse** : [../reponses/03-declarer-implementer-isr.md](../reponses/03-declarer-implementer-isr.md) · **Retour** : [Vue d'ensemble](../README.md)
