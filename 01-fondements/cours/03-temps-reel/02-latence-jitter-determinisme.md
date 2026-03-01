# Leçon 2 – Latence, jitter et déterminisme

## Objectif de la leçon

Comprendre les notions de **latence** (délai de réponse), **jitter** (variation de ce délai) et **déterminisme** (reproductibilité du comportement dans le temps). Ces notions sont essentielles pour concevoir et déboguer un système temps réel.

---

## 1. Latence (délai de réponse)

La **latence** est le **temps** qui s'écoule entre un **événement** (ex. interruption matérielle, réception d'un caractère UART, front sur une broche) et le **début de l'action** logicielle (ex. exécution de la routine d'interruption, réveil d'une tâche qui traite la donnée).

En temps réel, on cherche à :
- **Réduire** la latence (réagir le plus tôt possible).
- **Borner** la latence (connaître le **pire cas** : pire temps de réponse = Worst-Case Response Time).

La latence dépend de :
- La **priorité** des interruptions et des tâches (une interruption de plus haute priorité peut retarder le traitement d'un événement de priorité plus basse).
- La **durée** pendant laquelle les interruptions sont **désactivées** (section critique).
- L'**ordonnancement** (ordre d'exécution des tâches dans un RTOS).

---

## 2. Jitter

Le **jitter** est la **variation** du délai d'une exécution à l'autre. Par exemple : la première fois la tâche s'exécute 1 ms après l'événement, la fois suivante 3 ms, puis 2 ms, etc. Un **jitter faible** signifie que le délai est **stable** ; un jitter élevé rend le système **imprévisible** et peut dégrader les algorithmes (régulation, acquisition).

Pour limiter le jitter :
- Éviter les **allocations dynamiques** et les **branchements** dont le temps dépend fortement des données.
- Réduire les **sections critiques** (temps pendant lequel les interruptions sont désactivées).
- Donner des **priorités** cohérentes aux tâches et aux interruptions.

---

## 3. Déterminisme

Un comportement est **déterministe** si, pour les **mêmes entrées** et le **même état** du système, les **sorties** et les **instants** de réaction sont **reproductibles**. En temps réel, on vise un comportement déterministe pour pouvoir **analyser** et **garantir** les délais.

Pour favoriser le déterminisme, on évite notamment :
- **malloc / free** : le temps d'allocation et la fragmentation sont imprévisibles.
- **Boucles** dont le nombre d'itérations dépend de données **externes non bornées** (ex. attente sur une condition qui peut ne jamais être vraie).
- **Attentes actives** (busy-wait) non bornées sans timeout.

On privilégie :
- **Buffers et structures de taille fixe** (allocation statique).
- **Boucles** avec un nombre d'itérations **borné** ou un **timeout**.
- **Mesure** ou **analyse** du pire temps d'exécution (WCET) des parties critiques.

---

## 4. WCET (Worst-Case Execution Time)

Le **WCET** est le **pire temps d'exécution** d'un bout de code (une fonction, une ISR, une tâche) dans toutes les conditions possibles. Connaître le WCET permet de :
- Vérifier qu'une tâche s'exécute dans sa **fenêtre de temps** (période).
- Dimensionner les **priorités** et l'**ordonnancement** (la somme des WCET des tâches ne doit pas dépasser la période disponible).

Le WCET peut être **estimé** (mesures avec oscilloscope, trace, timestamps) ou **analysé** (outils d'analyse statique, modèles du processeur). En pratique, on combine souvent mesures et revue de code pour éviter les chemins d'exécution trop longs.

---

## Points clés à retenir

- **Latence** = délai entre l'événement et le début du traitement ; on la minimise et on la borne (pire cas).
- **Jitter** = variation de ce délai ; on le réduit pour garder un comportement stable.
- **Déterminisme** = reproductibilité du comportement dans le temps ; on évite tout ce qui est imprévisible (heap, boucles non bornées).
- **WCET** = pire temps d'exécution ; utile pour vérifier que les échéances sont respectées.

---

## Tester sa compréhension

→ [**Scénarios – Latence, jitter, déterminisme**](scenarios/latence-jitter-determinisme.md) · → [**Éléments de réponse**](reponses/latence-jitter-determinisme.md)

---

**Suite** : [Leçon 3 – Interruptions et réactivité](03-interruptions-reactivite.md)
