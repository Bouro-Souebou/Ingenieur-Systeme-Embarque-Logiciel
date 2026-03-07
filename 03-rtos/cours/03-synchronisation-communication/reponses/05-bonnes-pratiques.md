# Réponse – Bonnes pratiques

Voir [scénario](../scenarios/05-bonnes-pratiques.md).

---

## Réponse Scénario 1 : Caractères perdus à débit élevé

**Cause** : La **queue** est **pleine** ; SendFromISR retourne **errQUEUE_FULL** → l'octet est **perdu** (l'ISR ne peut pas bloquer).

**Limiter les pertes** : **Augmenter** la taille de la queue ; **augmenter** la priorité de la tâche qui consomme ; ou accepter la perte et gérer l'erreur (log, indicateur).

---

## Réponse Scénario 2 : Plusieurs tâches qui envoient dans la même queue

**FIFO** : Une queue FreeRTOS est **FIFO** ; l'ordre d'extraction reflète l'ordre d'insertion **dans cette file**. Donc une queue commune préserve l'ordre d'arrivée des messages.

**Incohérence possible** : (1) **Priorités** : une tâche prioritaire peut envoyer « entre » deux envois d'une tâche moins prioritaire → ordre perçu différent de l'ordre métier. (2) **Logique** : si le consommateur traite selon le type de commande, l'ordre peut sembler incohérent selon la sémantique. (3) **Bugs** : oubli de champ, mauvaise initialisation.

**Queue commune vs une par producteur** : **Une queue commune** : ordre global FIFO, simple. **Une queue par producteur** : si le consommateur doit traiter par source (round-robin, priorité par type de producteur) ou éviter qu'un producteur lent bloque les autres. Selon les besoins métier.

---

**Retour** : [Scénarios](../scenarios/README.md) · [Leçon 5](../05-bonnes-pratiques-synthese.md)
