# Leçon 2 – Types et stdint.h

## Objectif de la leçon

Savoir **choisir les bons types** en C pour l'embarqué : tailles garanties, types à taille fixe avec `stdint.h`, et éviter les pièges des types « classiques » (`int`, `long`).

---

## 1. Le problème des types « classiques » en C

En C standard, la taille des types **n'est pas fixée** par le langage, seulement par des **minima** :

| Type | Taille minimale | En pratique sur PC (64 bits) | Sur un MCU 32 bits |
|------|------------------|-------------------------------|---------------------|
| `char` | 1 octet | 1 octet | 1 octet |
| `short` | ≥ 16 bits | 16 bits | 16 bits |
| `int` | ≥ 16 bits | 32 bits | 32 bits |
| `long` | ≥ 32 bits | 64 bits (souvent) ou 32 | 32 bits |
| `long long` | ≥ 64 bits | 64 bits | 64 bits |

**Conséquence** : un programme qui suppose « `int` = 32 bits » peut se comporter différemment sur une autre plateforme. En embarqué, on travaille souvent avec des **registres matériels** de 8, 16 ou 32 bits : il faut des types dont la taille est **garantie**.

---

## 2. La solution : stdint.h

Le fichier d'en-tête **`<stdint.h>`** (C99) définit des types dont la **taille est fixée** :

### Types entiers non signés (unsigned)

| Type | Taille | Plage |
|------|--------|--------|
| `uint8_t` | 8 bits | 0 à 255 |
| `uint16_t` | 16 bits | 0 à 65 535 |
| `uint32_t` | 32 bits | 0 à 4 294 967 295 |
| `uint64_t` | 64 bits | 0 à une très grande valeur |

### Types entiers signés (signed)

| Type | Taille | Plage |
|------|--------|--------|
| `int8_t` | 8 bits | -128 à 127 |
| `int16_t` | 16 bits | -32 768 à 32 767 |
| `int32_t` | 32 bits | environ ±2,1 milliards |
| `int64_t` | 64 bits | très grand |

### Utilisation

```c
#include <stdint.h>

uint8_t  compteur;      /* 0 à 255, un octet */
uint16_t valeur_capteur;/* 0 à 65535, deux octets */
uint32_t registre_gpio; /* 32 bits, comme un registre sur Cortex-M */
int16_t  temperature;   /* peut être négatif */
```

---

## 3. Quand utiliser quel type ?

### Registres matériels

Les blocs matériels (GPIO, UART, etc.) ont des registres de **8**, **16** ou **32** bits. On utilise le type qui correspond exactement :

- Registre 32 bits (très courant sur ARM) → `uint32_t`
- Registre 16 bits (certains timers, ADC) → `uint16_t`
- Registre 8 bits (certains contrôleurs) → `uint8_t`

Exemple : lire un registre 32 bits.

```c
volatile uint32_t *p_reg = (volatile uint32_t *)0x4001080C;
uint32_t valeur = *p_reg;
```

### Compteurs et boucles

- Si la valeur ne peut **jamais** être négative (nombre d'échantillons, index 0..N-1), utiliser un type **non signé** : `uint8_t`, `uint16_t`, `uint32_t`.
- Éviter `int` pour les compteurs qui dépassent 255 : sur un MCU, `int` est souvent 32 bits, mais pour la clarté et la portabilité, `uint16_t` ou `uint32_t` est préférable.

### Données échangées (réseau, bus)

Les protocoles (UART, I2C, SPI, TCP/IP) définissent des **formats** en octets. Utiliser `uint8_t` pour les octets et `uint16_t` / `uint32_t` pour les champs multi-octets (en respectant l'ordre des octets, big-endian / little-endian, si nécessaire).

---

## 4. Suffixe « u » pour les constantes

En C, une constante comme `1` est de type `int` (signé). Pour les **décalages** et les **opérations bit à bit**, on préfère des constantes **non signées** pour éviter des comportements dépendants du signe :

```c
/* À privilégier */
1u      /* unsigned */
0xFFu   /* unsigned */
(1u << 5)

/* À éviter dans un contexte bit à bit avec des unsigned */
(1 << 5)   /* 1 est signé ; selon le contexte, peut donner des surprises */
```

Nous reviendrons sur les décalages dans la leçon « Accès aux bits ».

---

## 5. Résumé des bonnes pratiques

| Situation | Type recommandé |
|-----------|------------------|
| Registre 32 bits | `uint32_t` (avec `volatile` si accès matériel) |
| Registre 8 bits | `uint8_t` |
| Compteur 0..255 | `uint8_t` |
| Compteur plus grand, non négatif | `uint16_t` ou `uint32_t` |
| Valeur pouvant être négative (ex. température) | `int16_t` ou `int32_t` |
| Octet (trame, buffer) | `uint8_t` |
| Constantes pour masques / décalages | suffixe `u` (ex. `1u`, `0xFFu`) |

---

## Points clés à retenir

- En embarqué, **ne pas supposer** la taille de `int` ou `long` : utiliser **`stdint.h`**.
- `uint8_t`, `uint16_t`, `uint32_t` (et leurs versions signées) garantissent la taille et correspondent aux registres et aux formats de données.
- Privilégier les types **non signés** pour tout ce qui n'est pas négatif (compteurs, index, registres).

---

**Suite** : [Leçon 3 – Le qualificateur volatile](03-volatile.md)
