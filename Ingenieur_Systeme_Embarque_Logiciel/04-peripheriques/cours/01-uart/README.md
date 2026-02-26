# UART et communication série – Vue d'ensemble

Ce sous-dossier contient le cours **UART et communication série** : configuration, envoi/réception en polling et en interruption, DMA, et intégration avec un RTOS.

---

## Objectifs pédagogiques

À l'issue de ce cours, l'étudiant sera capable de :

- **Configurer** un UART (baudrate, format, broches) et activer l'horloge du périphérique.
- **Envoyer et recevoir** des données en **polling** (simple, bloquant).
- Utiliser le **mode interruption** (TX et RX) pour ne pas bloquer le CPU.
- Comprendre l'usage du **DMA** avec l'UART (optionnel).
- **Intégrer** l'UART avec un RTOS (queue entre ISR RX et tâche de traitement).

---

## Ordre de lecture recommandé

| N° | Leçon | Contenu |
|----|--------|---------|
| 1 | [Paramètres et configuration](01-parametres-configuration.md) | Baudrate, format, broches, horloge |
| 2 | [Envoi et réception en polling](02-polling.md) | TXE, RXNE, send/recv byte |
| 3 | [Mode interruption](03-mode-interruption.md) | IT TX, IT RX, buffer circulaire |
| 4 | [DMA avec UART (optionnel)](04-dma-uart.md) | TX/RX DMA, double buffering |
| 5 | [Intégration RTOS](05-integration-rtos.md) | Queue ISR ↔ tâche, mutex TX |

---

## Public et prérequis

- **Public** : débutants (étudiants, autodidactes).
- **Prérequis** : modules **02 – Microcontrôleurs** et **03 – RTOS** (registres, ISR, queues). Cours **Fondements – Bus** (UART) recommandé.

---

**Commencer par** : [01 – Paramètres et configuration](01-parametres-configuration.md)
