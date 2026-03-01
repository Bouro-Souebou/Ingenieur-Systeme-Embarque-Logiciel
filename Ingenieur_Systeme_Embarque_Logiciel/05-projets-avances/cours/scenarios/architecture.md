# Scénarios – Architecture logicielle embarquée

Pour le cours [5.1 – Architecture logicielle](01-architecture-logicielle.md).

---

## Scénario 1 : Couches et dépendances

Le **driver** UART appelle une fonction `app_notify_error()` déclarée dans l’application. Quel principe d’architecture est violé ? Que risque-t-on pour les tests et le portage ?

---

## Scénario 2 : Configuration et portage

Broches et fréquences sont codées en dur dans plusieurs `.c`. On porte le projet sur une autre carte. Comment organiser le code pour faciliter le portage ?

---

**Réponses** : [reponses/architecture.md](../reponses/architecture.md).

**Retour** : [5.1 – Architecture](01-architecture-logicielle.md) · [Vue 05](../../README.md)
