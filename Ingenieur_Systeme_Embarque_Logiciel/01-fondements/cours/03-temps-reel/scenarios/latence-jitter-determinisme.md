# Scénarios – Latence, jitter et déterminisme

Situations pour vérifier votre compréhension de la [Leçon 2 – Latence, jitter et déterminisme](../02-latence-jitter-determinisme.md).

---

## Scénario 1 : malloc dans une boucle de régulation

Une **boucle de régulation** (contrôle moteur) doit s'exécuter **toutes les 1 ms**. Pour traiter les données, le développeur alloue à chaque période un **petit buffer** avec `malloc(64)` et le libère avec `free()` en fin de boucle.

**Questions** :
1. Quel problème cela pose-t-il pour le **déterminisme** et le **jitter** ?
2. Que peut-il se passer après plusieurs heures de fonctionnement ?

---

## Scénario 2 : Attente sur un flag sans timeout

Dans une tâche temps réel, on trouve le code suivant :

```c
while (!flag_capteur_pret) {
    /* attendre que l'ISR ait mis flag_capteur_pret à 1 */
}
```

L'interruption qui met `flag_capteur_pret` à 1 est déclenchée par un capteur. Un jour, le capteur est déconnecté ou défaillant.

**Question** : Que se passe-t-il pour la tâche et pour le système ? Quel principe du cours (latence, déterminisme, WCET) est violé ?

---

*Après avoir réfléchi, consultez les* [**Éléments de réponse – Latence, jitter, déterminisme**](../reponses/latence-jitter-determinisme.md).

---

**Retour** : [Leçon 2 – Latence, jitter et déterminisme](../02-latence-jitter-determinisme.md) · [Vue d'ensemble](../README.md)
