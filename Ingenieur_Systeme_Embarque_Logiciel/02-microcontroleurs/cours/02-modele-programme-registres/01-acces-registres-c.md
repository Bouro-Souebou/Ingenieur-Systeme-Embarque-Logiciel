# Leçon 1 – Accès aux registres en C

## Objectif de la leçon

Savoir **accéder** à un registre matériel depuis le C : adresse du registre, pointeur `volatile`, et organisation des adresses (base + offset) pour garder le code lisible et maintenable.

---

## 1. Registre = adresse mémoire

Comme vu dans le cours **Architecture Cortex-M**, les **périphériques** sont **mappés en mémoire** : chaque registre (ODR, CRL, etc.) correspond à une **adresse** sur 32 bits. **Lire** cette adresse renvoie la valeur du registre ; **écrire** à cette adresse modifie le registre (et donc le comportement du matériel).

En C, on utilise un **pointeur** vers un entier 32 bits (souvent `uint32_t`) initialisé avec cette adresse. Pour que le compilateur ne supprime pas ni ne réordonne les accès (car le registre peut changer « tout seul » à cause du matériel), on utilise le qualificateur **volatile** (voir module Fondements).

---

## 2. Pointeur volatile vers une adresse fixe

```c
#include <stdint.h>

#define GPIOA_BASE  0x40010800u
#define GPIOA_ODR   (GPIOA_BASE + 0x0Cu)

#define REG(addr)  (*(volatile uint32_t *)(addr))

void led_on(void) {
    REG(GPIOA_ODR) |= (1u << 5);   /* mettre le bit 5 à 1 */
}
```

- **REG(addr)** : macro qui « déréférence » l'adresse `addr` comme un pointeur vers `volatile uint32_t`. Chaque lecture ou écriture de `REG(GPIOA_ODR)` produit bien un accès mémoire au registre.
- Les **adresses** sont définies en **macros** (ou constantes) pour éviter les « nombres magiques » et pour pouvoir les ajuster selon le MCU (Reference Manual).

---

## 3. Base + offset

Les blocs périphériques ont une **adresse de base** ; chaque **registre** du bloc est à un **offset** fixe (documenté dans le Reference Manual). Exemple pour un port GPIO (STM32-like) :

| Registre | Offset | Rôle |
|----------|--------|------|
| CRL | 0x00 | Configuration broches 0–7 |
| CRH | 0x04 | Configuration broches 8–15 |
| IDR | 0x08 | Lecture des entrées |
| ODR | 0x0C | Écriture des sorties |
| BSRR | 0x10 | Set/Reset bits (atomique) |

En C : `#define GPIOA_ODR (GPIOA_BASE + 0x0C)`. Si tu changes de MCU, tu ne modifies que `GPIOA_BASE` (ou tu utilises les headers du fabricant).

---

## 4. Taille du registre

Sur Cortex-M, beaucoup de registres sont **32 bits**. Certains blocs ont des registres **16 bits** (ex. certains timers) ou **8 bits**. Il faut utiliser le type qui correspond : `volatile uint32_t *`, `volatile uint16_t *`, ou `volatile uint8_t *`. Le Reference Manual indique la taille de chaque registre.

---

## Points clés à retenir

- Un **registre** est une **adresse** ; en C on y accède via un **pointeur** `volatile` (uint32_t, uint16_t ou uint8_t selon le cas).
- Organiser les adresses en **base + offset** (macros) pour la lisibilité et le portage.
- La macro **REG(addr)** permet d'écrire `REG(GPIOA_ODR) = valeur` au lieu de manipuler le pointeur à chaque fois.

---

**Suite** : [Leçon 2 – Exemple : le bloc GPIO](02-exemple-gpio.md)
