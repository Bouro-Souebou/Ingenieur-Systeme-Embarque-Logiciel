# Scénario – Headers CMSIS et fabricant

Pour la leçon [04 – Headers CMSIS et fabricant](../04-headers-cmsis.md).

---

## Scénario 1 : Remplacer les adresses

Le code contient `REG(0x4001080C) |= (1u << 5);`. On veut le rendre lisible.

**Questions** : Que fournissent les headers du fabricant ? Exemple avec structure GPIO_TypeDef et GPIOA->ODR ? À quoi sert CMSIS ?

---

## Scénario 2 : Constantes pour les bits

On écrit `GPIOA->ODR |= (1u << 5);`. Le fabricant fournit **GPIO_ODR_OD5**.

**Questions** : Avantage de GPIO_ODR_OD5 ? Où sont définies ces constantes ? Que signifie __IO dans la structure ?

---

**Réponse** : [../reponses/04-headers-cmsis.md](../reponses/04-headers-cmsis.md) · **Retour** : [Vue d'ensemble](../README.md)
