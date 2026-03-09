# TP – Périphériques

## Fichiers squelette (templates)

Chaque thème a un fichier `.c` à compléter (commentaires « A FAIRE ») :

| Fichier | Thème | Objectif |
|---------|--------|----------|
| `uart_echo_template.c` | UART | Config USART, bannière, echo RX → TX |
| `i2c_sensor_template.c` | I2C | Lire capteur/EEPROM I2C, afficher UART |
| `spi_sensor_template.c` | SPI | Lire/écrire périphérique SPI |
| `pwm_led_template.c` | PWM | PWM timer, varier rapport cyclique |
| `adc_dma_template.c` | ADC + DMA | Acquisition DMA, moyenne ou envoi UART |

## Ordre conseillé

1. **UART** : configurer USART1 (ou 2), envoyer une chaîne au démarrage, recevoir des caractères et les renvoyer (echo). Puis : réception en interruption + queue FreeRTOS vers une tâche qui parse des commandes (ex. `LED ON`, `LED OFF`).
2. **I2C** : lire un capteur (ex. température I2C) ou une EEPROM ; afficher la valeur sur UART ou sur un afficheur.
3. **SPI** : lire/écrire un capteur ou une mémoire SPI (ex. flash externe, écran).
4. **PWM** : générer un PWM sur un timer (LED ou moteur), faire varier le rapport cyclique (potentiomètre ADC ou commande UART).
5. **ADC + DMA** : acquérir un canal en continu via DMA, calculer la moyenne ou envoyer les échantillons par UART (format binaire ou CSV).

## Cible

Utiliser la même carte que pour les modules 02 et 03 (ex. STM32 Nucleo). Les exemples du fabricant (STM32Cube) et les drivers d’exemple (BSP) sont une bonne base ; les adapter pour FreeRTOS (queues, mutex) si besoin.
