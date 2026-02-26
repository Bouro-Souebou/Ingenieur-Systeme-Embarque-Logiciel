# Leçon 3 – Mode continu et scan

## Objectif de la leçon

Utiliser le **mode continu** (une conversion enchaîne la suivante automatiquement) et le **mode scan** (enchaîner **plusieurs canaux** dans une séquence). Utile pour acquérir plusieurs capteurs (température, tension, courants) en round-robin.

## 1. Mode continu

En **continu**, à la **fin** d'une conversion (EOC), la conversion **suivante** redémarre automatiquement (même canal ou séquence selon la config). On n'a pas à relancer SWSTART à chaque fois. Utile pour un **flux** d'échantillons sur un (ou plusieurs) canal(x). À combiner avec **DMA** pour stocker les résultats en RAM sans intervention CPU.

## 2. Mode scan

En **scan**, on définit une **liste de canaux** (registres SQR1, SQR2, SQR3 sur STM32 : ordre des canaux). L'ADC enchaîne les conversions : canal 1, puis canal 2, … puis retour au premier (en continu) ou arrêt (one-shot). À la fin de la **séquence** (EOS = End Of Sequence), une interruption peut être générée. Chaque résultat correspond à un canal (ordre fixe) ; le logiciel sait quel indice correspond à quel capteur.

## 3. Utilisation typique

Acquisition **périodique** de plusieurs capteurs : configurer **scan** (canaux temp, Vbat, courant), **continu** + **trigger timer** (ex. 100 Hz) pour lancer une séquence toutes les 10 ms, et **DMA** pour écrire les résultats dans un buffer (un mot par canal). Une interruption en **fin de séquence** ou **demi-buffer** signale qu'on peut traiter les données.

**Suite** : [Leçon 4 – DMA avec ADC](04-dma-adc.md)
