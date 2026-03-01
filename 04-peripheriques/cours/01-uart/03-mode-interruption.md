# Leçon 3 – Mode interruption

## Objectif de la leçon

Utiliser les **interruptions** UART pour l'**émission** (IT TX : envoyer l'octet suivant quand le buffer est vide) et la **réception** (IT RX : à chaque octet reçu, le copier dans un **buffer circulaire** ou une queue). La CPU n'est plus bloquée ; on peut combiner avec un RTOS.

---

## 1. Interruption de réception (RX)

À chaque **octet reçu**, le périphérique lève une **interruption** (flag RXNE ou équivalent). L'**ISR** doit :

1. **Lire** l'octet depuis le registre DR (ce qui clear le flag).
2. **Stocker** l'octet dans un **buffer circulaire** (ring buffer) ou l'**envoyer** dans une **queue** FreeRTOS (xQueueSendFromISR) pour qu'une tâche le traite.

Si on utilise un buffer circulaire, une **tâche** ou la **boucle principale** lit ensuite ce buffer (indices head/tail, protection si accès multi-tâches). Si on utilise une **queue** FreeRTOS, une tâche fait **xQueueReceive** et parse les commandes ou affiche les données. L'ISR reste **courte** : lire DR, mettre en buffer ou en queue, éventuellement portYIELD_FROM_ISR.

---

## 2. Interruption d'émission (TX)

Quand le **registre d'émission** est vide (octet envoyé), le périphérique peut générer une **interruption** (TXE). L'**ISR** :

1. Vérifie s'il reste des **octets à envoyer** (buffer ou queue).
2. Si oui : écrire le prochain octet dans **DR** (l'interruption se déclenchera à nouveau quand cet octet sera envoyé).
3. Si non : **désactiver** l'interruption TX pour ne pas appeler l'ISR en continu quand il n'y a rien à envoyer.

On réactive l'interruption TX quand une tâche (ou le code) ajoute de nouvelles données à envoyer. Ainsi, l'envoi se fait **en arrière-plan** sans bloquer la CPU (sauf si le buffer est plein et qu'on attend).

---

## 3. Buffer circulaire (ring buffer) pour RX

Un **buffer circulaire** est un tableau avec deux **indices** : **head** (où on écrit le prochain octet reçu) et **tail** (où on lit le prochain octet à consommer). L'ISR incrémente **head** après avoir écrit ; la tâche incrémente **tail** après avoir lu. Si head == tail, le buffer est vide ; si (head+1) % size == tail, le buffer est plein (on peut perdre un octet ou signaler overflow). L'accès depuis l'ISR et depuis la tâche doit être **protégé** (section critique ou variables atomiques) pour éviter les race conditions.

---

## 4. Avantages du mode interruption

- La CPU n'est **pas bloquée** pendant l'attente d'un caractère : d'autres tâches ou la boucle principale peuvent s'exécuter.
- **Réactivité** : dès qu'un octet arrive, l'ISR le stocke ; une tâche peut le traiter (commande, affichage).
- **Compatible RTOS** : queue entre ISR RX et tâche de traitement ; mutex ou queue pour TX si plusieurs tâches envoient.

---

## Points clés à retenir

- **IT RX** : à chaque octet reçu, ISR lit DR et met en **buffer circulaire** ou **queue** ; tâche consomme les données.
- **IT TX** : ISR envoie l'octet suivant depuis un buffer ; **désactiver** l'IT TX quand il n'y a plus rien à envoyer.
- Garder l'**ISR courte** ; utiliser une **queue** FreeRTOS pour lier proprement ISR et tâche.

---

**Suite** : [Leçon 4 – DMA avec UART (optionnel)](04-dma-uart.md)
