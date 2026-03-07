# Scénario – Mutex : exclusion mutuelle

Pour la leçon [04 – Mutex](../04-mutex-exclusion-mutuelle.md).

---

## Scénario 1 : vTaskDelay entre Take et Give

Une tâche prend un **mutex**, appelle **vTaskDelay(100)** « pour laisser du temps aux autres », fait un calcul, puis rend le mutex.

**Questions** : Pourquoi est-ce une mauvaise pratique ? Que subissent les autres tâches qui attendent le mutex ? Que doit contenir la section entre Take et Give ?

---

## Scénario 2 : Prendre le mutex dans une ISR

On souhaite qu'une ISR lise une variable protégée par un mutex en dehors de l'ISR. Le développeur appelle **xSemaphoreTake(mutex, 0)** dans l'ISR.

**Questions** : Pourquoi Take dans une ISR est interdit ou dangereux (blocage) ? Quelle alternative (queue, section critique courte, tâche dédiée notifiée par l'ISR) ?

---

**Réponse** : [../reponses/04-mutex.md](../reponses/04-mutex.md) · **Retour** : [Vue d'ensemble](../README.md)
