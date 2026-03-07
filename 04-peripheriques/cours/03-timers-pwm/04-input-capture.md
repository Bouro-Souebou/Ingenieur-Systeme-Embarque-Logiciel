# Leçon 4 – Input capture

## Objectif de la leçon

Utiliser un **canal timer en mode capture** : enregistrer la **valeur du compteur** sur un **front** (montant ou descendant) d'un signal d'entrée. Mesurer ainsi la **largeur d'impulsion** (deux captures : front montant puis descendant) ou la **période** (deux fronts montants consécutifs).

## 1. Principe

Le **canal** est configuré en **input capture** : la **broche** (TIx) est l'entrée. Sur un **front** (montant ou descendant, configurable), le **compteur** actuel est **copié** dans un registre **CCR** (ou registre de capture) et une **interruption** peut être générée. En lisant la valeur capturée à deux fronts, on obtient la **différence** = nombre de ticks entre les deux fronts = durée en unités de période du timer.

## 2. Largeur d'impulsion

- **Capture** sur front **montant** → valeur T1.
- **Capture** sur front **descendant** (même cycle ou cycle suivant selon la config) → valeur T2.
- **Largeur** = (T2 - T1) × période_timer (en secondes). Attention au **débordement** du compteur entre T1 et T2 : si le compteur a fait un overflow, ajouter (ARR+1) à la différence ou utiliser un compteur d'overflows.

## 3. Période (fréquence)

- **Capture** sur deux **fronts montants** consécutifs → T1 puis T2.
- **Période** = (T2 - T1) × période_timer ; **fréquence** = 1 / période.
Utile pour mesure de fréquence (encodeur, signal IR, capteur à impulsion).

## 4. Configuration

GPIO en **entrée** (alternate pour le timer) ; timer en mode **capture** sur le canal ; **source** de déclenchement = broche TIx ; **interruption** ou DMA sur événement capture. Consulter le Reference Manual pour les bits exacts (CCxS, ICx, polarité).

---

## Tester sa compréhension

→ [Scénario – Input capture](scenarios/04-input-capture.md) · [Réponse](reponses/04-input-capture.md)

---

**Suite** : [Leçon 5 – Bonnes pratiques](05-bonnes-pratiques.md)
