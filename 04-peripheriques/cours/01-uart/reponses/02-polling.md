# Réponse – Envoi et réception en polling

Voir [scénario](../scenarios/02-polling.md).

---

## Réponse Scénario 1 : Envoi d'une chaîne

**Troncature** : Si on écrit l'octet suivant **avant** que le précédent ait été envoyé (registre DR encore occupé), le matériel peut écraser la donnée ou n'envoyer qu'une partie. Il faut **attendre** que le buffer d'émission soit vide.

**Flag TXE** : **TXE** (Transmit Data Register Empty) = 1 signifie qu'on peut écrire le prochain octet dans DR. Boucle : `while (!(USART1->SR & USART_SR_TXE));` puis `USART1->DR = byte;`. Pour une chaîne : faire cette séquence pour chaque caractère.

**Reference Manual** : Section USART du manuel du MCU : registre **SR** (Status Register), bit **TXE** (souvent bit 7). Nom exact selon la famille (STM32 : USART_SR_TXE).

---

## Réponse Scénario 2 : Réception bloquante

**Réactivité** : La fonction **uart_recv_byte()** reste en boucle tant qu'aucun caractère n'arrive ; le code ne **revient jamais** à la partie qui lit le bouton. Une seule instruction à la fois : soit on attend l'UART, soit on lit le bouton — en polling pur, on ne peut pas faire les deux de façon réactive.

**Polling acceptable** : Debug minimal (quelques printf au démarrage), script séquentiel où le blocage est voulu (attendre une réponse avant de continuer).

**Alternative** : **Mode interruption** (ISR RX stocke dans buffer ou queue) ; ou **RTOS** avec une tâche qui fait xQueueReceive avec **timeout** pour vérifier le bouton périodiquement. Ainsi la CPU n'est pas bloquée en attendant un caractère.

---

**Retour** : [Scénarios](../scenarios/README.md) · [Leçon 2](../02-polling.md)
