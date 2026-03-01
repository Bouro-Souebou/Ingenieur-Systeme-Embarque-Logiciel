# Leçon 1 – Paramètres et configuration

## Objectif de la leçon

Savoir **configurer** un bloc UART sur un MCU : choix du **baudrate**, du **format** (bits, parité, stop), des **broches** TX/RX (fonction alternative), et activation de l'**horloge** du périphérique.

---

## 1. Rappel : rôle de l'UART

L'**UART** (Universal Asynchronous Receiver-Transmitter) permet une communication **série asynchrone** : pas de fil d'horloge, accord sur le **débit** (baudrate) et le **format** de trame entre l'émetteur et le récepteur. En embarqué, l'UART sert au **debug** (printf, logs), à la **commande** (terminal), et à la liaison avec des **modules** (GPS, GSM, Bluetooth). Voir le cours **Fondements – Bus** pour le format de trame (start, données, parité, stop).

---

## 2. Paramètres à régler

- **Baudrate** : débit en symboles par seconde (ex. 9600, 115200). L'émetteur et le récepteur **doivent** utiliser le même baudrate. Le MCU calcule un **diviseur** à partir de l'horloge du bus (APB) qui alimente l'UART : diviseur = f_APB / baudrate (avec arrondi ou fraction selon le matériel).
- **Données** : 7 ou 8 bits par caractère (souvent 8).
- **Parité** : none, even ou odd (détection d'erreur sur un bit).
- **Bits d'arrêt** : 1 ou 2 (fin de trame).

Les SDK (STM32CubeMX, HAL) fournissent des fonctions du type **HAL_UART_Init** qui prennent le baudrate et le format en paramètres et programment les registres (BRR, CR1, CR2, etc.) en conséquence.

---

## 3. Broches TX et RX

Les broches **TX** (émission) et **RX** (réception) sont des **GPIO** configurées en **fonction alternative** (alternate function) pour le bloc UART concerné (USART1, USART2, etc.). Le **Reference Manual** du MCU indique quelle broche correspond à quel UART (ex. PA9 = USART1_TX, PA10 = USART1_RX sur STM32). Il faut :

1. **Activer l'horloge** du port GPIO et du **périphérique UART** (RCC).
2. **Configurer** les broches en mode **alternate** (AF) avec la bonne fonction.
3. **Initialiser** l'UART (baudrate, format) avant d'envoyer ou recevoir.

---

## 4. Horloge du périphérique

Sur les STM32, chaque périphérique (dont USART1, USART2) est alimenté par une **horloge** (bus APB1 ou APB2). Cette horloge doit être **activée** (bit enable dans RCC_APBxENR) avant d'accéder aux registres de l'UART. L'ordre typique est : activer horloge RCC, configurer GPIO (TX, RX), initialiser UART (HAL_UART_Init ou registres).

---

## Points clés à retenir

- **Baudrate**, **format** (7/8 bits, parité, stop) et **broches** (TX, RX en alternate) doivent être cohérents avec l'autre côté de la liaison.
- **Activer l'horloge** du port GPIO et du bloc UART avant toute configuration.
- Utiliser le **Reference Manual** ou le **SDK** (CubeMX, HAL) pour les valeurs exactes.

---

**Suite** : [Leçon 2 – Envoi et réception en polling](02-polling.md)
