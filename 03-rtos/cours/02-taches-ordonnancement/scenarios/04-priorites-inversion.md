# Scénario – Priorités et inversion

Pour la leçon [04 – Priorités et inversion](../04-priorites-inversion.md).

---

## Scénario 1 : Inversion de priorité et mutex

Une tâche **basse priorité** tient un **mutex** ; une tâche **haute priorité** attend ce mutex et reste bloquée.

**Questions** : Quel phénomène (inversion de priorité) ? En quoi le mutex avec **héritage de priorité** (FreeRTOS) aide-t-il ? Que faire côté conception pour limiter le risque ?

---

## Scénario 2 : Priorité moyenne qui bloque la haute

Trois tâches : **H** (haute), **M** (moyenne), **L** (basse). L tient un mutex ; H attend le mutex. M est Ready et s'exécute (elle ne touche pas au mutex).

**Questions** : Pourquoi H ne reprend pas dès que L rend le mutex (M peut s'exécuter entre L et H) ? En quoi l'héritage de priorité (L grimpe à la priorité de H) limite le problème ?

---

**Réponse** : [../reponses/04-priorites-inversion.md](../reponses/04-priorites-inversion.md) · **Retour** : [Vue d'ensemble](../README.md)
