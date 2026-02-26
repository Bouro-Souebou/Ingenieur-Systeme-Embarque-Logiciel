# Leçon 3 – PWM : fréquence et rapport cyclique

## Objectif de la leçon

Générer un signal **PWM** (Pulse Width Modulation) avec un timer : **fréquence** = période du timer (registre ARR), **rapport cyclique** = comparaison avec le registre **CCR**. Configurer la **broche** en sortie alternate pour le canal du timer.

## 1. Période et fréquence

Le compteur du timer varie de 0 à **ARR** (Auto-Reload Register) puis repasse à 0 (mode up). La **période** du cycle = (ARR + 1) / f_timer. Donc **fréquence PWM** = f_timer / (ARR + 1). Ex. f_timer = 1 MHz, ARR = 999 → période 1 ms → 1 kHz.

## 2. Rapport cyclique (duty cycle)

Un registre **CCR** (Capture/Compare) est comparé au compteur. En mode PWM classique : **sortie à 1** tant que count < CCR, **sortie à 0** sinon (ou l'inverse selon le mode). Donc **rapport cyclique** = CCR / (ARR + 1). Ex. ARR = 999, CCR = 300 → duty 30 %.

## 3. Broche et canal

Chaque **canal** du timer (CH1, CH2, …) peut être connecté à une **broche** GPIO (voir Reference Manual : TIMx_CHy sur quelle broche). Configurer la broche en **alternate function** pour le timer, et le **canal** en mode **PWM** (comparaison, output compare). La sortie PWM apparaît sur la broche.

## 4. Usages typiques

- **LED** : varier CCR pour le dimming (luminosité).
- **Moteur DC** : rapport cyclique = rapport tension moyenne (avec pont en H).
- **Servo** : impulsion 1–2 ms à 50 Hz (période 20 ms) ; la largeur d'impulsion commande l'angle.

**Suite** : [Leçon 4 – Input capture](04-input-capture.md)
