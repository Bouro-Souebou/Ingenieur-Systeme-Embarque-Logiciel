# Réponse – Input capture

Voir [scénario](../scenarios/04-input-capture.md).

---

## Réponse Scénario 1 : Largeur d'impulsion

**Largeur en ticks** : T2 - T1 = 3500 - 1000 = **2500** ticks.

**Largeur en secondes** : 2500 × 1 µs = **2,5 ms**.

**Overflow** : Si T2 < T1, le compteur a dépassé ARR entre les deux captures. Il faut **ajouter (ARR+1)** à (T2 - T1), ou **compter les overflows** (ISR Update) et faire : largeur = (T2 - T1) + n_overflows × (ARR+1).

---

## Réponse Scénario 2 : Mesurer une période (fréquence)

**Période** : (T2 - T1) × 1 µs = 50000 µs = **50 ms**. **Fréquence** = 1/0,05 = **20 Hz**.

**Configuration** : Canal en **input capture** ; **source** = broche TIx (broche GPIO en entrée, alternate pour le timer) ; **polarité** = front montant (ou les deux si deux captures). **Interruption** sur événement capture pour lire le registre CCR (valeur capturée). Pour la période : capturer à deux fronts montants, différence = période en ticks.

---

**Retour** : [Scénarios](../scenarios/README.md) · [Leçon 4](../04-input-capture.md)
