# Leçon 2 – États et ordonnancement préemptif

## Objectif de la leçon

Comprendre les **états** d'une tâche (Running, Ready, Blocked, Suspended) et le principe de l'**ordonnancement préemptif** : à tout instant, la tâche **Ready** de priorité la plus élevée s'exécute ; une tâche plus prioritaire qui devient prête **préempte** la tâche en cours.

---

## 1. Les quatre états

Une tâche se trouve dans **un** des états suivants :

- **Running** : elle **s'exécute** sur le CPU. À tout instant, il n'y a qu'**une seule** tâche Running par cœur.
- **Ready** : elle est **prête** à s'exécuter (pas en attente d'un événement), mais une autre tâche de priorité égale ou supérieure est Running. Dès que le CPU se libère (ou qu'une tâche plus prioritaire ne soit plus prête), l'ordonnanceur peut la mettre en Running.
- **Blocked** : elle **attend** un événement : fin d'un **vTaskDelay**, réception d'un message dans une **queue**, prise d'un **sémaphore** ou d'un **mutex**. Elle ne consomme **pas** de CPU. Quand l'événement se produit, la tâche passe en Ready.
- **Suspended** : mise en **pause** explicite par **vTaskSuspend**. Elle ne s'exécute pas tant qu'un **vTaskResume** ne la réveille pas (ou vTaskResumeAll pour reprendre toutes les tâches suspendues, selon l'usage).

---

## 2. Transitions typiques

- **Running → Ready** : une tâche de priorité **plus haute** devient Ready (ex. fin de son délai ou réception d'un message) → la tâche en cours est **préemptée** et repasse en Ready.
- **Running → Blocked** : la tâche appelle **vTaskDelay**, **xQueueReceive** (file vide), **xSemaphoreTake** (sémaphore non disponible), etc. → elle est bloquée jusqu'à l'événement.
- **Blocked → Ready** : l'événement attendu se produit (délai écoulé, message envoyé, Give sur le sémaphore) → la tâche redevient Ready.
- **Ready → Running** : l'ordonnanceur la sélectionne (priorité la plus haute parmi les Ready).

---

## 3. Ordonnancement préemptif

L'**ordonnanceur** prend des **décisions** à certains moments :

- À chaque **tick** (interruption périodique, ex. 1 ms) : il peut réveiller des tâches en Blocked (délai écoulé) et choisir quelle tâche Ready doit passer en Running.
- À chaque **événement** qui débloque une tâche (message envoyé dans une queue, Give sur un sémaphore, etc.) : si la tâche débloquée a une priorité **supérieure** à la tâche en cours, un **changement de contexte** peut avoir lieu (la tâche prioritaire prend le CPU).

On parle de **préemption** : une tâche de priorité plus haute « prend » le CPU à une tâche de priorité plus basse. Cela permet de garantir qu'une tâche **critique** (priorité haute) s'exécute dans un délai borné après l'événement qui la débloque.

---

## 4. Tourniquet (round-robin) à priorité égale

Si plusieurs tâches sont **Ready** avec la **même** priorité, FreeRTOS les exécute en **tourniquet** : à chaque tick (ou après un délai volontaire), la tâche suivante de même priorité prend le CPU. Ainsi, les tâches de même priorité se **partagent** le temps CPU.

---

## Points clés à retenir

- **Running** = une seule par cœur ; **Ready** = prête, en attente du CPU ; **Blocked** = en attente d'un événement ; **Suspended** = pause explicite.
- **Préemption** : une tâche plus prioritaire qui devient Ready prend le CPU à la tâche en cours.
- **Blocked** ne consomme pas de CPU ; les transitions dépendent des primitives (Delay, Queue, Semaphore, Mutex).

---

## Tester sa compréhension

→ [Scénario – États et ordonnancement](scenarios/02-etats-ordonnancement.md) · [Réponse](reponses/02-etats-ordonnancement.md)

---

**Suite** : [Leçon 3 – vTaskDelay et tick](03-vtaskdelay-tick.md)
