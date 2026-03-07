# Scénario – PWM : fréquence et rapport cyclique

Pour la leçon [03 – PWM : fréquence et rapport cyclique](../03-pwm-frequence-rapport.md).

---

## Scénario 1 : Fréquence et période

Le timer a une fréquence **f_timer = 1 MHz** (après prescaler). On programme **ARR = 1999**.

**Questions** : Quelle est la **période** du cycle PWM en secondes ? Quelle est la **fréquence** du signal PWM en Hz ? Si on veut 25 kHz pour éviter le sifflement audible, quelle valeur d'ARR (approximative) avec la même f_timer ?

---

## Scénario 2 : Rapport cyclique et servo

Un **servomoteur** standard attend une impulsion de **1 ms** (0°) à **2 ms** (180°) sur une **période** de **20 ms** (50 Hz).

**Questions** : Quelle **fréquence** PWM (50 Hz) et quelle **période** en ticks si f_timer = 1 MHz (20000 ticks) ? Pour 1,5 ms (milieu), quelle valeur de **CCR** (1500 ticks) ? La broche doit être configurée en quoi (alternate function, canal timer en mode PWM) ?

---

**Réponse** : [../reponses/03-pwm-frequence-rapport.md](../reponses/03-pwm-frequence-rapport.md) · **Retour** : [Vue d'ensemble](../README.md)
