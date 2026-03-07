# Scénario – Mode interruption UART

Pour la leçon [03 – Mode interruption](../03-mode-interruption.md).

---

## Scénario 1 : IT RX et buffer

L'ISR de réception UART lit l'octet dans **DR** et l'écrit dans un **buffer circulaire**. Une tâche lit ce buffer pour construire des lignes de commande. Parfois un octet semble manquer ou être dupliqué.

**Questions** : Comment le buffer circulaire gère-t-il **head** et **tail** (qui écrit, qui lit) ? Pourquoi faut-il **protéger** l'accès au buffer si l'ISR et la tâche y accèdent (race condition) ? Alternative : queue FreeRTOS au lieu du buffer ?

---

## Scénario 2 : IT TX laissée active

Après avoir envoyé tous les octets du buffer TX, le développeur ne désactive pas l'**interruption TX**. Le programme ralentit et consomme beaucoup de CPU.

**Questions** : Pourquoi l'IT TX se déclenche-t-elle encore quand il n'y a plus rien à envoyer (registre vide) ? Que faire dans l'ISR quand le buffer TX est vide (désactiver l'IT TX) ? Quand réactiver l'IT TX (à l'ajout de nouvelles données) ?

---

**Réponse** : [../reponses/03-mode-interruption.md](../reponses/03-mode-interruption.md) · **Retour** : [Vue d'ensemble](../README.md)
