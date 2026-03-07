# Réponse – Mutex

Voir [scénario](../scenarios/04-mutex.md).

---

## Réponse Scénario 1 : vTaskDelay entre Take et Give

**Mauvaise pratique** : **vTaskDelay** entre Take et Give **bloque la tâche en gardant le mutex** → les autres tâches qui attendent le mutex restent bloquées inutilement (latence, mauvaise réactivité).

**Section Take–Give** : Doit contenir **uniquement** l'accès à la ressource partagée. Pas de delay, pas de calcul lourd, pas d'attente sur une autre primitive. Sections **courtes**.

---

## Réponse Scénario 2 : Prendre le mutex dans une ISR

**Interdit** : **xSemaphoreTake** peut **bloquer** (timeout > 0). Une ISR ne doit **jamais** bloquer ; le noyau n'attend pas en ISR. Take(mutex, 0) pourrait retourner immédiatement si le mutex est libre, mais en général les mutex sont pour la **synchronisation entre tâches** ; en ISR on évite.

**Alternatives** : (1) **Queue** : l'ISR envoie un message (SendFromISR), une **tâche dédiée** fait Take(mutex), lit/écrit la ressource, Give(mutex). (2) **Section critique** très courte : taskENTER_CRITICAL / taskEXIT_CRITICAL si la lecture en ISR est minimale. (3) Variable lue en ISR, écrite en tâche avec protection (mutex côté tâche uniquement).

---

**Retour** : [Scénarios](../scenarios/README.md) · [Leçon 4](../04-mutex-exclusion-mutuelle.md)
