# Leçon 4 – Activer une interruption

## Objectif de la leçon

Savoir **activer** une interruption pour qu’elle soit prise en compte par le processeur : **configurer le périphérique** (quelle broche, quel événement) et **activer l’IRQ dans le NVIC** (et éventuellement définir la priorité).

---

## 1. Deux niveaux d’activation

Pour qu’une interruption soit **effective**, deux choses sont nécessaires :

1. **Côté périphérique** : le bloc (GPIO/EXTI, UART, timer, etc.) doit être configuré pour **générer** une requête d’interruption quand l’événement se produit (ex. front montant sur la broche 0, caractère reçu sur l’UART).
2. **Côté NVIC** : l’**IRQ** correspondante doit être **activée** (enable) dans le contrôleur d’interruptions du cœur. Sinon, le processeur ignore la requête.

Il faut aussi que les **interruptions globales** ne soient pas masquées (pas de désactivation globale prolongée ; après le reset, le cœur active en général les interruptions une fois le startup terminé).

---

## 2. Configurer le périphérique

Chaque type de périphérique a ses registres de configuration. Exemples :

- **EXTI (External Interrupt)** : choisir la **ligne** (broche 0 à 15), la **source** (quel port GPIO pour cette ligne), le **type** d’événement (front montant, descendant, ou les deux), et **activer** la ligne (bit enable). Les détails sont dans le Reference Manual, chapitre EXTI.
- **UART** : activer l’interruption de **réception** (RXNE) et/ou d’**émission** (TXE) dans le registre de contrôle (ex. USARTx->CR1).
- **Timer** : activer l’interruption d’**update** (overflow) ou de **compare** dans le registre du timer.

Sans cette configuration, le périphérique ne génère pas de requête IRQ vers le NVIC.

---

## 3. Activer l’IRQ dans le NVIC

Le **NVIC** a un registre (ou un ensemble de bits) pour **activer** chaque IRQ : mettre le bit correspondant à 1 pour que le processeur accepte cette source. En pratique on utilise les fonctions **CMSIS** :

```c
#include "stm32f4xx.h"   /* ou le header de ton MCU */

NVIC_EnableIRQ(EXTI0_IRQn);   /* EXTI0_IRQn = numéro d’IRQ pour la ligne 0 */
```

On peut aussi définir la **priorité** (plus le nombre est petit, plus la priorité est élevée) :

```c
NVIC_SetPriority(EXTI0_IRQn, 2);   /* priorité 2 */
NVIC_EnableIRQ(EXTI0_IRQn);
```

Le **numéro d’IRQ** (EXTI0_IRQn, USART1_IRQn, etc.) est défini dans les headers CMSIS / fabricant (c’est l’index dans la partie « IRQ fabricant » de la table des vecteurs).

---

## 4. Ordre recommandé

1. **Configurer** le périphérique (broche, événement, enable dans le bloc).
2. **Définir la priorité** (optionnel mais recommandé) : `NVIC_SetPriority(IRQn, priority)`.
3. **Activer** l’IRQ dans le NVIC : `NVIC_EnableIRQ(IRQn)`.
4. S’assurer que le **handler** (ISR) est bien défini et qu’il **acquitte** l’interruption.

Si tu actives l’IRQ avant d’avoir configuré le périphérique (ou si le périphérique génère des événements parasites), tu peux recevoir des interruptions inattendues ; l’ordre ci-dessus limite les faux déclenchements.

---

## Points clés à retenir

- **Périphérique** : configurer la source (broche, événement) et activer la génération d’IRQ dans le bloc.
- **NVIC** : `NVIC_EnableIRQ(IRQn)` et éventuellement `NVIC_SetPriority(IRQn, priority)`.
- **Ordre** : config périphérique → priorité → enable NVIC ; handler implémenté et qui acquitte.

---

## Tester sa compréhension

→ [Scénario – Activer une interruption](scenarios/isr-activation.md) · [Réponse](reponses/isr-activation.md)

---

**Suite** : [Leçon 5 – Synthèse et bonnes pratiques](05-synthese-bonnes-pratiques.md)
