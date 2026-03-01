# Leçon 4 – Boucle principale vs RTOS

## Objectif de la leçon

Comparer deux façons d'organiser le logiciel embarqué : la **boucle principale** (super-loop) et un **RTOS** (système d'exploitation temps réel). Comprendre les avantages et les limites de chacune pour choisir selon la complexité de l'application.

---

## 1. Boucle principale (super-loop)

Le programme est constitué d'une **seule** boucle infinie dans `main()`. Les traitements (lecture capteur, commande moteur, envoi UART, etc.) s'enchaînent, éventuellement avec des **délais** (`delay`) ou des **tests** sur des flags mis à jour par les **interruptions**. Il n'y a qu'**un seul fil d'exécution** : à chaque instant, une seule chose s'exécute.

**Avantages** :
- **Simple** à comprendre et à déboguer.
- **Peu de ressources** (pas de noyau RTOS, pas de stacks multiples).
- **Déterministe** si les délais et les chemins sont bien maîtrisés.

**Inconvénients** :
- Difficile de **garantir** plusieurs **échéances indépendantes** (ex. « toutes les 10 ms » pour un capteur et « toutes les 100 ms » pour l'affichage) si les traitements ont des durées variables.
- Un traitement **long** ou **bloquant** retarde tout le reste (sauf si on le découpe à la main avec des machines à états).
- La **structuration** du code peut devenir confuse quand on ajoute beaucoup de fonctionnalités.

**Adapté à** : petits systèmes, prototypes, applications avec peu de tâches et des contraintes temps réel faibles.

---

## 2. RTOS (Real-Time Operating System)

Un **RTOS** (ex. FreeRTOS, Zephyr) fournit plusieurs **tâches** (threads), chacune avec sa propre **stack** et sa **priorité**. Un **ordonnanceur** décide quelle tâche s'exécute à chaque instant : en général la tâche **prête** (non bloquée) de **priorité la plus élevée**. Les tâches peuvent se **bloquer** (attendre un délai, attendre un message dans une file, attendre un sémaphore) ; pendant ce temps, d'autres tâches s'exécutent.

**Avantages** :
- **Séparation des préoccupations** : une tâche par fonction (acquisition, commande, communication, affichage).
- **Garanties temporelles** : avec des priorités et des mécanismes de synchronisation (files, sémaphores), on peut mieux borner les délais et les périodes.
- **Réactivité** : une tâche prioritaire peut s'exécuter dès qu'un événement la débloque (ex. message dans une queue envoyé depuis une ISR).

**Inconvénients** :
- **Plus complexe** : ordonnancement, partage de ressources (mutex), risque de deadlock ou d'inversion de priorité.
- **Consommation** de RAM (stack par tâche) et de CPU (changement de contexte).
- Nécessite de **dimensionner** les stacks et de **configurer** le noyau (nombre de priorités, options).

**Adapté à** : applications avec plusieurs activités concurrentes, contraintes temps réel plus strictes, projets qui vont évoluer (ajout de fonctionnalités).

---

## 3. Comparaison rapide

| Critère | Boucle principale | RTOS |
|---------|-------------------|------|
| Nombre de « tâches » | 1 (enchaînement dans la boucle) | Plusieurs (tâches avec priorité) |
| Blocage | Un `delay` bloque tout | Une tâche peut attendre pendant que les autres tournent |
| Complexité | Faible | Plus élevée |
| Ressources | Minimales | Stacks, noyau |
| Garanties temporelles | Difficiles si beaucoup de traitements | Possibles avec priorités et sync |

---

## 4. En pratique

- **Commencer** par une **super-loop** pour des projets simples ou pour apprendre (blink, echo UART, un capteur).
- **Passer à un RTOS** quand on a besoin de plusieurs activités **indépendantes** (ex. acquisition + communication + commande) ou de **délais** multiples et garantis. Le module **03 – RTOS** du parcours détaille FreeRTOS (tâches, files, sémaphores, mutex).

---

## Points clés à retenir

- **Super-loop** = un seul fil d'exécution ; simple mais peu adapté à plusieurs échéances indépendantes.
- **RTOS** = plusieurs tâches, ordonnancement par priorité ; plus puissant pour le temps réel et la structure du code, mais plus complexe.

---

## Tester sa compréhension

→ [**Scénarios – Boucle vs RTOS**](scenarios/boucle-vs-rtos.md) · → [**Éléments de réponse**](reponses/boucle-vs-rtos.md)

---

**Suite** : [Leçon 5 – Contraintes à garder en tête](05-contraintes-synthese.md)
