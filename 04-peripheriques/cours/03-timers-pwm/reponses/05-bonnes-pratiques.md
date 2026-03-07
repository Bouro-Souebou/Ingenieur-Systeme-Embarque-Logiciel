# Réponse – Bonnes pratiques Timers et PWM

Voir [scénario](../scenarios/05-bonnes-pratiques.md).

---

## Réponse Scénario 1 : PWM et sifflement

**Cause** : **2 kHz** est dans le domaine **audible** (environ 20 Hz – 20 kHz). Le circuit (condensateurs, inductances, fil) peut **vibrer** et émettre un son.

**Plage audible** : Typiquement **1–20 kHz** (selon l’âge et l’environnement).

**LED** : Utiliser une fréquence **au-dessus** de l’audible (ex. **25 kHz**) pour éviter le sifflement ; ou **en dessous** (ex. 100 Hz) si le scintillement n’est pas gênant. Filtrer (RC) si on veut une tension continue pour la LED.

---

## Réponse Scénario 2 : Capture et overflow

**100 ms** = 100 000 µs → **100 000 ticks** si période = 1 µs. Compteur 16 bits : **max 65535** → **overflow** certain (au moins une fois).

**Gérer** : (1) **Compter les overflows** : en ISR **Update** (overflow), incrémenter un compteur ; à la deuxième capture, période = (T2 - T1) + n_overflows × (ARR+1). (2) **Augmenter la période** : prescaler plus grand (ex. 10) pour que 100 ms tienne dans 65535 ticks ; ou timer 32 bits si disponible.

---

**Retour** : [Scénarios](../scenarios/README.md) · [Leçon 5](../05-bonnes-pratiques.md)
