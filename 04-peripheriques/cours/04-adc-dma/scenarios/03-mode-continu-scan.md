# Scénario – Mode continu et scan

Pour la leçon [03 – Mode continu et scan](../03-mode-continu-scan.md).

---

## Scénario 1 : Plusieurs canaux en round-robin

On veut lire **3 canaux** : température (canal 0), tension batterie (canal 1), courant (canal 2), dans cet ordre, en continu.

**Questions** : Quel **mode** activer (scan) ? Où configurer l'**ordre** des canaux (SQR1, SQR2, SQR3 ou équivalent) ? À la fin de la séquence de 3 conversions, quel événement (EOS) peut générer une interruption ? À quoi sert le **mode continu** (enchaîner la séquence sans relancer SWSTART) ?

---

## Scénario 2 : Trigger timer et DMA

On acquiert les 3 canaux à **100 Hz** (toutes les 10 ms). On utilise un **timer** pour déclencher l'ADC et le **DMA** pour stocker les 3 valeurs dans un buffer.

**Questions** : Quel **trigger** ADC utiliser (événement timer) ? Combien d'**éléments** le DMA transfère-t-il par « séquence » (3 : un par canal) ? Où le DMA écrit-il (buffer RAM, incrément après chaque EOC) ? Interruption en **fin de séquence** ou **fin de buffer** pour traiter les données ?

---

**Réponse** : [../reponses/03-mode-continu-scan.md](../reponses/03-mode-continu-scan.md) · **Retour** : [Vue d'ensemble](../README.md)
