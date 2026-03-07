# Réponse – FreeRTOS en bref

Voir [scénario](../scenarios/05-freertos-en-bref.md).

---

## Réponse Scénario 1 : vTaskStartScheduler ne revient pas

**Ce n'est pas un bug.** vTaskStartScheduler() **démarre l'ordonnanceur** et **ne revient pas** en fonctionnement normal : le CPU est géré par l'ordonnanceur, qui alterne entre les tâches.

**Elle revient** seulement en cas d'**erreur** (ex. heap insuffisant pour la tâche idle, config invalide). Prévoir alors une boucle de secours ou un indicateur d'erreur.

**Piège** : Mettre du code après vTaskStartScheduler() en espérant qu'il s'exécute : il ne sera jamais atteint si le scheduler tourne.

---

## Réponse Scénario 2 : Pas d'appel à vTaskStartScheduler

**Pourquoi** : Les tâches créées par xTaskCreate sont seulement **enregistrées** dans le noyau ; elles ne s'exécutent pas tant que l'**ordonnanceur** n'est pas démarré. Sans vTaskStartScheduler(), main() continue et se termine ; le CPU ne passe jamais aux tâches.

**Rôle** : vTaskStartScheduler() **lance la boucle de l'ordonnanceur** : il choisit une tâche Ready, la fait exécuter, gère les blocages (delays, queues, etc.). C'est le point d'entrée du multitâche ; après cet appel, ce n'est plus main() qui « pilote », c'est le scheduler.

---

**Retour** : [Scénarios](../scenarios/README.md) · [Leçon 5](../05-freertos-en-bref.md)
