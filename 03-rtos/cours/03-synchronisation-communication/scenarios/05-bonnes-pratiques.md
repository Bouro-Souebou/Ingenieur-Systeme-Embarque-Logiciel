# Scénario – Bonnes pratiques et synthèse

Pour la leçon [05 – Bonnes pratiques et synthèse](../05-bonnes-pratiques-synthese.md).

---

## Scénario 1 : Caractères perdus à débit élevé

L'ISR UART envoie des octets dans une queue avec **SendFromISR**. À débit élevé, des caractères sont **perdus**.

**Questions** : Cause probable (file pleine) ? Que retourne SendFromISR si la file est pleine ? Que faire pour limiter les pertes (taille queue, priorité tâche) ?

---

## Scénario 2 : Plusieurs tâches qui envoient dans la même queue

Trois tâches productrices envoient des commandes (structure { type, valeur }) dans **une seule queue**. Une tâche consommateur traite les commandes. Parfois l'ordre de traitement semble incohérent.

**Questions** : Une queue FIFO suffit-elle pour l'ordre (oui, FIFO par file) ? D'où peut venir l'« incohérence » (priorités, ordre d'envoi réel, ou logique métier) ? Quand utiliser une queue par producteur vs une queue commune ?

---

**Réponse** : [../reponses/05-bonnes-pratiques.md](../reponses/05-bonnes-pratiques.md) · **Retour** : [Vue d'ensemble](../README.md)
