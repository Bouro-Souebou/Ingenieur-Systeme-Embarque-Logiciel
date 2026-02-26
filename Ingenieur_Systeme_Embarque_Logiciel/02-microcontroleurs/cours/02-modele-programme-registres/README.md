# Modèle programme et registres – Vue d'ensemble

Ce sous-dossier contient le cours **Modèle programme et registres** : accès aux registres des périphériques en C, avec exemples GPIO et utilisation des headers du fabricant.

---

## Objectifs pédagogiques

À l'issue de ce cours, l'étudiant sera capable de :

- Lire et écrire des **registres** de périphériques à partir de leur adresse (pointeurs `volatile`).
- Comprendre le **layout** d'un registre (champs de configuration en bits).
- Configurer un **GPIO** (mode, vitesse, type) et piloter une sortie (ODR, BSRR).
- Utiliser les **headers CMSIS** ou du fabricant pour les noms de registres et de bits.
- Modifier un **champ** de plusieurs bits sans toucher aux autres (lecture–masquage–écriture).

---

## Ordre de lecture recommandé

| N° | Leçon | Contenu |
|----|--------|---------|
| 1 | [Accès aux registres en C](01-acces-registres-c.md) | Adresses, pointeurs volatile, macros |
| 2 | [Exemple : le bloc GPIO](02-exemple-gpio.md) | CRL/CRH, IDR, ODR, BSRR |
| 3 | [Configurer une broche en sortie](03-configurer-sortie.md) | Mode, vitesse, push-pull ; exemple PA5 |
| 4 | [Headers CMSIS et fabricant](04-headers-cmsis.md) | Structures, noms de registres, GPIOA->ODR |
| 5 | [Champs multi-bits et bonnes pratiques](05-champs-bonnes-pratiques.md) | Masques, BSRR, conventions |

---

## Public et prérequis

- **Public** : débutants (étudiants, autodidactes).
- **Prérequis** : module **01 – Fondements** (C embarqué : volatile, bits, pointeurs) et cours **01 – Architecture Cortex-M** (carte mémoire, périphériques mappés).

---

**Commencer par** : [01 – Accès aux registres en C](01-acces-registres-c.md)
