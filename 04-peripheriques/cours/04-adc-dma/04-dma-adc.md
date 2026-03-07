# Leçon 4 – DMA avec ADC

## Objectif de la leçon

Configurer le **DMA** pour transférer les **résultats** de l'ADC (registre DR) vers un **buffer** en RAM à chaque conversion (ou à chaque fin de séquence). Interruption en **fin de buffer** ou **demi-buffer** (double buffering) pour traiter les données sans perte.

**Prérequis** : [Principes du DMA](../../00-dma-principes/01-principes-dma.md) (paramètres de transfert, interruptions fin / demi-transfert).

---

## 1. Pourquoi DMA + ADC

Sans DMA, le CPU doit **lire** le registre DR après chaque conversion (polling ou ISR). À **haute fréquence** d'échantillonnage ou avec **plusieurs canaux**, on risque de **manquer** des échantillons ou de surcharger le CPU. Avec le **DMA** : à chaque **EOC** (End Of Conversion) ou **EOS** (End Of Sequence), le DMA copie **automatiquement** la valeur de DR vers l'adresse courante du buffer et incrémente l'adresse. Aucune intervention CPU pendant le transfert.

## 2. Configuration DMA

- **Source** : adresse du registre **ADC DR** (fixe).
- **Destination** : **buffer** en RAM (adresse incrémentée après chaque transfert).
- **Nombre** de transferts : taille du buffer (ex. 256 mots pour 256 échantillons).
- **Déclencheur** : **EOC** (ou EOS) de l'ADC.
- **Interruption** : en **fin de transfert** (buffer plein) ou **demi-transfert** (demi-buffer) pour double buffering.

En **double buffering** : on traite la première moitié du buffer pendant que le DMA remplit la seconde (interruption demi-transfert), puis on inverse. Ainsi pas de perte d'échantillon pendant le traitement.

## 3. Débit et taille de buffer

Le **débit** (échantillons/s) = fréquence de conversion × nombre de canaux en scan. S'assurer que le **traitement** (ou la copie) peut suivre : taille de buffer suffisante et interruption traitée assez vite. Sinon le buffer déborde (données écrasées) ou le DMA s'arrête.

---

## Tester sa compréhension

→ [Scénario – DMA avec ADC](scenarios/04-dma-adc.md) · [Réponse](reponses/04-dma-adc.md)

---

**Suite** : [Leçon 5 – Bonnes pratiques](05-bonnes-pratiques.md)
