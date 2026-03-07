# Scénario – Intégration UART et RTOS

Pour la leçon [05 – Intégration RTOS](../05-integration-rtos.md).

---

## Scénario 1 : Queue RX entre ISR et tâche

L'ISR UART RX envoie chaque octet reçu dans une **queue** FreeRTOS. Une tâche fait **xQueueReceive** pour parser les commandes. À 115200 baud, des caractères sont parfois perdus.

**Questions** : Quelle peut être la cause (tâche pas assez prioritaire, queue trop petite) ? Pourquoi utiliser **xQueueSendFromISR** et **portYIELD_FROM_ISR** dans l'ISR ? Quel **timeout** mettre sur xQueueReceive (éviter blocage infini, permettre watchdog) ?

---

## Scénario 2 : Plusieurs tâches qui envoient sur l'UART

Deux tâches appellent parfois **printf** ou une fonction d'envoi UART en même temps. Les messages sont entremêlés (alternance de caractères de deux lignes).

**Questions** : Pourquoi le mélange (pas d'exclusion mutuelle sur l'accès au registre DR) ? Quelle solution avec un **mutex** (une tâche « envoi » détient le mutex, les autres mettent leur message dans une queue) ? Ou une **queue TX** unique avec une tâche dédiée qui envoie les octets ?

---

**Réponse** : [../reponses/05-integration-rtos.md](../reponses/05-integration-rtos.md) · **Retour** : [Vue d'ensemble](../README.md)
