# Réponse – Pourquoi un RTOS ?

Voir [scénario](../scenarios/01-pourquoi-rtos.md).

---

## Réponse Scénario 1 : Super-loop et délais multiples

**Problème** : Un seul fil d'exécution ; chaque traitement bloque les autres. Garantir 10 ms, 100 ms et 50 ms en même temps devient complexe (flags, machines à états).

**Solution** : RTOS = plusieurs **tâches**, **ordonnancement préemptif** (priorités), **primitives** (délais, files, sémaphores). Chaque activité a sa période ou réagit à un événement sans bloquer les autres.

---

## Réponse Scénario 2 : Blocage d'une routine longue

**Risque** : Pendant 200 ms, la boucle est bloquée ; le bouton d'urgence n'est pas lu → **réactivité non garantie**, possible dépassement de la contrainte temps réel.

**Solution RTOS** : Une **tâche dédiée** pour l'envoi radio (bloquée sur ACK ou timeout) ; une autre tâche **haute priorité** pour le bouton (ou ISR + sémaphore). L'ordonnanceur donne le CPU à la tâche bouton dès qu'elle est prête, sans attendre la fin de l'envoi radio.

---

**Retour** : [Scénarios](../scenarios/README.md) · [Leçon 1](../01-pourquoi-rtos.md)
