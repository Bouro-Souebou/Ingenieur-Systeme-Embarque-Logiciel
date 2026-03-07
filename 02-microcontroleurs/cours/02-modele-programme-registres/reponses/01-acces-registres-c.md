# Réponse – Accès aux registres en C

Voir [scénario](../scenarios/01-acces-registres-c.md).

---

## Réponse Scénario 1 : Pointeur volatile

**Optimisation** : Le compilateur considère que l'écriture dans une « variable » qui n'est jamais relue peut être supprimée (dead store). Il ne sait pas que cette adresse est un **registre matériel** dont l'écriture a un **effet de bord** (allumer la LED).

**volatile** : En qualifiant le pointeur avec **volatile** (`*(volatile uint32_t *)0x4001080C`), chaque lecture ou écriture est considérée comme un **effet de bord** : le compilateur ne supprime pas et ne réordonne pas ces accès.

**Adresse** : Dans le **Reference Manual** du MCU, chapitre « Memory map » ou « Register map » : base du bloc GPIOA (ex. 0x4001_0800), offset de ODR (ex. 0x0C) → adresse = base + offset.

---

## Réponse Scénario 2 : Base et offset

**Organisation** : Définir **GPIOA_BASE** (ex. 0x40010800), puis **GPIOA_ODR = GPIOA_BASE + 0x0C**. Idem pour GPIOB_BASE, etc. Les offsets (0x0C pour ODR) sont en général identiques d'un port à l'autre.

**Changement de MCU** : Si seule la **base** change (ex. 0x4002_0000 sur un autre STM32), on ne modifie que **GPIOA_BASE**. Les offsets restent les mêmes (documentés dans le manuel).

**Macro REG** : `#define REG(addr) (*(volatile uint32_t *)(addr))`. Utilisation : `REG(GPIOA_ODR) = valeur;` pour écrire, `valeur = REG(GPIOA_ODR);` pour lire. Une seule définition, accès lisible partout.

---

**Retour** : [Scénarios](../scenarios/README.md) · [Leçon 1](../01-acces-registres-c.md)
