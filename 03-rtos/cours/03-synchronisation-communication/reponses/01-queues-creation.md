# Réponse – Queues : création, envoi et réception

Voir [scénario](../scenarios/01-queues-creation.md).

---

## Réponse Scénario 1 : File vide et portMAX_DELAY

**Blocage** : La file est **vide** ; xQueueReceive(..., portMAX_DELAY) **attend indéfiniment** qu'un élément arrive. Si personne n'envoie (ex. UART pas encore configuré, pas d'ISR), la tâche reste **Blocked**.

**portMAX_DELAY** : attendre sans limite de temps (blocage jusqu'à réception).

**Alternative** : Utiliser un **timeout** : xQueueReceive(q, &byte, pdMS_TO_TICKS(100)) pour se réveiller toutes les 100 ms si rien n'arrive (permet de détecter un problème ou de faire autre chose).

---

## Réponse Scénario 2 : Envoi sans réception (file pleine)

**Pourquoi** : La queue a une **taille fixe** (ex. 10 éléments). Après 10 envois sans réception, la file est **pleine**.

**xQueueSend(..., portMAX_DELAY)** : **bloque** jusqu'à ce qu'une place se libère (qu'une tâche fasse Receive). En ISR on ne peut pas bloquer → utiliser SendFromISR et gérer errQUEUE_FULL.

**Taille et débit** : Choisir la taille selon le débit producteur/consommateur et la latence acceptable. Si le producteur va plus vite : augmenter la taille, augmenter la priorité du consommateur, ou accepter de perdre des éléments (timeout en Send, ou en ISR ignorer/logger errQUEUE_FULL).

---

**Retour** : [Scénarios](../scenarios/README.md) · [Leçon 1](../01-queues-creation-envoi-reception.md)
