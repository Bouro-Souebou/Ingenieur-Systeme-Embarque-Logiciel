# Scénario – Bonnes pratiques ADC

Pour la leçon [05 – Bonnes pratiques](../05-bonnes-pratiques.md).

---

## Scénario 1 : Mesure fausse et impédance

Un **capteur** avec une sortie à **haute impédance** (ex. 1 MΩ) est connecté directement à l'entrée ADC. La valeur lue varie beaucoup et semble incorrecte.

**Questions** : Pourquoi (condensateur d'échantillonnage de l'ADC chargé via une résistance élevée, temps de charge insuffisant) ? Que faire : **temps d'échantillonnage** plus long (registre SMP) ou **buffer** (ampli suiveur) entre capteur et ADC ?

---

## Scénario 2 : Bruit et moyennage

Les mesures ADC **fluctuent** de quelques LSB autour de la valeur attendue (bruit).

**Questions** : Quelles causes possibles (bruit alimentation, câblage, quantification) ? Comment **réduire** le bruit (filtrage Vref, condensateurs de découplage, **moyenne** de N échantillons) ? Quel inconvénient du moyennage (temps de réponse, latence) ?

---

**Réponse** : [../reponses/05-bonnes-pratiques.md](../reponses/05-bonnes-pratiques.md) · **Retour** : [Vue d'ensemble](../README.md)
