# Leçon 5 – Intégration RTOS

## Objectif de la leçon

Intégrer l'UART dans une application **FreeRTOS** : **ISR RX** qui envoie les octets dans une **queue** ; **tâche** qui consomme la queue (parsing, commandes, affichage). Pour l'**émission**, tâche qui prépare un message et utilise un **driver** (mutex + buffer ou queue TX). Bonnes pratiques (priorités, timeouts).

---

## 1. Schéma classique : RX

- **ISR RX** : à chaque octet reçu (ou par paquet si DMA), **xQueueSendFromISR(q_uart_rx, &byte, &wake)** ; puis **portYIELD_FROM_ISR(wake)**. La queue doit être créée à la création (ex. 64 ou 128 octets, élément = uint8_t).
- **Tâche « traitement UART »** : boucle avec **xQueueReceive(q_uart_rx, &byte, timeout)**. Quand un octet est reçu, le parser (ligne de commande, protocole) ou l'afficher. Priorité de la tâche : suffisamment haute pour ne pas accumuler trop de retard si le débit est élevé, mais pas au-dessus des tâches critiques temps réel.

---

## 2. Schéma classique : TX

Deux approches possibles :

- **Tâche + mutex** : une seule tâche « envoi UART » détient un **mutex** sur l'UART. Les autres tâches qui veulent envoyer mettent leur message dans une **queue** (ou buffer partagé) ; la tâche envoi récupère et envoie octet par octet (ou par bloc avec DMA). Ainsi un seul expéditeur à la fois, pas de mélange de caractères.
- **Queue TX** : une **queue** d'octets à envoyer ; une tâche (ou une ISR TX) dépile et écrit dans DR. Les autres tâches font **xQueueSend(q_uart_tx, &byte, timeout)** pour envoyer. Mutex si plusieurs tâches envoient des messages multi-octets (pour ne pas intercaler les octets de deux messages).

---

## 3. Priorités et timeouts

- **Tâche traitement RX** : priorité adaptée au débit (trop basse = queue pleine, perte ; trop haute = peut affamer d'autres tâches). **Timeout** sur xQueueReceive (ex. pdMS_TO_TICKS(100)) pour ne pas bloquer indéfiniment et permettre des vérifications périodiques (watchdog, LED).
- **TX** : timeout sur xQueueSend si la file TX est pleine (éviter blocage infini si le récepteur ne consomme pas).

---

## 4. Résumé du cours UART

- **Configuration** : baudrate, format, broches (alternate), horloge RCC.
- **Polling** : simple, bloquant ; TXE/RXNE puis DR.
- **Interruption** : IT RX → buffer ou queue ; IT TX → envoi depuis buffer, désactiver quand vide.
- **DMA** : transferts sans CPU ; fin (ou demi-) de buffer pour traitement.
- **RTOS** : queue RX ISR → tâche ; mutex ou queue TX pour envoi multi-tâches.

---

## Tester sa compréhension

→ [Scénario – Intégration RTOS](scenarios/05-integration-rtos.md) · [Réponse](reponses/05-integration-rtos.md)

---

**Fin du cours UART.**  
Retour à la [vue d'ensemble](README.md) ou passage au cours [SPI et I2C](../../02-spi-i2c/README.md).
