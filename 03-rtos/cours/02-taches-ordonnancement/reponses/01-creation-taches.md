# Réponse – Création de tâches

Voir [scénario](../scenarios/01-creation-taches.md).

---

## Réponse Scénario 1 : Stack en words, pas en octets

**Unité** : usStackDepth = taille en **words** (Cortex-M : 1 word = 4 octets). 128 → **512 octets**.

**Risque** : Stack trop petite → **overflow** → crash. Dimensionner selon appels et variables locales ; utiliser high water mark.

---

## Réponse Scénario 2 : Paramètre passé à la tâche

**Comment** : Passer **pvParameters** = pointeur vers la valeur (ex. (void*)LED_GPIO_PIN). Dans la tâche : `uint32_t pin = (uint32_t) pvParameters;` puis utiliser pin.

**Où allouer** : Variable **static** ou tableau global, ou allocation heap ; chaque tâche doit recevoir une **adresse valide pour toute la durée de vie** de la tâche. **Éviter** : dans une boucle `for (i=0; i<3; i++) xTaskCreate(..., &i, ...)` car &i est la même pour toutes les tâches et la valeur peut changer avant que la tâche lise → passer une copie (ex. tableau `uint32_t pins[] = {1,2,3}` et passer &pins[i] ou allouer une copie).

---

**Retour** : [Scénarios](../scenarios/README.md) · [Leçon 1](../01-creation-taches.md)
