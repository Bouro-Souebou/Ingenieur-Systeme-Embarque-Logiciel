# Scénario – Principes du DMA

Pour la leçon [01 – Principes du DMA](../01-principes-dma.md).

---

## Scénario 1 : Quand choisir le DMA ?

Une application reçoit un flux UART à **115200 baud** (quelques Ko/s) et doit en parallèle lire un **ADC sur 4 canaux** à **1 kHz** (4 échantillons par période).

**Questions** : Pourquoi le polling ou les seules interruptions peuvent-ils devenir limitants ? Quels avantages le DMA apporte-t-il pour l'UART et pour l'ADC (charge CPU, régularité) ?

---

## Scénario 2 : Paramètres d'un transfert DMA

On configure un transfert DMA pour remplir un **buffer RAM** de 256 octets à partir du **registre de réception UART** (un octet à chaque fois que l'UART reçoit).

**Questions** : Quelle est la **source** et la **destination** du transfert ? Le déclencheur est-il logiciel ou matériel ? Faut-il incrémenter la source et la destination après chaque transfert ? À quoi sert l'interruption « fin de transfert » ?

---

**Réponse** : [../reponses/01-principes-dma.md](../reponses/01-principes-dma.md) · **Retour** : [Vue d'ensemble](../README.md)
