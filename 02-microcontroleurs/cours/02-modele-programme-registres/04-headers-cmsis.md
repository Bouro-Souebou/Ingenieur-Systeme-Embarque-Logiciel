# Leçon 4 – Headers CMSIS et fabricant

## Objectif de la leçon

Utiliser les **fichiers d'en-tête** fournis par le fabricant (ST, NXP, etc.) ou **CMSIS** pour accéder aux registres par **nom** (GPIOA->ODR, GPIO_ODR_OD5) au lieu d'adresses numériques, ce qui réduit les erreurs et facilite le portage.

---

## 1. Pourquoi des headers ?

Écrire à la main toutes les adresses (0x40010800, 0x4001080C, …) est **source d'erreurs** et **peu lisible**. Les fabricants fournissent des **headers** (fichiers .h) qui définissent :

- Les **adresses de base** des blocs (GPIOA_BASE, USART1_BASE, …).
- Des **structures** dont les champs correspondent aux registres (offset 0, 4, 8, …).
- Des **constantes** pour les valeurs des champs (modes GPIO, bits de statut, etc.).

Ainsi, au lieu de `REG(0x4001080C) |= (1u << 5);`, on écrit par exemple `GPIOA->ODR |= GPIO_ODR_OD5;` (noms qui varient selon le SDK).

---

## 2. CMSIS (Cortex Microcontroller Software Interface Standard)

**CMSIS** est une couche d'abstraction **ARM** pour les Cortex-M. Elle définit :

- Les **noms des exceptions** et des **IRQ** (numéros de vecteur).
- Les **fonctions** pour le NVIC (NVIC_EnableIRQ, NVIC_SetPriority), le SysTick, etc.
- Une structure commune pour décrire les **périphériques** (GPIO_TypeDef, etc.).

Les **fabricants** (ST, NXP, Nordic, etc.) fournissent des **packs** qui incluent CMSIS **et** les définitions spécifiques à leur MCU (adresses des GPIOA, GPIOB, … pour leur gamme). En projet STM32, on inclut en général un fichier du type `stm32f4xx.h` (ou stm32l4xx.h, etc.) qui inclut lui-même les headers CMSIS et définit les bases et structures pour ce MCU.

---

## 3. Structures et accès aux registres

Le header du fabricant définit souvent une **structure** dont les champs sont aux bons offsets. Exemple (conceptuel) :

```c
typedef struct {
    __IO uint32_t CRL;
    __IO uint32_t CRH;
    __IO uint32_t IDR;
    __IO uint32_t ODR;
    __IO uint32_t BSRR;
    /* ... */
} GPIO_TypeDef;

#define GPIOA ((GPIO_TypeDef *) GPIOA_BASE)
```

`__IO` est en général un macro pour `volatile`. On accède alors aux registres par :

```c
GPIOA->ODR |= (1u << 5);
GPIOA->BSRR = (1u << 5);
```

---

## 4. Constantes pour les bits

Les headers définissent aussi des **masques** et **noms de bits** pour éviter les nombres magiques. Exemples (noms typiques STM32) :

- `GPIO_ODR_OD5` = (1u << 5) pour le bit 5 de ODR.
- `GPIO_CRL_MODE5_0`, `GPIO_CRL_MODE5_1` pour les bits de mode de la broche 5.
- `RCC_AHB1ENR_GPIOAEN` = (1u << 0) pour activer l'horloge GPIOA.

En incluant le bon header et en utilisant ces noms, le code reste lisible et cohérent avec la documentation du fabricant.

---

## 5. En pratique

- **Créer un projet** avec STM32CubeIDE ou un template (Makefile + SDK) inclut en général les bons headers.
- **Lire** le fichier `stm32f4xx.h` (ou équivalent) pour voir les noms exacts (GPIOA, GPIO_TypeDef, ODR, etc.) et les constantes disponibles.
- **Ne pas mélanger** dans le même fichier accès directs avec adresses en dur et accès via HAL/LL sans convention claire : choisir un style (registres directs avec headers, ou couche HAL) et s'y tenir.

---

## Points clés à retenir

- Les **headers** du fabricant (et CMSIS) fournissent les **adresses**, **structures** et **constantes** pour les registres.
- Accès typique : **GPIOA->ODR**, **GPIOA->BSRR**, etc., avec constantes du type **GPIO_ODR_OD5**.
- Utiliser ces headers **systématiquement** en projet pour éviter les erreurs d'adresse et garder le code maintenable.

---

**Suite** : [Leçon 5 – Champs multi-bits et bonnes pratiques](05-champs-bonnes-pratiques.md)
