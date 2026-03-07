# Scénario – Timer : principe

Pour la leçon [01 – Timer : principe](../01-timer-principe.md).

---

## Scénario 1 : Fréquence du timer

L'horloge du bus APB qui alimente le timer est à **72 MHz**. Le prescaler du timer est réglé à **71** (valeur programmée 71).

**Questions** : Quelle est la **fréquence** du compteur (f_timer) après le prescaler ? Si le compteur est 16 bits (0 à 65535) en mode **up**, quelle est la **période** d'un cycle complet (overflow) en secondes ?

---

## Scénario 2 : Comparaison et sortie

On veut qu'une **sortie** (broche du timer) passe à 1 quand le compteur atteint **1000** et repasse à 0 au **overflow** (reload à 0). Le reste du temps elle est à 0.

**Questions** : Quel registre du timer contient la valeur de **comparaison** (CCR) ? Que se passe-t-il au moment où compteur = CCR (événement compare match) ? En quoi cela est la base du **PWM** (en répétant le cycle avec ARR) ?

---

**Réponse** : [../reponses/01-timer-principe.md](../reponses/01-timer-principe.md) · **Retour** : [Vue d'ensemble](../README.md)
