# Leçon 1 – Timer : principe

## Objectif de la leçon

Comprendre le **principe** d'un timer matériel : un **compteur** incrémenté (ou décrémenté) par une horloge, avec **overflow** et **comparaison** pour générer des événements (interruption, toggle de sortie). Base du PWM et de la capture.

## 1. Compteur et horloge

Un **timer** est un **registre compteur** (souvent 16 ou 32 bits) incrémenté (ou décrémenté) à chaque **tick** d'une horloge. L'horloge peut être l'horloge interne du MCU (APB, souvent divisée par un prescaler) ou un signal **externe** (broche TIx). La **fréquence** du timer = fréquence d'entrée / (prescaler + 1).

## 2. Overflow

Quand le compteur **dépasse** sa valeur max (0xFFFF pour 16 bits en mode up), il repasse à 0 (ou à la valeur de **reload** si configuré). Cet événement est un **overflow** (update event). Il peut générer une **interruption** (Update IRQ) ou servir de base à un **tick** logiciel (comme SysTick pour FreeRTOS).

## 3. Comparaison (compare match)

Le timer peut **comparer** la valeur courante du compteur à une (ou plusieurs) **valeur(s)** stockée(s) dans des registres de **comparaison** (CCR, Capture/Compare Register). Quand compteur = CCR :
- Génération d'une **interruption** ou d'un événement.
- **Toggle** d'une sortie (broche du timer) : base du **PWM** (sortie haute si count < CCR, basse sinon, avec reload périodique).

## 4. Résumé

- **Timer** = compteur + horloge (interne ou externe) + prescaler.
- **Overflow** = fin de cycle ; **comparaison** = égalité avec CCR → événement ou sortie.
- Utilisé pour : **tick** (SysTick), **PWM** (comparaison avec CCR), **capture** (enregistrer le compteur sur un front d'entrée).

**Suite** : [Leçon 2 – SysTick](02-systick.md)
