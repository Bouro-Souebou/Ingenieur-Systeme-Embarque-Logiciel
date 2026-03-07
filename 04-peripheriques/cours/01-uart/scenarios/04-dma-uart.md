# Scénario – DMA avec UART

Pour la leçon [04 – DMA avec UART](../04-dma-uart.md).

---

## Scénario 1 : UART RX + DMA

On configure un transfert DMA pour recevoir **128 octets** : à chaque octet reçu par l'UART, le DMA copie le registre **DR** vers un buffer RAM.

**Questions** : Quelle est la **source** et la **destination** du transfert DMA ? La source s'incrémente-t-elle (non : toujours DR) ? À quoi sert l'**interruption** en fin de transfert (buffer plein) ? Que faire dans l'ISR (courte : flag, queue, relancer un transfert) ?

---

## Scénario 2 : Double buffering RX

À débit élevé, quand le DMA remplit le buffer, le logiciel doit le traiter ; pendant ce temps des octets peuvent continuer à arriver et être perdus.

**Questions** : Qu'est-ce que le **double buffering** (deux buffers A et B) ? À quoi sert l'interruption **demi-transfert** (half-transfer) sur certains MCU ? Comment éviter de perdre des données pendant le traitement d'un demi-buffer ?

---

**Réponse** : [../reponses/04-dma-uart.md](../reponses/04-dma-uart.md) · **Retour** : [Vue d'ensemble](../README.md)
