# Principes du DMA – Vue d'ensemble

Ce sous-dossier contient une **leçon commune** sur le **DMA** (Direct Memory Access), réutilisée avant les cours **UART** (leçon DMA) et **ADC et DMA**. Les principes généraux sont vus une seule fois ici ; les applications concrètes (UART, ADC) sont détaillées dans leurs cours respectifs.

---

## Objectif

À l'issue de cette leçon, l'étudiant sera capable de :

- Définir le **DMA** et expliquer son rôle (transfert sans CPU).
- Décrire les **paramètres** d'un transfert DMA : source, destination, déclencheur, nombre d'éléments, incrément d'adresse.
- Comprendre les **interruptions** fin de transfert et demi-transfert (double buffering).
- Savoir **quand** privilégier le DMA plutôt que le polling ou les interruptions.

---

## Leçon

| N° | Leçon | Contenu |
|----|--------|---------|
| 1 | [Principes du DMA](01-principes-dma.md) | Définition, paramètres, déclencheurs, interruptions, quand l'utiliser |

---

## Utilisation dans le module

- **Avant** [UART – DMA](../01-uart/04-dma-uart.md) et [ADC et DMA – DMA](../04-adc-dma/04-dma-adc.md) : lire cette leçon pour avoir les bases ; les leçons UART et ADC ne reprennent que les aspects **spécifiques** au périphérique.
- Le **glossaire** et la leçon **Fondements – volatile** font référence au DMA ; cette leçon en donne une vue complète.

---

**Commencer par** : [01 – Principes du DMA](01-principes-dma.md)
