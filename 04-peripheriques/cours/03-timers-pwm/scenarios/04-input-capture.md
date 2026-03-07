# Scénario – Input capture

Pour la leçon [04 – Input capture](../04-input-capture.md).

---

## Scénario 1 : Largeur d'impulsion

On mesure la **largeur** d'une impulsion (temps entre front **montant** et front **descendant**) avec un timer. Capture au front montant → **T1 = 1000** ; capture au front descendant → **T2 = 3500**. La période du timer est **1 µs**.

**Questions** : Quelle est la **largeur** en ticks (T2 - T1) ? Quelle est la largeur en **secondes** ? Que faire si T2 < T1 (overflow du compteur entre les deux captures) ?

---

## Scénario 2 : Mesurer une période (fréquence)

On veut mesurer la **fréquence** d'un signal (ex. encodeur). On capture le compteur sur **deux fronts montants** consécutifs : **T1 = 0**, **T2 = 50000**. f_timer = 1 MHz (période 1 µs).

**Questions** : Quelle est la **période** du signal en secondes ? Quelle est la **fréquence** en Hz ? Où configurer le canal timer (mode capture, source = broche TIx, interruption sur capture) ?

---

**Réponse** : [../reponses/04-input-capture.md](../reponses/04-input-capture.md) · **Retour** : [Vue d'ensemble](../README.md)
