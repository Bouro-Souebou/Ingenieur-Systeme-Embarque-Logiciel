# Scénario – Conversion one-shot

Pour la leçon [02 – Conversion one-shot](../02-conversion-one-shot.md).

---

## Scénario 1 : Polling et EOC

Le code lance une conversion avec **SWSTART**, puis entre dans une boucle `while (!(ADC->SR & ADC_SR_EOC));` pour attendre la fin. Ensuite il lit **DR**.

**Questions** : À quoi sert le flag **EOC** (End Of Conversion) ? Que risque-t-on si on lit **DR** avant que EOC soit à 1 (valeur précédente ou indéfinie) ? Pourquoi un **timeout** dans la boucle est recommandé (ADC bloqué, capteur déconnecté) ?

---

## Scénario 2 : Mode interruption

On active l'**interruption EOC** et dans l'ISR on lit **DR** et on écrit la valeur dans une variable globale.

**Questions** : Pourquoi l'ISR doit rester **courte** (lire DR, stocker ou envoyer en queue) ? Que faire si une tâche RTOS doit utiliser la valeur (queue, notification) ? Faut-il **clear** EOC après la lecture (selon le MCU : souvent automatique à la lecture de DR) ?

---

**Réponse** : [../reponses/02-conversion-one-shot.md](../reponses/02-conversion-one-shot.md) · **Retour** : [Vue d'ensemble](../README.md)
