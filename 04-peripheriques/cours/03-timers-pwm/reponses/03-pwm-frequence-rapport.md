# Réponse – PWM : fréquence et rapport cyclique

Voir [scénario](../scenarios/03-pwm-frequence-rapport.md).

---

## Réponse Scénario 1 : Fréquence et période

**Période** : (ARR+1) / f_timer = 2000 / 1 MHz = 2 ms. **Fréquence** = 500 Hz.

**25 kHz** : période = 40 µs. Avec f_timer = 1 MHz, ARR+1 = 40 donc ARR = 39.

---

## Réponse Scénario 2 : Rapport cyclique et servo

**Période** : 20 ms = 50 Hz. ARR = 19999 (20000 ticks à 1 µs).

**1,5 ms** : CCR = 1500. Broche en alternate function pour le canal timer ; canal en mode PWM (output compare).

---

**Retour** : [Scénarios](../scenarios/README.md) · [Leçon 3](../03-pwm-frequence-rapport.md)
