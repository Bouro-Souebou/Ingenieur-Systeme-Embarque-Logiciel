# Réponse – vTaskDelay et tick

Voir [scénario](../scenarios/03-vtaskdelay-tick.md).

---

## Réponse Scénario 1 : Période 100 ms et configTICK_RATE_HZ

**pdMS_TO_TICKS(100)** : convertit 100 ms en nombre de **ticks** (selon configTICK_RATE_HZ). Ex. 1 kHz → 100 ticks.

**Période** : dépend de configTICK_RATE_HZ (résolution du délai) et du temps d'exécution de la tâche avant le delay.

**portMAX_DELAY** : attente infinie ; en production un blocage (file vide, mutex non rendu) peut figer la tâche. Préférer un **timeout** pour détecter les erreurs.

---

## Réponse Scénario 2 : Délai trop court et dérive

**Problème** : Si le traitement dépasse 1 ms, la tâche appelle vTaskDelay(1) alors qu'elle est déjà en retard ; la période effective dépasse 1 ms et peut **dériver** (jitter, période variable).

**Période stable** : Utiliser **vTaskDelayUntil(&prevWakeTime, pdMS_TO_TICKS(100))** : prevWakeTime est mis à jour à chaque réveil ; le délai est ajusté pour que la période soit stable même si le traitement varie. Ou mesurer le temps écoulé (xTaskGetTickCount) et retarder seulement le temps restant.

---

**Retour** : [Scénarios](../scenarios/README.md) · [Leçon 3](../03-vtaskdelay-tick.md)
