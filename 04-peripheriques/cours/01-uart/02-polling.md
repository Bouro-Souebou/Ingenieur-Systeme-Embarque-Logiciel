# Leçon 2 – Envoi et réception en polling

## Objectif de la leçon

Savoir **envoyer** et **recevoir** un octet (ou une chaîne) en **polling** : attendre que le périphérique soit prêt en lisant les bits de statut **TXE** (Transmit Data Register Empty) et **RXNE** (Read Data Register Not Empty). Comprendre les limites (blocage du CPU).

---

## 1. Registres de statut et de données

L'UART expose typiquement :

- Un registre de **statut** (SR) avec des **flags** : **TXE** = 1 quand le registre d'émission est vide (on peut envoyer l'octet suivant) ; **RXNE** = 1 quand une donnée a été reçue (on peut lire).
- Un registre de **données** (DR) : **écriture** = envoi d'un octet ; **lecture** = réception d'un octet (et clear du flag RXNE selon le MCU).

Les noms et offsets exacts sont dans le **Reference Manual** (ex. USART_SR, USART_DR sur STM32).

---

## 2. Envoi d'un octet (polling)

Pour envoyer un octet, on attend que **TXE** soit à 1 (buffer d'émission vide), puis on écrit l'octet dans **DR** :

```c
void uart_send_byte(uint8_t b) {
    while (!(USART1->SR & USART_SR_TXE))
        ;
    USART1->DR = b;
}
```

La boucle **bloque** tant que le précédent octet n'a pas été envoyé. Pour envoyer une chaîne, on appelle cette fonction en boucle (ou on envoie octet par octet avec le même schéma).

---

## 3. Réception d'un octet (polling)

Pour recevoir un octet, on attend que **RXNE** soit à 1 (donnée disponible), puis on lit **DR** (la lecture peut automatiquement clear RXNE) :

```c
uint8_t uart_recv_byte(void) {
    while (!(USART1->SR & USART_SR_RXNE))
        ;
    return (uint8_t)(USART1->DR & 0xFF);
}
```

La boucle **bloque** tant qu'aucun caractère n'est reçu. Si aucun caractère n'arrive jamais, le programme reste bloqué.

---

## 4. Avantages et limites du polling

**Avantages** : mise en œuvre **simple**, pas de gestion d'interruption ni de buffer. Adapté au **debug** minimal (envoyer quelques messages au démarrage) ou à des échanges **occasionnels** où le blocage est acceptable.

**Limites** : la CPU est **bloquée** pendant l'attente. On ne peut pas faire autre chose (réagir à un bouton, gérer une autre tâche) pendant l'envoi ou la réception. Pour un **débit** soutenu ou une **réactivité** globale, il faut passer au **mode interruption** (ou DMA).

---

## Points clés à retenir

- **TXE** = 1 → on peut écrire dans DR (envoi). **RXNE** = 1 → on peut lire DR (réception).
- **Polling** = boucle d'attente sur le flag puis lecture/écriture de DR ; **bloquant**.
- Utiliser le polling pour du **debug** ou des échanges **légers** ; pour le reste, préférer les **interruptions**.

---

## Tester sa compréhension

→ [Scénario – Envoi et réception en polling](scenarios/02-polling.md) · [Réponse](reponses/02-polling.md)

---

**Suite** : [Leçon 3 – Mode interruption](03-mode-interruption.md)
