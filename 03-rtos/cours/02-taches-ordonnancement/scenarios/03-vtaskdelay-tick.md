# Scénario – vTaskDelay et tick

Pour la leçon [03 – vTaskDelay et tick](../03-vtaskdelay-tick.md).

---

## Scénario 1 : Période 100 ms et configTICK_RATE_HZ

Une tâche doit exécuter une action **toutes les 100 ms**. Le développeur utilise **vTaskDelay(pdMS_TO_TICKS(100))** à la fin de sa boucle.

**Questions** : Que fait pdMS_TO_TICKS(100) ? La période réelle dépend de quoi (configTICK_RATE_HZ) ? Pourquoi éviter portMAX_DELAY en production ?

---

## Scénario 2 : Délai trop court et dérive

Une tâche fait : « lire capteur » puis **vTaskDelay(1)** (1 tick). configTICK_RATE_HZ = 1000, donc 1 ms. Le traitement « lire capteur » prend parfois 2 ms.

**Questions** : Que se passe-t-il (la tâche est déjà en retard quand elle appelle vTaskDelay) ? Comment calculer une période stable (mesurer le temps écoulé, ajuster le délai restant) ?

---

**Réponse** : [../reponses/03-vtaskdelay-tick.md](../reponses/03-vtaskdelay-tick.md) · **Retour** : [Vue d'ensemble](../README.md)
