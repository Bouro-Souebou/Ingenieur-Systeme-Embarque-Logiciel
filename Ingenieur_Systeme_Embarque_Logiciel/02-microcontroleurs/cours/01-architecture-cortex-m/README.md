# Architecture ARM Cortex-M – Vue d'ensemble

Ce sous-dossier contient le cours **Architecture ARM Cortex-M**, découpé en leçons progressives pour des **débutants** en microcontrôleurs.

---

## Objectifs pédagogiques

À l'issue de ce cours, l'étudiant sera capable de :

- Expliquer ce qu'est un cœur **ARM Cortex-M** et pourquoi il est dominant en embarqué.
- Distinguer les **familles** (M0, M3, M4, M7) et leurs usages typiques.
- Décrire le **modèle de programmation** (registres R0–R15, stack, modes).
- Comprendre la **carte mémoire** (flash, RAM, périphériques mappés).
- Comprendre le rôle du **NVIC** et des **vecteurs d'interruption**.

---

## Ordre de lecture recommandé

| N° | Leçon | Contenu |
|----|--------|---------|
| 1 | [Vue d'ensemble du Cortex-M](01-vue-ensemble.md) | Cœur 32 bits RISC, Thumb, pas de MMU |
| 2 | [Familles Cortex-M](02-familles-cortex-m.md) | M0/M0+, M3, M4, M7 ; pipeline, FPU, MPU |
| 3 | [Modèle de programmation : registres](03-modele-programmation.md) | R0–R15, SP, LR, PC |
| 4 | [Mémoire et bus](04-memoire-et-bus.md) | Carte mémoire, flash, RAM, périphériques |
| 5 | [NVIC et vecteurs d'interruption](05-nvic-vecteurs.md) | Exceptions, IRQ, priorités, handlers |

---

## Public et prérequis

- **Public** : débutants (étudiants, autodidactes).
- **Prérequis** : avoir suivi le module **01 – Fondements** (C embarqué, bus, temps réel). Notions de base en électronique (tension, broche) sont un plus.

---

**Tester sa compréhension** : [Scénarios](scenarios/README.md) et [Réponses](reponses/README.md).

---

**Commencer par** : [01 – Vue d'ensemble du Cortex-M](01-vue-ensemble.md)
