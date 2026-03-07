# Scénario – Tâches : unité d'exécution

Pour la leçon [02 – Tâches : unité d'exécution](../02-taches-unite-execution.md).

---

## Scénario 1 : printf et mélange de sorties

Une tâche FreeRTOS contient un **printf** dans sa boucle. Une autre tâche affiche aussi des messages. Les sorties se mélangent et le système ralentit.

**Questions** : Pourquoi les messages se mélangent (une seule tâche Running) ? Pourquoi le ralentissement ? Que faire pour éviter les conflits sur printf ?

---

## Scénario 2 : Variable partagée sans protection

Deux tâches lisent et écrivent une variable globale **compteur**. Parfois la valeur finale après 1000 incrémentations par chaque tâche n'est pas 2000.

**Questions** : Quelle est la cause (contexte préemptif, section non atomique) ? En quoi la tâche comme « unité d'exécution » n'empêche pas ce problème ? Quelle primitive utiliser (mutex, section critique) ?

---

**Réponse** : [../reponses/02-taches-unite-execution.md](../reponses/02-taches-unite-execution.md) · **Retour** : [Vue d'ensemble](../README.md)
