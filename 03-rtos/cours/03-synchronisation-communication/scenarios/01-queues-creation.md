# Scénario – Queues : création, envoi et réception

Pour la leçon [01 – Queues : création, envoi et réception](../01-queues-creation-envoi-reception.md).

---

## Scénario 1 : File vide et portMAX_DELAY

On crée une queue **xQueueCreate(10, sizeof(uint8_t))** et une tâche fait **xQueueReceive(q, &byte, portMAX_DELAY)**. Parfois le programme semble bloqué au démarrage.

**Questions** : Pourquoi (file vide) ? Que fait portMAX_DELAY ? Quelle alternative pour éviter un blocage infini (timeout) ?

---

## Scénario 2 : Envoi sans réception (file pleine)

Une tâche envoie des octets dans une queue avec **xQueueSend(..., portMAX_DELAY)**. Aucune autre tâche ne fait xQueueReceive. Après N envois, le programme bloque.

**Questions** : Pourquoi (taille de la file) ? Que fait xQueueSend quand la file est pleine avec portMAX_DELAY ? Quelle taille de file choisir et que faire si le producteur va plus vite que le consommateur ?

---

**Réponse** : [../reponses/01-queues-creation.md](../reponses/01-queues-creation.md) · **Retour** : [Vue d'ensemble](../README.md)
