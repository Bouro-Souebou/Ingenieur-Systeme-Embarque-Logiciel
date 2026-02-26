# Leçon 4 – DMA avec UART (optionnel)

## Objectif de la leçon

Comprendre l'usage du **DMA** avec l'UART : transfert des octets à envoyer de la RAM vers le registre DR (TX) et des octets reçus du registre DR vers la RAM (RX) **sans intervention** du CPU. Réduit la charge CPU et le jitter pour les gros volumes.

**Prérequis** : avoir vu les [Principes du DMA](../00-dma-principes/01-principes-dma.md) (définition, source/destination/déclencheur, interruptions).

---

## 1. UART TX + DMA

- **Source** : un **buffer** en RAM contenant les octets à envoyer.
- **Destination** : le registre **DR** de l'UART (adresse fixe).
- **Déclencheur** : demande du périphérique UART (TX empty) ; à chaque octet envoyé, le DMA envoie le suivant.
- **Fin de transfert** : interruption DMA (ou UART) pour signaler que tout a été envoyé ; on peut alors préparer le prochain message ou désactiver le DMA.

Avantage : la CPU n'a pas à écrire octet par octet ; elle remplit un buffer, lance le transfert DMA, et peut faire autre chose pendant l'envoi.

---

## 2. UART RX + DMA

- **Source** : le registre **DR** de l'UART.
- **Destination** : un **buffer** en RAM (incrément d'adresse à chaque réception).
- **Déclencheur** : à chaque **réception** d'octet (RXNE), le DMA copie DR vers la RAM.
- **Fin de transfert** : interruption quand le buffer est **rempli** (ou **demi-buffer** en double buffering).

Avantage : aucun octet perdu tant que le buffer ne déborde pas ; charge CPU minimale. Pour un débit élevé, buffer suffisamment grand et/ou double buffering avec interruption à mi-parcours.

---

## 3. Double buffering (optionnel)

Pour le **RX** : deux buffers A et B. Le DMA remplit A ; à **mi-parcours** (ou à la fin), une interruption signale que A est prêt ; le logiciel **traite** A pendant que le DMA remplit B, puis on inverse. La configuration dépend du MCU (mode circulaire avec demi-transfer interrupt, etc.).

---

## Points clés à retenir

- **UART TX + DMA** : buffer RAM → registre DR ; **UART RX + DMA** : DR → buffer RAM ; déclencheur = événement UART (TX empty / RXNE) ; interruption en **fin de transfert** (ou demi-buffer).
- Utile pour **gros volumes** ou **débit soutenu** ; pour des échanges légers, le mode **interruption** suffit souvent. Rappel : [Principes du DMA](../00-dma-principes/01-principes-dma.md).

---

**Suite** : [Leçon 5 – Intégration RTOS](05-integration-rtos.md)
