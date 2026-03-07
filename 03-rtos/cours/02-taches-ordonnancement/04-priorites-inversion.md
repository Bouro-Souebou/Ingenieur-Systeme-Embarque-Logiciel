# Leçon 4 – Priorités et inversion de priorité

## Objectif de la leçon

Comprendre la **priorité** des tâches sous FreeRTOS (nombre élevé = priorité élevée) et le phénomène d'**inversion de priorité** quand une tâche de priorité basse détient un **mutex** attendu par une tâche de priorité haute. Connaître la parade : mutex avec **héritage de priorité**.

---

## 1. Priorité sous FreeRTOS

Sous FreeRTOS, **plus le nombre de priorité est élevé, plus la tâche est prioritaire** :
- Priorité **0** = la plus basse (souvent réservée à la tâche **idle**).
- Priorité **configMAX_PRIORITIES - 1** = la plus haute.

L'ordonnanceur donne toujours le CPU à la tâche **Ready** dont la priorité est la **plus élevée**. Une tâche de priorité 3 **préempte** une tâche de priorité 1 ou 2 dès qu'elle est prête.

---

## 2. Inversion de priorité (sans parade)

**Scénario** : une tâche **basse priorité** (ex. 1) prend un **mutex** (accès à une ressource partagée). Une tâche **haute priorité** (ex. 3) a besoin du même mutex et appelle **xSemaphoreTake(mutex, ...)** → elle **bloque** car le mutex est détenu. La tâche basse priorité devrait libérer le mutex rapidement, mais entre-temps une tâche de **priorité moyenne** (2) peut devenir Ready et **s'exécuter** à la place de la tâche 1 (car 2 > 1). La tâche 1 ne progresse pas, ne rend pas le mutex, et la tâche 3 (pourtant prioritaire) reste bloquée. On dit qu'il y a **inversion de priorité** : une tâche de priorité 2 retarde indirectement la tâche 3.

---

## 3. Parade : héritage de priorité (mutex)

FreeRTOS propose des **mutex** avec **héritage de priorité** (option standard pour les mutex créés avec **xSemaphoreCreateMutex**). Quand une tâche de **priorité haute** bloque sur un mutex détenu par une tâche de **priorité basse**, le noyau **élève temporairement** la priorité de la tâche qui détient le mutex à celle de la tâche bloquée (ou à la plus haute des tâches en attente). Ainsi la tâche qui détient le mutex s'exécute **tout de suite** (elle n'est plus devancée par une tâche de priorité moyenne), libère le mutex, et sa priorité revient à la normale. La tâche haute priorité peut alors prendre le mutex.

**En pratique** : utiliser les mutex FreeRTOS standard (xSemaphoreCreateMutex) pour protéger les ressources partagées ; éviter qu'une tâche basse priorité garde un mutex **longtemps** (sections critiques courtes).

---

## 4. Ne pas prendre deux fois le même mutex (deadlock)

Une tâche ne doit **pas** prendre le **même** mutex **deux fois** sans l'avoir rendu entre-temps (mutex non réentrant). Sinon : la tâche se bloque elle-même (deadlock). Si tu as besoin de « réentrance », utiliser un **mutex récursif** (xSemaphoreCreateRecursiveMutex, Take/Give récursifs) avec précaution.

---

## Points clés à retenir

- **Priorité** FreeRTOS : nombre **élevé** = priorité **élevée**.
- **Inversion de priorité** : tâche basse priorité détient un mutex attendu par une tâche haute priorité ; une tâche moyenne peut retarder la libération.
- **Héritage de priorité** : le mutex standard FreeRTOS élève temporairement la priorité du détenteur pour limiter l'inversion.
- Ne **pas** prendre le même mutex deux fois sans Give entre les deux (risque de deadlock).

---

## Tester sa compréhension

→ [Scénario – Priorités et inversion](scenarios/04-priorites-inversion.md) · [Réponse](reponses/04-priorites-inversion.md)

---

**Suite** : [Leçon 5 – Dimensionnement de la stack](05-dimensionnement-stack.md)
