# Leçon 1 – ADC : principes

## Objectif de la leçon

Comprendre les **principes** de l'ADC (Analog-to-Digital Converter) : conversion **tension → nombre** (résolution 8/10/12/16 bits), **canaux** (broches analogiques, internes), **trigger** (logiciel ou événement), et **référence** (Vref).

## 1. Conversion tension → nombre

L'**ADC** convertit une **tension** d'entrée (entre 0 et Vref en général) en un **nombre** sur N bits (8, 10, 12 ou 16 selon le MCU). Formule : **V = (valeur / (2^N - 1)) × Vref**. Ex. 12 bits, Vref = 3,3 V : valeur 2048 → V = 1,65 V environ.

## 2. Canaux

Un ADC a **plusieurs canaux** (entrées) : broches **analogiques** (AN0, AN1, …), et souvent des canaux **internes** (référence interne, température du chip). On **sélectionne** le canal avant (ou dans) la séquence de conversion. Les broches doivent être configurées en **mode analogique** (pas en digital) pour éviter les conflits.

## 3. Trigger

Le **démarrage** d'une conversion peut être :
- **Logiciel** : bit **SWSTART** (Start Conversion) dans un registre de contrôle.
- **Événement** : timer (conversion périodique), EXTI (sur front), etc.

Selon l'application : one-shot sur demande (SWSTART) ou conversions **périodiques** (trigger timer).

## 4. Résolution et référence

**Résolution** : 12 bits courant sur STM32 (0–4095). Plus N est grand, plus la quantification est fine. **Vref** : souvent Vdd ou une broche Vref+ ; la plage de mesure est 0–Vref. Pour des signaux hors plage, utiliser un **étage de conditionnement** (ampli, diviseur).

**Suite** : [Leçon 2 – Conversion one-shot](02-conversion-one-shot.md)
