# Réponses – NVIC et vecteurs

Voir [scénarios](../scenarios/nvic-vecteurs.md).

---

## Scénario 1 : Priorité

**Réponse** : Oui. Priorité 2 (timer) est **plus élevée** que 5 (UART). Le processeur va **suspendre** l’ISR UART, sauvegarder le contexte, et exécuter l’ISR du timer. À la fin de l’ISR timer, il reprendra l’ISR UART. Règle : plus le **nombre** de priorité est **petit**, plus la priorité est **élevée**.

---

## Scénario 2 : Table des vecteurs

**Réponse** : **Offset 0** = valeur initiale du **SP** (stack pointer) ; **offset 4** = adresse du **Reset_Handler**. Ensuite viennent NMI, HardFault, puis les IRQ fabricant. La table est fournie par le **fichier startup** (`.s`) du fabricant ou générée par CubeMX ; ce fichier définit les symboles des handlers (souvent en **weak** pour que votre code les remplace).

---

**Retour** : [Scénarios](../scenarios/README.md) · [Architecture Cortex-M](../README.md)
