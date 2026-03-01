# Bus et protocoles numériques – Vue d'ensemble

Ce sous-dossier contient le cours **Bus et protocoles numériques**, découpé en leçons progressives pour des **débutants** en systèmes embarqués.

---

## Objectifs pédagogiques

À l'issue de ce cours, l'étudiant sera capable de :

- Comprendre la différence entre communication **série** et **parallèle**, et entre **synchrone** et **asynchrone**.
- Décrire le fonctionnement de l'**UART** (format de trame, paramètres, usage typique).
- Décrire le fonctionnement de **SPI** (rôle des fils, modes CPOL/CPHA, maître/esclave).
- Décrire le fonctionnement de **I2C** (SDA, SCL, adressage, séquence START/STOP/ACK).
- Lire un **schéma de signaux** (timing) et choisir le **bon protocole** selon l'application.

---

## Ordre de lecture recommandé

| N° | Leçon | Contenu |
|----|--------|---------|
| 1 | [Communication série : notions de base](01-communication-serie.md) | Série vs parallèle, synchrone vs asynchrone |
| 2 | [UART en détail](02-uart-en-detail.md) | Trame, baudrate, broches, usage |
| 3 | [SPI en détail](03-spi-en-detail.md) | Fils, modes, maître/esclave |
| 4 | [I2C en détail](04-i2c-en-detail.md) | Deux fils, adressage, séquences |
| 5 | [Comparaison et choix](05-comparaison-choix.md) | Tableau comparatif, bonnes pratiques |

---

## Public et prérequis

- **Public** : débutants (étudiants, autodidactes).
- **Prérequis** : avoir suivi le cours **C pour l'embarqué** (optionnel pour la théorie ; utile pour les exemples de code plus tard). Notions de base en électronique (tension, masse, niveau logique) sont un plus.

---

**Tester sa compréhension** : [Scénarios](scenarios/README.md) (UART, SPI/I2C, comparaison) et [Réponses](reponses/README.md).

---

**Commencer par** : [01 – Communication série : notions de base](01-communication-serie.md)
