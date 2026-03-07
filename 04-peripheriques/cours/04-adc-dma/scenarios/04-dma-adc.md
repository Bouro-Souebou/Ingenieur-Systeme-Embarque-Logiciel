# Scénario – DMA avec ADC

Pour la leçon [04 – DMA avec ADC](../04-dma-adc.md).

---

## Scénario 1 : Source et destination du transfert

On configure le DMA pour stocker **64 conversions** ADC (un canal) dans un buffer **uint16_t buf[64]**.

**Questions** : Quelle est la **source** du DMA (registre ADC DR, adresse fixe) ? La **destination** (buffer RAM) : faut-il **incrémenter** l'adresse après chaque transfert (oui) ? Quel est le **déclencheur** (EOC : à chaque conversion terminée) ? Quelle **taille** d'élément (16 bits pour ADC 12 bits) ?

---

## Scénario 2 : Double buffering

À 10 kHz d'échantillonnage, le buffer de 256 échantillons est rempli en 25,6 ms. Le traitement (FFT, envoi) prend 20 ms. Sans précaution, des données peuvent être écrasées.

**Questions** : Qu'est-ce que le **double buffering** (deux moitiés : pendant que le DMA remplit la seconde, le CPU traite la première) ? À quoi sert l'interruption **demi-transfert** (half-transfer) ? Comment éviter d'écraser des données (traiter avant que le DMA n'ait rempli la moitié suivante) ?

---

**Réponse** : [../reponses/04-dma-adc.md](../reponses/04-dma-adc.md) · **Retour** : [Vue d'ensemble](../README.md)
