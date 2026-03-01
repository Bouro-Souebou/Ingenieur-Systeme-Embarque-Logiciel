# Scénarios – Contraintes à garder en tête

Situations pour vérifier votre compréhension de la [Leçon 5 – Contraintes à garder en tête](../05-contraintes-synthese.md).

---

## Scénario 1 : Buffer partagé sans protection

Deux **tâches** (ou une tâche et une **ISR**) utilisent un **même buffer global** `uint8_t buffer[256]` :
- L’**une** écrit des données (ex. réception UART).
- L’**autre** lit et traite ces données.

Aucun **mutex**, aucune **section critique**, aucun mécanisme de synchronisation. Chacun accède au buffer quand il en a besoin.

**Questions** :
1. Quel **risque** court-on ? (Nom du problème et conséquence possible.)
2. Dans quel **cas** le bug peut-il être rare et difficile à reproduire ?
3. Quelle **solution** recommanderiez-vous (au moins une) ?

---

## Scénario 2 : Stack sous-dimensionnée et printf

Une tâche FreeRTOS est créée avec une **stack de 128 words** (512 octets sur Cortex-M). Dans cette tâche, le développeur appelle **printf** pour afficher un message de debug (avec une chaîne formatée et des entiers).

**Questions** :
1. Pourquoi **printf** est-il particulièrement gourmand en **stack** ?
2. Que peut-il se passer à l’exécution ? (Comportement typique et nom du phénomène.)
3. Quelles **bonnes pratiques** appliquer (dimensionnement, détection, alternative à printf) ?

---

*Après avoir réfléchi, consultez les* [**Éléments de réponse – Contraintes et synthèse**](../reponses/contraintes-synthese.md).

---

**Retour** : [Leçon 5 – Contraintes à garder en tête](../05-contraintes-synthese.md) · [Vue d'ensemble](../README.md)
