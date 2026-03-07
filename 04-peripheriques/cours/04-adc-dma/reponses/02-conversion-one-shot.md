# Réponse – Conversion one-shot

Voir [scénario](../scenarios/02-conversion-one-shot.md).

---

## Réponse Scénario 1 : Polling et EOC

**EOC** : Indique que la conversion est **terminée** et que **DR** contient la nouvelle valeur. Lire DR avant EOC peut donner l'**ancienne** valeur ou une valeur indéfinie.

**Timeout** : Si l'ADC ne termine pas (bug, canal inexistant, horloge coupée), la boucle **while** peut être **infinie**. Un timeout (compteur ou timer) permet d'abandonner et de signaler une erreur.

---

## Réponse Scénario 2 : Mode interruption

**ISR courte** : Pour limiter la latence et le temps en contexte interrupt. Lire DR, écrire dans une variable ou **xQueueSendFromISR** vers une tâche.

**RTOS** : Envoyer la valeur dans une **queue** ou utiliser une **notification** pour qu'une tâche traite (affichage, seuil). Éviter de faire un traitement lourd en ISR.

**Clear EOC** : Sur beaucoup de MCU, la **lecture de DR** clear automatiquement EOC. Consulter le Reference Manual.

---

**Retour** : [Scénarios](../scenarios/README.md) · [Leçon 2](../02-conversion-one-shot.md)
