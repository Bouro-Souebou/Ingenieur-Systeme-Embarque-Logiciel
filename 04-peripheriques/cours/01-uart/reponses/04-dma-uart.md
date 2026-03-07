# Réponse – DMA avec UART

Voir [scénario](../scenarios/04-dma-uart.md).

---

## Réponse Scénario 1 : UART RX + DMA

**Source** : le **registre DR** de l'UART (adresse **fixe**). **Destination** : le **buffer en RAM** (adresse de départ ; **incrément** après chaque octet transféré).

**Incrément** : La source (DR) ne s'incrémente **pas** (toujours le même registre). La destination (RAM) s'incrémente pour remplir le buffer séquentiellement.

**Interruption fin de transfert** : Le DMA a copié les **128 octets** ; le buffer est **complet**. L'ISR peut : poser un **flag** pour qu'une tâche traite le buffer ; **envoyer** un message dans une queue ; ou **relancer** un nouveau transfert DMA (même buffer ou double buffering). L'ISR doit rester **courte** (pas de traitement lourd).

---

## Réponse Scénario 2 : Double buffering RX

**Double buffering** : Deux buffers **A** et **B**. Pendant que le DMA remplit **A**, le logiciel peut traiter **B** (déjà rempli) ; puis on inverse. Ainsi aucun octet n'est perdu pendant le traitement.

**Demi-transfert** : Sur certains MCU, une interruption **half-transfer** est générée quand le DMA a rempli **la moitié** du buffer (ex. 64 premiers octets sur 128). Le logiciel peut **traiter** cette première moitié pendant que le DMA remplit la seconde moitié. Évite une « fenêtre » où des octets arrivent alors que le buffer est plein et pas encore traité.

**Éviter les pertes** : Buffer suffisamment grand ; traiter (ou copier) les données **avant** que le prochain demi-buffer ou buffer soit plein ; ou utiliser deux buffers en ping-pong avec interruption fin + demi selon le MCU.

---

**Retour** : [Scénarios](../scenarios/README.md) · [Leçon 4](../04-dma-uart.md)
