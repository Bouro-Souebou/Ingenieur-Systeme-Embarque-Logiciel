# Leçon 5 – Champs multi-bits et bonnes pratiques

## Objectif de la leçon

Récapituler la **modification d'un champ** de plusieurs bits dans un registre (sans toucher aux autres bits) et les **bonnes pratiques** : noms explicites, BSRR pour un bit, cohérence du style d'accès.

---

## 1. Modifier un champ de plusieurs bits

Beaucoup de registres ont des **champs** sur 2, 4 ou 8 bits (ex. mode GPIO = 2 bits, mode+config = 4 bits). Pour modifier **uniquement** ce champ :

1. **Lire** le registre.
2. **Effacer** les bits du champ (AND avec un masque où ces bits sont à 0).
3. **Mettre** la nouvelle valeur du champ (décalée au bon offset).
4. **Écrire** le registre.

```c
#define MASK_PA5   (0xFu << 20)   /* 4 bits pour PA5 dans CRL */
uint32_t crl = REG(GPIOA_CRL);
crl = (crl & ~MASK_PA5) | ((nouvelle_valeur & 0xFu) << 20);
REG(GPIOA_CRL) = crl;
```

C'est la même technique qu'en **Fondements** (cours C, leçon Accès aux bits). Toujours **borner** la valeur (ex. `& 0xFu` pour un champ de 4 bits) pour ne pas déborder sur les bits voisins.

---

## 2. Un seul bit : préférer BSRR

Pour **un seul bit** en sortie (ex. allumer/éteindre une LED), utiliser **BSRR** au lieu de read-modify-write sur ODR :

- **Évite** la race condition si une ISR (ou une autre tâche) modifie ODR en même temps.
- **Plus clair** : intention « set bit 5 » ou « reset bit 5 » explicite.
- **Atomique** côté accès registre (une seule écriture).

```c
GPIOA->BSRR = (1u << 5);       /* set PA5 */
GPIOA->BSRR = (1u << (5 + 16));  /* reset PA5 */
```

---

## 3. Noms explicites

- **Macros** ou **constantes** pour les adresses (GPIOA_BASE, GPIOA_ODR) et les **masques** (MASK_PA5, MASK_MODE5).
- **Noms de bits** du header du fabricant (GPIO_ODR_OD5) quand ils existent.
- **Commentaires** courts si la valeur n'est pas évidente (ex. « mode 11 = output 50 MHz » avec référence au manuel).

---

## 4. Ne pas mélanger les styles

Dans un même projet (ou un même module), choisir un **style** cohérent :

- Soit **accès direct** aux registres avec les headers du fabricant (GPIOA->ODR, etc.) pour la performance et le contrôle.
- Soit **HAL/LL** (HAL_GPIO_WritePin, etc.) pour la portabilité et la lisibilité haute niveau.

Éviter de mélanger les deux dans la même fonction sans raison (ex. une partie en registres pour un timing critique, le reste en HAL : documenter la raison).

---

## 5. Résumé du cours « Modèle programme et registres »

- **Registres** = adresses ; accès en C avec **pointeurs volatile** (ou structures du fabricant).
- **GPIO** : CRL/CRH (config), IDR (lecture), ODR (écriture), BSRR (set/reset atomique).
- **Champs multi-bits** : lecture → masquage → mise à jour → écriture.
- **Headers** du fabricant (CMSIS, stm32f4xx.h, etc.) pour les noms et constantes ; **BSRR** pour un bit en sortie.

---

## Tester sa compréhension

- **Scénarios** (registres, GPIO, horloge, IDR/ODR) : [scenarios/registres-gpio.md](scenarios/registres-gpio.md).
- **Éléments de réponse** : [reponses/registres-gpio.md](reponses/registres-gpio.md).

---

**Fin du cours Modèle programme et registres.**  
Retour à la [vue d'ensemble](README.md) ou passage au cours [Startup, reset et vecteurs d'interruption](../../03-startup-interruptions/README.md).
