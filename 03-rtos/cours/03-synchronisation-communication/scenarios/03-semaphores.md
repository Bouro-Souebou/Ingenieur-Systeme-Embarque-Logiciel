# Scénario – Sémaphores binaires et à compteur

Pour la leçon [03 – Sémaphores](../03-semaphores-binaires-compteur.md).

---

## Scénario 1 : Bouton vs N slots

Une ISR doit **réveiller** une tâche à chaque appui sur un bouton (sans passer de donnée). Une autre partie du code gère **N slots** dans un buffer (prendre un slot = consommer, rendre = libérer).

**Questions** : Quelle primitive pour le bouton (sémaphore binaire, queue, mutex) ? Quelle primitive pour les N slots (sémaphore à compteur, mutex, queue) ?

---

## Scénario 2 : Sémaphore binaire Give en ISR sans réveil

L'ISR fait **xSemaphoreGiveFromISR(sem, NULL)** (deuxième paramètre NULL). La tâche qui fait Take(sem) se réveille parfois avec un délai notable.

**Questions** : Pourquoi NULL est problématique ? Que doit-on passer (BaseType_t *pxHigherPriorityTaskWoken) et que faire après GiveFromISR avec ce pointeur ?

---

**Réponse** : [../reponses/03-semaphores.md](../reponses/03-semaphores.md) · **Retour** : [Vue d'ensemble](../README.md)
