# Startup, reset et vecteurs d'interruption – Vue d'ensemble

Ce sous-dossier contient le cours **Startup, reset et vecteurs d'interruption** : ce qui se passe au démarrage du MCU, le fichier startup, et comment déclarer et utiliser des ISR.

---

## Objectifs pédagogiques

À l'issue de ce cours, l'étudiant sera capable de :

- Décrire la **séquence au reset** (SP, PC, Reset_Handler, main).
- Comprendre le rôle du **fichier startup** (table des vecteurs, initialisation .data/.bss).
- **Déclarer et implémenter** une ISR en C (nom, acquittement, règle « ISR courte »).
- **Activer** une interruption (configuration du périphérique + NVIC).

---

## Ordre de lecture recommandé

| N° | Leçon | Contenu |
|----|--------|---------|
| 1 | [Séquence au reset](01-sequence-reset.md) | SP, PC, table des vecteurs, Reset_Handler |
| 2 | [Le fichier startup](02-fichier-startup.md) | Table des vecteurs, .data/.bss, weak handlers |
| 3 | [Déclarer et implémenter une ISR](03-declarer-implementer-isr.md) | Nom, signature, acquittement, bonnes pratiques |
| 4 | [Activer une interruption](04-activer-interruption.md) | Config périphérique, NVIC_EnableIRQ, priorité |
| 5 | [Synthèse et bonnes pratiques](05-synthese-bonnes-pratiques.md) | Checklist, pièges, suite RTOS |

---

## Public et prérequis

- **Public** : débutants (étudiants, autodidactes).
- **Prérequis** : cours **01 – Architecture Cortex-M** (NVIC, vecteurs) et **02 – Modèle programme et registres** (accès aux registres).

---

**Tester sa compréhension** : [Scénarios](scenarios/README.md) et [Réponses](reponses/README.md).

---

**Commencer par** : [01 – Séquence au reset](01-sequence-reset.md)
