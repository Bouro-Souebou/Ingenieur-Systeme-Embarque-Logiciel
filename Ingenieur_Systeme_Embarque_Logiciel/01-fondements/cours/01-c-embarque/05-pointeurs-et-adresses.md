# Leçon 5 – Pointeurs et adresses mémoire

## Objectif de la leçon

Comprendre comment les **périphériques** d'un microcontrôleur sont accessibles en mémoire à des **adresses fixes**, et comment utiliser des **pointeurs** en C pour lire et écrire dans ces registres.

---

## 1. Mémoire mappée en entrée/sortie

Sur un microcontrôleur, la **mémoire** (RAM, flash) et les **périphériques** (GPIO, UART, timers, etc.) partagent le même **espace d'adressage**. Le processeur n'a pas d'instructions « entrée/sortie » séparées : il accède aux périphériques en **lisant ou écrivant à une adresse** précise.

On parle de **mémoire mappée en E/S** (Memory-Mapped I/O) :

- À l'adresse **0x4001080C**, par exemple, se trouve le registre **ODR** du port GPIO A (Output Data Register).
- Une **lecture** à cette adresse renvoie la valeur du registre (état des sorties).
- Une **écriture** à cette adresse modifie le registre (donc l'état des broches).

Les adresses exactes sont données dans le **Reference Manual** du MCU (ou dans les headers fournis par le fabricant).

---

## 2. De l'adresse au pointeur en C

En C, un **pointeur** contient une adresse. Pour accéder à une adresse **fixe**, on convertit un entier (l'adresse) en pointeur :

```c
uint32_t *p;
p = (uint32_t *)0x4001080C;   /* cast : cette adresse pointe vers un uint32_t */
*p = 0x0001;                  /* écrire 1 dans le registre (allumer la sortie 0) */
uint32_t val = *p;            /* lire le registre */
```

Pour les registres matériels, on combine avec **volatile** (voir leçon 3) :

```c
volatile uint32_t *p_odr = (volatile uint32_t *)0x4001080C;
*p_odr = 0x0001;
```

---

## 3. Organiser les adresses : macros et constantes

Éviter les « nombres magiques » dispersés dans le code. Centraliser les adresses dans des **macros** ou des constantes :

```c
#define PERIPH_BASE   0x40000000u
#define GPIOA_BASE    (PERIPH_BASE + 0x00010800u)
#define GPIOA_ODR     (GPIOA_BASE + 0x0Cu)

#define REG_GPIOA_ODR  (*(volatile uint32_t *)GPIOA_ODR)

void led_on(void) {
    REG_GPIOA_ODR |= (1u << 5);   /* allumer la broche 5 du port A */
}
```

Avantages :

- **Lisibilité** : le nom du registre indique son rôle.
- **Maintenabilité** : si l'adresse change (autre MCU, autre document), on ne modifie qu'un seul endroit.
- **Vérification** : on peut comparer avec le Reference Manual (offset 0x0C pour ODR, etc.).

---

## 4. Structure des blocs périphériques

Souvent, un **périphérique** a plusieurs registres à des **offsets** fixes par rapport à une **adresse de base**. Exemple (simplifié) :

| Offset | Nom | Rôle |
|--------|-----|------|
| 0x00 | CRL | Configuration des broches 0–7 |
| 0x04 | CRH | Configuration des broches 8–15 |
| 0x08 | IDR | Lecture des entrées |
| 0x0C | ODR | Écriture des sorties |

En C, on peut définir une **structure** dont les champs correspondent à ces offsets (en respectant l'ordre et les types), puis pointer vers l'adresse de base. Les fabricants le font dans leurs headers (ex. `GPIO_TypeDef` dans les SDK STM32). Pour un débutant, des macros par registre suffisent ; les structures viennent quand on lit le code du fabricant.

---

## 5. Bonnes pratiques

- **Toujours** utiliser un cast explicite : `(volatile uint32_t *)ADRESSE`.
- **Documenter** la source de l'adresse (nom du manuel, numéro de page ou de section) en commentaire si ce n'est pas évident.
- Ne **pas** faire d'arithmétique de pointeurs hasardeuse : un registre = une adresse ; pour le registre suivant, utiliser l'offset documenté (base + offset).
- Vérifier la **taille** du registre (8, 16 ou 32 bits) et utiliser `uint8_t`, `uint16_t` ou `uint32_t` en conséquence.

---

## 6. Exemple complet (extrait)

```c
#include <stdint.h>

#define GPIOA_BASE   0x40010800u
#define GPIOA_CRL    (GPIOA_BASE + 0x00)
#define GPIOA_ODR    (GPIOA_BASE + 0x0C)

#define REG(addr)  (*(volatile uint32_t *)(addr))

void gpio_pa5_init_output(void) {
    /* Configurer PA5 en sortie (champ mode sur 2 bits, position 20-21) */
    uint32_t crl = REG(GPIOA_CRL);
    crl &= ~(0x3u << 20);   /* mode = 00 (entrée) -> on va mettre 01 ou 10 */
    crl |=  (0x1u << 20);   /* mode 01 = sortie 10 MHz */
    REG(GPIOA_CRL) = crl;
}

void gpio_pa5_set(void) {
    REG(GPIOA_ODR) |= (1u << 5);
}

void gpio_pa5_clear(void) {
    REG(GPIOA_ODR) &= ~(1u << 5);
}
```

---

## Points clés à retenir

- Les **périphériques** sont accessibles à des **adresses fixes** ; en C on utilise des **pointeurs** (avec `volatile` pour les registres).
- Centraliser les adresses dans des **macros** ou constantes (nom du registre, base + offset).
- Toujours **caster** en `(volatile uint32_t *)` (ou 8/16 bits selon le registre) et vérifier les tailles dans le manuel.

---

**Suite** : [Leçon 6 – Const, static et mémoire (stack/heap)](06-const-static-memoire.md)
