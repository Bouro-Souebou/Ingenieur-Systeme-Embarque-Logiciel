# Leçon 5 – Bonnes pratiques

## Objectif de la leçon

Récapituler les **bonnes pratiques** pour l'ADC : **impédance** d'entrée, **bruit** (filtrage, moyennage), **temps d'échantillonnage**, et résumé du cours ADC et DMA.

## 1. Impédance d'entrée

Les entrées ADC ont une **impédance** limitée et un **temps d'échantillonnage** pendant lequel un condensateur interne se charge. Pour des **capteurs à haute impédance** (sortie non bufferisée), la charge peut être trop lente → mesure fausse. Solution : **étage buffer** (ampli suiveur) entre le capteur et l'ADC, ou augmenter le **temps d'échantillonnage** si le MCU le permet (registre SMP).

## 2. Bruit

- **Alimentation** : filtrer Vref et Vdd (condensateurs de découplage) pour limiter le bruit.
- **Signaux** : filtre **anti-repliement** (low-pass) si la fréquence d'échantillonnage est limitée ; moyenner **plusieurs échantillons** pour réduire le bruit aléatoire (au prix d'un temps de réponse).

## 3. Temps d'échantillonnage

Le **datasheet** ADC indique le **temps d'échantillonnage** minimum pour une précision donnée (en fonction de l'impédance de source). Configurer le registre **SMP** (sample time) en conséquence. Un temps trop court donne des mesures bruitées ou incorrectes.

## 4. Résumé du cours ADC et DMA

- **ADC** : canal, trigger, résolution ; one-shot (SWSTART, EOC, lire DR) ou **continu** + **scan** (plusieurs canaux).
- **DMA** : transfert DR → buffer RAM ; interruption fin (ou demi-) de buffer pour traitement.
- **Timer + ADC + DMA** : acquisitions **périodiques** sans charge CPU ; double buffering pour ne pas perdre d'échantillons.

**Fin du cours ADC et DMA.**  
Retour à la [vue d'ensemble](README.md) du module Périphériques ou au [README principal](../../README.md) du parcours.  
→ **Module suivant** : [05 – Projets avancés](../../../05-projets-avances/README.md).
