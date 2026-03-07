# Réponse – Files d'attente

Voir [scénario](../scenarios/03-files-attente.md).

---

## Réponse Scénario 1 : Flag volatile et valeur de l'octet

**Problème** : Un flag indique « quelque chose est arrivé » mais pas **quelle valeur** (l'octet). Il faudrait un buffer partagé + indices, avec risque de **race** et complexité.

**Queue** : La queue **transporte la donnée** (l'octet). L'ISR envoie l'octet, la tâche reçoit. Le RTOS gère la synchro. Si la file est vide, la tâche peut bloquer jusqu'à réception (ou timeout).

**Vs sémaphore** : Le sémaphore **signale** un événement (Give/Take) mais **sans payload**. Pour passer l'octet, il faut une **queue** ; un sémaphore seul ne suffit pas pour la valeur.

---

## Réponse Scénario 2 : Plusieurs producteurs, un consommateur

**Queue** : Chaque message peut contenir un **type** ou un **identifiant de source** (ex. structure { source_t src; uint8_t data; }). La tâche consommateur reçoit et traite selon la source. La queue garantit l'**ordre FIFO** et évite les races (un seul récepteur, buffer géré par le RTOS).

**Vs flag** : Un seul flag ne peut pas distinguer capteur vs UART ; avec deux flags on perd l'ordre et on complique la logique. Une queue avec un champ « source » ou des queues séparées par producteur est plus propre.

---

**Retour** : [Scénarios](../scenarios/README.md) · [Leçon 3](../03-files-attente.md)
