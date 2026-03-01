# Réponses – Architecture logicielle

Voir [scénarios](../scenarios/architecture.md).

---

## Scénario 1 : Couches et dépendances

**Problème** : Le driver (couche basse) dépend de l’application (couche haute) : dépendance inversée, couplage fort.

**Solution** : Remonter les événements par **callback** (enregistré à l’init) ou **queue** ; le driver ne connaît pas l’application. Interfaces stables, pas de dépendance basse vers haute.

**Piège** : Configuration en dur dans plusieurs fichiers → centraliser dans un `board_config.h`.

---

## Scénario 2 : Configuration et portage

**Problème** : Config dispersée, portage coûteux et source d’erreurs.

**Solution** : **Centraliser** la config (broches, clock) dans un fichier dédié (`board_config.h`, etc.) ; le reste du code n’utilise que ces symboles. Un fichier (ou cible de build) par carte.

**Piège** : Utiliser `#ifdef BOARD_V2` pour variantes sans dupliquer tout le code.

---

**Retour** : [Scénarios Architecture](../scenarios/architecture.md) · [5.1](../01-architecture-logicielle.md)
