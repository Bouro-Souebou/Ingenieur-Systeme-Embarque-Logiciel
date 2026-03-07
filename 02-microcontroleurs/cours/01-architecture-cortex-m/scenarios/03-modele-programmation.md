# Scénario – Modèle de programmation : registres

Pour la leçon [03 – Modèle de programmation : registres](../03-modele-programmation.md).

---

## Scénario 1 : SP et table des vecteurs

Au **reset**, le processeur charge une valeur dans le **Stack Pointer** (SP) puis saute à une adresse pour exécuter le premier code.

**Questions** : D'où vient la **valeur initiale du SP** (table des vecteurs, à quel offset) ? Pourquoi la pile doit-elle être initialisée avant toute utilisation ? Où se trouve cette table (flash) ?

---

## Scénario 2 : PC et débogage

Le programme entre en **HardFault**. Dans le débogueur, on affiche les registres du cœur.

**Questions** : Quel **registre** indique l'instruction qui a provoqué la faute (PC) ? À quoi sert le **Link Register** (LR) en situation normale ? En contexte d'interruption, LR contient-il une adresse de retour classique ?

---

**Réponse** : [../reponses/03-modele-programmation.md](../reponses/03-modele-programmation.md) · **Retour** : [Vue d'ensemble](../README.md)
