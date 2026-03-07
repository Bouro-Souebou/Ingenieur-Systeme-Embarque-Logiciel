# Réponse – Mode interruption UART

Voir [scénario](../scenarios/03-mode-interruption.md).

---

## Réponse Scénario 1 : IT RX et buffer

**Head / tail** : L'**ISR** écrit à l'indice **head** et fait head = (head+1) % size. La **tâche** lit à l'indice **tail** et fait tail = (tail+1) % size. Buffer vide : head == tail. Buffer plein : (head+1) % size == tail (gestion overflow : perdre ou signaler).

**Protection** : L'ISR peut modifier **head** pendant que la tâche lit **tail** ou les données ; sans protection, la tâche peut lire un indice incohérent ou un octet à moitié écrit. Solutions : **section critique** (désactiver interruptions courtement), ou **queue FreeRTOS** : l'ISR fait xQueueSendFromISR, la tâche fait xQueueReceive — le RTOS gère la synchro.

**Queue** : Plus simple que le buffer circulaire manuel ; pas de gestion head/tail ni de protection à coder soi-même ; adapté à une tâche qui consomme les octets (parsing, commandes).

---

## Réponse Scénario 2 : IT TX laissée active

**Déclenchement** : L'interruption **TXE** se déclenche quand le **registre d'émission est vide** (octet envoyé). Si on n'a plus de donnée à envoyer mais qu'on ne désactive pas l'IT, le registre reste vide → l'IT se déclenche **en continu** (ou à chaque tick selon le MCU), l'ISR est appelée en boucle → **gaspillage CPU**.

**ISR** : Quand le buffer TX est **vide** : **désactiver** l'interruption TX (bit IT TXE dans le registre de contrôle). Ainsi l'ISR ne sera plus appelée tant qu'on ne réactive pas.

**Réactivation** : Dès qu'on **ajoute** de nouvelles données à envoyer (une tâche remplit le buffer ou envoie dans une queue TX), réactiver l'IT TX ; l'ISR enverra le premier octet, puis les suivants à chaque TXE.

---

**Retour** : [Scénarios](../scenarios/README.md) · [Leçon 3](../03-mode-interruption.md)
