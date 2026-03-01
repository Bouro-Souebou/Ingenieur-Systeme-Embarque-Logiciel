# Leçon 5 – Bonnes pratiques

## Objectif de la leçon

Récapituler les **bonnes pratiques** pour les timers et le PWM : éviter les fréquences audibles (vibrations), gérer l'**overflow** en capture, et vérifier **résolution** et **fréquence d'entrée** pour la précision.

## 1. PWM : fréquences audibles

Si la **fréquence PWM** tombe dans le domaine **audible** (ex. 1–20 kHz) et que le circuit (condensateurs, moteur) peut vibrer, on peut entendre un sifflement. Pour l'éclairage LED ou moteur, utiliser une fréquence **au-dessus** de l'audible (ex. 25 kHz) ou **en dessous** (ex. 100 Hz) selon l'application. Filtrer le signal PWM si besoin (filtre RC) pour lisser la tension moyenne.

## 2. Capture : overflow du compteur

Si la **période** à mesurer est **longue** par rapport à (ARR+1) × période_timer, le compteur peut **déborder** une ou plusieurs fois entre deux captures. Il faut soit **compter** les overflows (interruption Update) et les ajouter au calcul, soit utiliser un **timer en mode 32 bits** (si disponible) ou un prescaler plus grand pour allonger la période max mesurable.

## 3. Résolution et précision

La **résolution** du PWM (nombre de pas de rapport cyclique) = ARR+1. Ex. ARR = 999 → 1000 pas (0,1 %). Pour une résolution fine, augmenter ARR (en réduisant la fréquence PWM si la même base de temps) ou utiliser un timer avec une **horloge** plus rapide. Vérifier la **fréquence d'entrée** du timer (après prescaler) pour la précision des mesures de temps.

## 4. Résumé du cours Timers et PWM

- **Timer** : compteur + overflow + comparaison ; base du tick, PWM et capture.
- **SysTick** : réservé au RTOS en général.
- **PWM** : ARR = période, CCR = rapport cyclique ; broche en alternate.
- **Capture** : enregistrer le compteur sur un front ; mesurer largeur d'impulsion ou période.

**Fin du cours Timers, PWM et capture.**  
Retour à la [vue d'ensemble](README.md) ou passage au cours [ADC et DMA](../../04-adc-dma/README.md).
