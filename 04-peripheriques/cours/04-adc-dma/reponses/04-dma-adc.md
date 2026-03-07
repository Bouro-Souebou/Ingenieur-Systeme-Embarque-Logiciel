# Réponse – DMA avec ADC

Voir [scénario](../scenarios/04-dma-adc.md).

---

## Réponse Scénario 1 : Source et destination

**Source** : Adresse du **registre ADC DR** (fixe) ; pas d'incrément. **Destination** : **buf** en RAM ; **incrément** après chaque transfert (un mot 16 bits par conversion).

**Déclencheur** : **EOC** (End Of Conversion) : à chaque fois que l'ADC écrit dans DR, le DMA effectue un transfert. **Nombre** : 64 transferts. **Taille** élément : 16 bits (half-word) pour ADC 12 bits (résultat aligné dans un mot 16 bits).

---

## Réponse Scénario 2 : Double buffering

**Double buffering** : Buffer divisé en deux **moitiés**. Pendant que le DMA remplit la **seconde** moitié, le CPU **traite** la première (FFT, envoi). À l'interruption **demi-transfert**, on traite la première moitié ; à l'interruption **fin de transfert**, on traite la seconde. Puis on relance le DMA (ou mode circulaire selon le MCU).

**Éviter écrasement** : Traiter les données **avant** que le DMA n'ait rempli à nouveau la même zone. Avec demi-transfert, on a « jusqu'à la moitié du buffer » de temps pour traiter l'autre moitié.

---

**Retour** : [Scénarios](../scenarios/README.md) · [Leçon 4](../04-dma-adc.md)
