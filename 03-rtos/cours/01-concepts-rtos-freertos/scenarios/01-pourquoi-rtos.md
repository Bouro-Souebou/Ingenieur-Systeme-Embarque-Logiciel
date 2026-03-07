# Scénario – Pourquoi un RTOS ?

Pour la leçon [01 – Pourquoi un RTOS ?](../01-pourquoi-rtos.md).

---

## Scénario 1 : Super-loop et délais multiples

Une application doit : lire un capteur toutes les **10 ms**, envoyer un message toutes les **100 ms**, réagir à un bouton en **< 50 ms**. On utilise une super-loop avec delays et flags.

**Questions** : Pourquoi c'est difficile à maintenir ? Qu'apporte un RTOS (tâches, ordonnancement) ?

---

## Scénario 2 : Blocage d'une routine longue

Dans une super-loop, une fonction « envoi paquet radio » prend **200 ms** (attente ACK). Pendant ce temps, le bouton d'urgence n'est pas scruté.

**Questions** : Quel est le risque pour la réactivité ? Comment un RTOS (tâche dédiée, non-bloquante) résout-il le problème ?

---

**Réponse** : [../reponses/01-pourquoi-rtos.md](../reponses/01-pourquoi-rtos.md) · **Retour** : [Vue d'ensemble](../README.md)
