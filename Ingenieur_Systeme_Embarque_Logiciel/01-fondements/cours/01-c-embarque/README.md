# C pour l'embarqué – Vue d'ensemble

Ce sous-dossier contient le cours **C pour l'embarqué**, découpé en leçons courtes et progressives, destinées à des **débutants** en programmation embarquée.

---

## Objectifs pédagogiques

À l'issue de ce cours, l'étudiant sera capable de :

- Expliquer pourquoi le C est privilégié en embarqué et quelles contraintes il impose.
- Utiliser les types à taille fixe (`stdint.h`) et éviter les types ambigus (`int`, `long`).
- Comprendre et utiliser correctement le qualificateur **volatile**.
- Manipuler des registres matériels (accès bit à bit et champs de plusieurs bits).
- Accéder à des adresses mémoire fixes (périphériques) via des pointeurs.
- Maîtriser **const**, **static**, et les notions de stack/heap en contexte MCU.
- Identifier et éviter les pièges courants (comportement indéfini, overflow).

---

## Ordre de lecture recommandé

| N° | Leçon | Contenu |
|----|--------|---------|
| 1 | [Pourquoi le C en embarqué ?](01-pourquoi-le-c.md) | Contexte, contraintes matérielles, rôle du langage |
| 2 | [Types et stdint.h](02-types-et-stdint.md) | Tailles des types, types à taille fixe, bonnes pratiques |
| 3 | [Le qualificateur volatile](03-volatile.md) | Optimisations du compilateur, variables partagées, registres. *Notions ISR et DMA introduites brièvement (détails dans Temps réel et Périphériques).* |
| 4 | [Accès aux bits et aux champs](04-acces-bits.md) | Set/clear bit, masques, champs multi-bits |
| 5 | [Pointeurs et adresses mémoire](05-pointeurs-et-adresses.md) | Mémoire mappée, accès aux périphériques |
| 6 | [Const, static et mémoire (stack/heap)](06-const-static-memoire.md) | Lecture seule, visibilité, stack, heap |
| 7 | [Pièges et bonnes pratiques](07-pieges-et-bonnes-pratiques.md) | Comportement indéfini, résumé, checklist |

---

## Public et prérequis

- **Public** : débutants en systèmes embarqués (étudiants, reconversion, autodidactes).
- **Prérequis** : bases en programmation C (variables, boucles, fonctions, pointeurs simples). Des rappels sont inclus dans les leçons si besoin.

---

## Durée indicative

Environ **3 à 4 heures** de lecture et d'exercices pour couvrir l'ensemble. Les exercices pratiques du dossier `../tp/` complètent la formation.

---

**Commencer par** : [01 – Pourquoi le C en embarqué ?](01-pourquoi-le-c.md)
