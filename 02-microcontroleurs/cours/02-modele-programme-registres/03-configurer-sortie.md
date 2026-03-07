# Leçon 3 – Configurer une broche en sortie

## Objectif de la leçon

Réaliser **étape par étape** la configuration d'une broche GPIO en **sortie** (ex. PA5 pour une LED) : activer l'horloge du port, puis configurer le registre CRL (ou CRH) avec le bon mode et le bon type.

---

## 1. Activer l'horloge du port

Sur les STM32, chaque périphérique (dont chaque port GPIO) est alimenté par une **horloge** qui doit être **activée** avant d'accéder à ses registres. Sinon, les accès peuvent être ignorés ou provoquer une faute. L'horloge des ports GPIO est en général gérée par le bus **AHB** (ou AHB1) via le bloc **RCC** (Reset and Clock Control).

Exemple (STM32F4) : le bit 0 du registre **RCC_AHB1ENR** active l'horloge de **GPIOA**. Il faut donc faire :

```c
#define RCC_BASE        0x40023800u
#define RCC_AHB1ENR     (RCC_BASE + 0x30u)
#define REG(addr)      (*(volatile uint32_t *)(addr))

REG(RCC_AHB1ENR) |= (1u << 0);   /* enable GPIOA clock */
```

Le numéro du bit (0 pour GPIOA, 1 pour GPIOB, etc.) et le nom du registre (AHB1ENR, AHB2ENR, etc.) dépendent du MCU ; consulter le Reference Manual, chapitre RCC.

---

## 2. Choisir le bon registre : CRL ou CRH

- Broches **0 à 7** → **CRL**. Chaque broche utilise les bits **n*4** à **n*4+3** (ex. broche 5 : bits 20 à 23).
- Broches **8 à 15** → **CRH**. Broche 8 = bits 0–3, broche 9 = bits 4–7, etc.

Pour **PA5** (broche 5 du port A), on modifie **CRL**, bits **20–23**.

---

## 3. Valeurs du champ « mode » et « configuration »

Pour une **sortie** push-pull à 50 MHz (exemple courant pour une LED) :

- **Mode** (2 bits) : 11 = sortie 50 MHz (ou 10 = 2 MHz, 01 = 10 MHz selon les familles STM32).
- **Configuration** (2 bits) : 00 = sortie push-pull (GPIO push-pull).

Les 4 bits pour PA5 sont donc : mode = 11, config = 00 → en binaire **1100** = 0xCu. En position 20 : valeur = `0xCu << 20` (après avoir effacé les 4 bits de PA5).

Référence : Reference Manual, section GPIO, tableau « Port configuration register ».

---

## 4. Code complet : init PA5 en sortie

```c
#define GPIOA_BASE  0x40010800u
#define GPIOA_CRL   (GPIOA_BASE + 0x00u)
#define REG(addr)   (*(volatile uint32_t *)(addr))

void gpio_pa5_init(void) {
    /* 1. Activer l'horloge GPIOA (ex. STM32F4) */
    REG(RCC_AHB1ENR) |= (1u << 0);

    /* 2. PA5 : mode = 11 (output 50 MHz), config = 00 (push-pull) */
    uint32_t crl = REG(GPIOA_CRL);
    crl &= ~(0xFu << 20);           /* effacer les 4 bits de PA5 */
    crl |= (0x3u << 20) | (0x0u << 22);  /* mode 11, config 00 ; ou simplement 0x3u << 20 selon codage */
    REG(GPIOA_CRL) = crl;
}
```

Les constantes exactes (0x3 pour mode, 0x0 pour config) peuvent varier selon le manuel (parfois mode = 01 pour 10 MHz, etc.). En pratique, utiliser les définitions du SDK du fabricant évite les erreurs.

---

## 5. Allumer et éteindre la LED

Une fois PA5 configurée en sortie :

```c
#define GPIOA_ODR   (GPIOA_BASE + 0x0Cu)
#define GPIOA_BSRR  (GPIOA_BASE + 0x10u)

void led_on(void)  { REG(GPIOA_BSRR) = (1u << 5); }
void led_off(void) { REG(GPIOA_BSRR) = (1u << (5 + 16)); }
```

Ou avec ODR : `REG(GPIOA_ODR) |= (1u << 5);` et `REG(GPIOA_ODR) &= ~(1u << 5);`.

---

## Points clés à retenir

- **Activer l'horloge** du port (RCC) avant d'accéder aux registres GPIO.
- **CRL** pour broches 0–7, **CRH** pour 8–15 ; **4 bits par broche** (mode + config).
- Pour une sortie push-pull : mode = sortie (01/10/11 selon vitesse), config = push-pull (00).
- Utiliser **BSRR** pour set/reset propre d'un bit.

---

## Tester sa compréhension

→ [Scénario – Configurer une sortie](scenarios/03-configurer-sortie.md) · [Réponse](reponses/03-configurer-sortie.md)

---

**Suite** : [Leçon 4 – Headers CMSIS et fabricant](04-headers-cmsis.md)
