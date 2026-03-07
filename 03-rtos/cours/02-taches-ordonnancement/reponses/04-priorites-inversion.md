# Réponse – Priorités et inversion

Voir [scénario](../scenarios/04-priorites-inversion.md).

---

## Réponse Scénario 1 : Inversion de priorité et mutex

**Inversion** : La tâche haute priorité attend le mutex détenu par la basse → la haute est bloquée par la basse (priorité « inversée » tant que la basse garde le mutex).

**Héritage** : Le mutex FreeRTOS peut **élever** temporairement la priorité de la tâche qui détient le mutex (à celle du plus prioritaire en attente), pour qu'elle finisse vite et rende le mutex.

**Conception** : Garder les sections critiques (Take–Give) **courtes** ; éviter qu'une tâche basse priorité tienne longtemps un mutex attendu par une haute.

---

## Réponse Scénario 2 : Priorité moyenne qui bloque la haute

**Pourquoi M s'exécute** : Quand L rend le mutex, H redevient Ready ; mais si M est aussi Ready (même priorité ou entre L et H), l'ordonnanceur peut choisir M. M ne rend pas le CPU immédiatement si elle est de priorité moyenne et qu'elle tourne longtemps → **H attend encore** (priorité inversée « prolongée » par M).

**Héritage** : Avec héritage, **L** prend temporairement la priorité de **H** tant qu'elle détient le mutex. Donc L s'exécute avant M ; dès que L rend le mutex, H reprend. Sans héritage, M pourrait s'exécuter entre L et H et retarder H.

---

**Retour** : [Scénarios](../scenarios/README.md) · [Leçon 4](../04-priorites-inversion.md)
