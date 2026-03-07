# Scénario – Files d'attente (queues)

Pour la leçon [03 – Files d'attente](../03-files-attente.md).

---

## Scénario 1 : Flag volatile et valeur de l'octet

Une ISR reçoit un octet UART ; une tâche doit le traiter. On utilise uniquement un **flag** volatile « donnée reçue ».

**Questions** : Quel problème (valeur de l'octet) ? Pourquoi une **queue** est-elle adaptée ici ? Quelle différence avec un sémaphore ?

---

## Scénario 2 : Plusieurs producteurs, un consommateur

Une tâche « capteur » et une ISR « UART » envoient toutes les deux des données à une tâche « traitement ». Avec un seul flag, on ne sait pas qui a produit la donnée.

**Questions** : Pourquoi une queue (avec type de message ou source) est-elle préférable à un flag ? Comment une queue préserve-t-elle l'ordre et la source des messages ?

---

**Réponse** : [../reponses/03-files-attente.md](../reponses/03-files-attente.md) · **Retour** : [Vue d'ensemble](../README.md)
