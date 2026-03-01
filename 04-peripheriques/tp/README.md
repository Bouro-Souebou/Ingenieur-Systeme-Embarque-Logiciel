# TP – Périphériques

## Ordre conseillé

1. **UART** : configurer USART1 (ou 2), envoyer une chaîne au démarrage, recevoir des caractères et les renvoyer (echo). Puis : réception en interruption + queue FreeRTOS vers une tâche qui parse des commandes (ex. `LED ON`, `LED OFF`).
2. **I2C** : lire un capteur (ex. température I2C) ou une EEPROM ; afficher la valeur sur UART ou sur un afficheur.
3. **SPI** : lire/écrire un capteur ou une mémoire SPI (ex. flash externe, écran).
4. **PWM** : générer un PWM sur un timer (LED ou moteur), faire varier le rapport cyclique (potentiomètre ADC ou commande UART).
5. **ADC + DMA** : acquérir un canal en continu via DMA, calculer la moyenne ou envoyer les échantillons par UART (format binaire ou CSV).

## Cible

Utiliser la même carte que pour les modules 02 et 03 (ex. STM32 Nucleo). Les exemples du fabricant (STM32Cube) et les drivers d’exemple (BSP) sont une bonne base ; les adapter pour FreeRTOS (queues, mutex) si besoin.
