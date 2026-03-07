# Scénario – Création de tâches (xTaskCreate)

Pour la leçon [01 – Création de tâches](../01-creation-taches.md).

---

## Scénario 1 : Stack en words, pas en octets

On crée une tâche avec **xTaskCreate(ma_tache, "T1", 128, NULL, 1, NULL)**. On pense avoir réservé 128 **octets** de stack.

**Questions** : Quelle est l'unité du 3e paramètre (usStackDepth) sur Cortex-M ? Quelle taille en octets ? Que risque-t-on si la tâche utilise beaucoup de variables locales ?

---

## Scénario 2 : Paramètre passé à la tâche

On veut créer **trois tâches** qui font la même chose (ex. clignoter une LED) mais sur des broches différentes (LED1, LED2, LED3). xTaskCreate accepte un paramètre (pvParameters).

**Questions** : Comment passer le numéro de broche à chaque tâche ? Où allouer la valeur (static, heap, tableau) et pourquoi éviter de passer l'adresse d'une variable de boucle ?

---

**Réponse** : [../reponses/01-creation-taches.md](../reponses/01-creation-taches.md) · **Retour** : [Vue d'ensemble](../README.md)
