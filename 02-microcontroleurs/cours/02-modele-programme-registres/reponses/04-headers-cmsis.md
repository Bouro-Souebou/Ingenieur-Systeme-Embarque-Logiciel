# Réponse – Headers CMSIS et fabricant

Voir [scénario](../scenarios/04-headers-cmsis.md).

---

## Réponse Scénario 1 : Remplacer les adresses en dur

**Headers** : Ils définissent les **adresses de base** (GPIOA_BASE), des **structures** (GPIO_TypeDef avec champs CRL, CRH, IDR, ODR, BSRR aux bons offsets), et des **constantes** (noms de bits). On accède par **nom** au lieu d'adresses numériques.

**Équivalent** : `GPIOA->ODR |= (1u << 5);` avec `#define GPIOA ((GPIO_TypeDef *) GPIOA_BASE)`. Le header définit GPIO_TypeDef et GPIOA_BASE.

**CMSIS** : Couche **ARM** pour Cortex-M : noms des **exceptions** et **IRQ**, fonctions **NVIC** (NVIC_EnableIRQ, NVIC_SetPriority), **SysTick**, et structures communes. Les fabricants fournissent des packs qui **incluent** CMSIS et les définitions spécifiques à leur MCU.

---

## Réponse Scénario 2 : Constantes pour les bits

**Avantage** : **Lisibilité** (OD5 = Output Data bit 5), **cohérence** avec le Reference Manual et la doc du fabricant, **éviter les erreurs** (mauvais numéro de bit). Si le header change (autre MCU), les constantes suivent.

**Définition** : Dans le fichier **stm32f4xx.h** (ou stm32l4xx.h, etc.) du pack du fabricant : `#define GPIO_ODR_OD5 (1u << 5)` ou équivalent.

**__IO** : Macro fournie par le fabricant (ou CMSIS), en général définie comme **volatile** : les champs de la structure correspondent à des **registres** dont la valeur peut changer en dehors du programme (matériel).

---

**Retour** : [Scénarios](../scenarios/README.md) · [Leçon 4](../04-headers-cmsis.md)
