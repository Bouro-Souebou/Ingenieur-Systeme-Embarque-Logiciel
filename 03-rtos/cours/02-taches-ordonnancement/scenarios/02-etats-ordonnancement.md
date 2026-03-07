# Scénario – États et ordonnancement

Pour la leçon [02 – États et ordonnancement](../02-etats-ordonnancement.md).

---

## Scénario 1 : Deux tâches de même priorité

Deux tâches ont la **même priorité**. Une seule semble s'exécuter ; l'autre ne démarre pas.

**Questions** : Comment l'ordonnanceur gère-t-il deux tâches Ready de même priorité ? Pourquoi une tâche pourrait-elle ne jamais s'exécuter (autre cause que la priorité) ?

---

## Scénario 2 : Tâche qui reste Blocked

Une tâche attend **xQueueReceive(..., portMAX_DELAY)**. Aucune autre tâche n'envoie jamais dans cette queue.

**Questions** : Dans quel état est cette tâche (Blocked) ? Que se passe-t-il pour les autres tâches (elles s'exécutent normalement) ? Que faire pour débloquer la tâche (envoyer dans la queue, ou timeout au lieu de portMAX_DELAY) ?

---

**Réponse** : [../reponses/02-etats-ordonnancement.md](../reponses/02-etats-ordonnancement.md) · **Retour** : [Vue d'ensemble](../README.md)
