# Réponse – Paramètres et configuration UART

Voir [scénario](../scenarios/01-parametres-configuration.md).

---

## Réponse Scénario 1 : Baudrate et format

**Identiques** : **Baudrate** (9600), **nombre de bits** (8), **parité** (none), **bits d'arrêt** (1). Si l'un des deux est différent, les caractères reçus sont incorrects.

**Configuration MCU** : Dans le SDK (HAL_UART_Init, CubeMX) : baudrate = 9600, WordLength = 8, Parity = None, StopBits = 1. Le MCU calcule un **diviseur** (f_APB / baudrate) pour le registre BRR.

**Horloge** : Le diviseur dépend de l'horloge du bus (APB) qui alimente l'UART. Si la fréquence APB est différente de celle supposée (quartz, PLL), le baudrate réel diffère ; vérifier la config RCC et le calcul du diviseur.

---

## Réponse Scénario 2 : Broches et horloge

**Étapes** : (1) **Activer l'horloge** du port GPIO (RCC_AHB ou APB pour GPIOA) et du périphérique **USART1** (RCC_APB2ENR ou équivalent). (2) Configurer **PA9** en alternate function pour USART_TX et **PA10** pour USART_RX (mode AF, pull si besoin). (3) Initialiser l'UART (baudrate, format).

**RCC** : Les registres du périphérique (USART1->SR, DR, etc.) ne sont pas accessibles tant que l'horloge du bloc n'est pas activée ; une lecture/écriture pourrait être ignorée ou provoquer un comportement indéfini. Toujours activer l'horloge **avant** d'accéder aux registres.

---

**Retour** : [Scénarios](../scenarios/README.md) · [Leçon 1](../01-parametres-configuration.md)
