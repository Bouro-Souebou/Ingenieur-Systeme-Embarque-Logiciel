# Scénario – Configurer une broche en sortie

Pour la leçon [03 – Configurer une broche en sortie](../03-configurer-sortie.md).

---

## Scénario 1 : CRL et broche PA5

On configure **PA5** en **sortie push-pull 50 MHz**. CRL configure les broches 0 à 7.

**Questions** : Quels bits de CRL concernent la broche 5 (bits 20 à 23) ? Que signifient mode (11 = 50 MHz) et configuration (00 = push-pull) ? Pourquoi effacer les 4 bits avant de les mettre à la nouvelle valeur ?

---

## Scénario 2 : Ordre d'initialisation

On configure **CRL** pour PA5 **avant** d'activer l'horloge du port. La LED ne réagit pas.

**Questions** : Quel est le bon ordre (1. RCC horloge, 2. CRL, 3. ODR/BSRR) ? Pourquoi l'horloge doit-elle être activée avant tout accès au port ?

---

**Réponse** : [../reponses/03-configurer-sortie.md](../reponses/03-configurer-sortie.md) · **Retour** : [Vue d'ensemble](../README.md)
