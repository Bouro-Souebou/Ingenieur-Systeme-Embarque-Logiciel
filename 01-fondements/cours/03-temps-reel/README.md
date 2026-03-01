# Temps réel et contraintes – Vue d'ensemble

Ce sous-dossier contient le cours **Temps réel et contraintes**, découpé en leçons progressives pour des **débutants** en systèmes embarqués.

---

## Objectifs pédagogiques

À l'issue de ce cours, l'étudiant sera capable de :

- Définir un **système temps réel** et distinguer **temps réel dur** et **temps réel mou**.
- Comprendre les notions de **latence**, **jitter**, **déterminisme** et **réactivité**.
- Expliquer le rôle des **interruptions** et la règle des **ISR courtes**.
- Comparer **boucle principale** (super-loop) et **RTOS** pour structurer une application.

---

## Ordre de lecture recommandé

| N° | Leçon | Contenu |
|----|--------|---------|
| 1 | [Qu'est-ce que le temps réel ?](01-definition-temps-reel.md) | Définition, temps réel dur / mou |
| 2 | [Latence, jitter et déterminisme](02-latence-jitter-determinisme.md) | Délais, reproductibilité, WCET |
| 3 | [Interruptions et réactivité](03-interruptions-reactivite.md) | ISR, priorité, sections critiques |
| 4 | [Boucle principale vs RTOS](04-boucle-vs-rtos.md) | Super-loop, tâches, ordonnancement |
| 5 | [Contraintes à garder en tête](05-contraintes-synthese.md) | Stack, ressources partagées, synthèse |

**Tester sa compréhension** : [Scénarios](scenarios/README.md) (questions) et [Réponses](reponses/README.md) (analyse, solution, pièges). Une entrée par leçon : définition temps réel, latence/jitter/déterminisme, interruptions, boucle vs RTOS, contraintes.

---

## Public et prérequis

- **Public** : débutants (étudiants, autodidactes).
- **Prérequis** : avoir vu les bases du C embarqué et les bus (pour le contexte) ; pas obligatoire pour la théorie.

---

**Commencer par** : [01 – Qu'est-ce que le temps réel ?](01-definition-temps-reel.md)
