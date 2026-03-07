# Réponse – Timer : principe

Voir [scénario](../scenarios/01-timer-principe.md).

---

## Réponse Scénario 1 : Fréquence du timer

**Fréquence** : f_timer = f_APB / (prescaler + 1) = 72 MHz / 72 = **1 MHz**. Chaque tick du compteur = 1 µs.

**Période overflow** : Compteur 0 à 65535 (65536 pas) ; overflow après 65536 ticks. Période = 65536 / 1 MHz = **65,536 ms** (environ 15,26 Hz).

---

## Réponse Scénario 2 : Comparaison et sortie

**Registre** : **CCR** (Capture/Compare Register) pour le canal utilisé. On met CCR = 1000.

**Compare match** : Quand compteur = CCR, le **comparateur** déclenche un **événement** : interruption possible, et **toggle** de la sortie (broche) si le canal est en mode output compare. La sortie peut être mise à 1 quand count < CCR, à 0 sinon (mode PWM).

**Base PWM** : En répétant le cycle avec **ARR** (reload), la sortie est à 1 pendant CCR ticks et à 0 pendant (ARR+1 - CCR) ticks → **rapport cyclique** = CCR/(ARR+1). C'est le PWM.

---

**Retour** : [Scénarios](../scenarios/README.md) · [Leçon 1](../01-timer-principe.md)
