# Leçon 2 – Exemple : le bloc GPIO

## Objectif de la leçon

Décrire les **registres** typiques d'un bloc **GPIO** (General Purpose Input/Output) : configuration (CRL/CRH), lecture (IDR), écriture (ODR), et set/reset atomique (BSRR). Ces notions sont communes à de nombreux MCU type STM32.

---

## 1. Rôle du GPIO

Un port **GPIO** permet de **piloter des broches** du MCU en **entrée** ou en **sortie** (ou en fonction alternative pour les périphériques comme UART, SPI). Chaque broche peut être :

- **Entrée** : lecture d'un niveau logique (0 ou 1), éventuellement avec résistance pull-up/pull-down.
- **Sortie** : génération d'un niveau logique (push-pull ou open-drain), avec une vitesse configurable (pour limiter les EMI et la consommation).

Un MCU comporte **plusieurs ports** (GPIOA, GPIOB, …) et chaque port a **plusieurs broches** (0 à 15 sur 16 bits, souvent). Les registres du bloc décrivent la configuration et l'état de toutes les broches du port.

---

## 2. Registres de configuration : CRL et CRH

Sur les STM32 (F1, F4, L4, etc.), la configuration des broches est répartie en deux registres :

- **CRL** (Configuration Register Low) : broches **0 à 7**. Chaque broche utilise **4 bits** : 2 bits pour le **mode** (entrée/sortie 2/10/50 MHz, entrée), 2 bits pour la **configuration** (push-pull, open-drain, etc.).
- **CRH** (Configuration Register High) : broches **8 à 15**, même principe (4 bits par broche).

Les valeurs exactes (mode 01 = sortie 10 MHz, etc.) sont dans le **Reference Manual** du MCU. En pratique on utilise souvent des constantes fournies par le SDK (ex. `GPIO_MODE_OUTPUT_PP`, `GPIO_SPEED_FREQ_LOW`).

---

## 3. IDR (Input Data Register)

Le registre **IDR** est en **lecture seule** (ou lecture seule côté logiciel). Chaque **bit** correspond à l'état **actuel** de la broche en entrée : 0 = niveau bas, 1 = niveau haut. On lit par exemple le bit 3 pour la broche 3 du port.

```c
uint32_t val = REG(GPIOA_IDR);
if (val & (1u << 3)) {
    /* broche 3 à 1 */
}
```

---

## 4. ODR (Output Data Register)

Le registre **ODR** permet d'**écrire** l'état des broches configurées en **sortie**. Écrire 1 dans le bit n met la broche n au niveau haut, écrire 0 au niveau bas. On peut faire un **read-modify-write** pour ne modifier qu'un bit (comme en Fondements) : `REG(GPIOA_ODR) |= (1u << 5);` pour mettre la broche 5 à 1.

Attention : en **lecture-modification-écriture**, si une interruption (ou le DMA) modifie le même registre entre la lecture et l'écriture, on peut écraser son changement. Pour **un seul bit**, le registre **BSRR** évite ce problème.

---

## 5. BSRR (Bit Set/Reset Register)

Le **BSRR** est un registre en **écriture seule** (ou utilisé uniquement en écriture) qui permet de mettre **un bit** à 1 ou à 0 **sans lire** le registre ODR. Il est souvent sur 32 bits :

- **Bits 0–15** : mettre à **1** le bit correspondant de ODR (écrire 1 dans BSRR bit n → ODR bit n = 1). Écrire 0 n'a pas d'effet.
- **Bits 16–31** : mettre à **0** le bit correspondant de ODR (écrire 1 dans BSRR bit (16+n) → ODR bit n = 0).

Exemple : mettre la broche 5 à 1 puis à 0 de façon atomique :

```c
REG(GPIOA_BSRR) = (1u << 5);    /* set : PA5 = 1 */
REG(GPIOA_BSRR) = (1u << (5 + 16));  /* reset : PA5 = 0 */
```

Aucune lecture de ODR ; pas de race condition avec une ISR qui modifierait ODR.

---

## Points clés à retenir

- **CRL/CRH** : configuration (mode, vitesse, type) des broches 0–7 et 8–15.
- **IDR** : lecture de l'état des entrées.
- **ODR** : écriture de l'état des sorties (read-modify-write possible mais attention concurrence).
- **BSRR** : set/reset d'un bit **atomique** pour les sorties.

---

**Suite** : [Leçon 3 – Configurer une broche en sortie](03-configurer-sortie.md)
