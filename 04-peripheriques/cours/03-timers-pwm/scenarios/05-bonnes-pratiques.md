# Scénario – Bonnes pratiques Timers et PWM

Pour la leçon [05 – Bonnes pratiques](../05-bonnes-pratiques.md).

---

## Scénario 1 : PWM et sifflement

Un PWM à **2 kHz** pilote une **LED** avec un fil long. On entend un **sifflement**.

**Questions** : Pourquoi (fréquence dans le domaine audible, vibration du circuit ou du fil) ? Quelle plage de fréquences est typiquement **audible** (1–20 kHz) ? Que faire pour l'éclairage LED (monter au-dessus, ex. 25 kHz, ou descendre en dessous, ex. 100 Hz) ?

---

## Scénario 2 : Capture et overflow

On mesure la **période** d'un signal avec un timer 16 bits (ARR = 65535). La période du signal à mesurer est de **100 ms**. La période du timer (1 tick) est **1 µs**.

**Questions** : Combien de **ticks** représentent 100 ms (100 000) ? Le compteur 16 bits peut-il contenir cette valeur (oui, 65535 max → **overflow**) ? Comment gérer (compter les overflows en ISR Update, ou augmenter ARR/prescaler pour allonger la période max) ?

---

**Réponse** : [../reponses/05-bonnes-pratiques.md](../reponses/05-bonnes-pratiques.md) · **Retour** : [Vue d'ensemble](../README.md)
