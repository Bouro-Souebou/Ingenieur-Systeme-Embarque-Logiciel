# Leçon 3 – Interruptions et réactivité

## Objectif de la leçon

Comprendre le rôle des **interruptions** (IRQ) en embarqué : comment le processeur réagit à un événement externe, et pourquoi il faut garder les **routines de service d'interruption (ISR)** **courtes** pour préserver la **réactivité**.

---

## 1. Principe des interruptions

En temps normal, le processeur exécute le programme **instruction par instruction**. Un **événement externe** (timer, caractère reçu sur l'UART, front sur une broche, etc.) peut déclencher une **interruption** (IRQ) : le processeur **suspend** l'exécution en cours, **sauvegarde** le contexte (registres, adresse de retour), puis exécute une **routine de service d'interruption** (ISR) associée à cet événement. À la fin de l'ISR, le processeur **restaure** le contexte et **reprend** le programme interrompu.

Cela permet de **réagir rapidement** à un événement sans avoir à « regarder » en permanence (polling) si l'événement s'est produit.

---

## 2. Réactivité

La **réactivité** est la capacité du système à **réagir rapidement** aux événements. Elle dépend de :

- Les **priorités** des interruptions : une IRQ de priorité plus haute peut interrompre une ISR de priorité plus basse (selon le matériel). Les événements les plus critiques doivent avoir la priorité la plus élevée.
- La **durée** des ISR : tant qu'une ISR s'exécute, les interruptions de priorité égale ou inférieure sont bloquées (ou reportées). Une ISR **longue** retarde la prise en compte des autres événements.
- Les **sections critiques** : quand le logiciel **désactive** volontairement les interruptions (pour protéger une donnée partagée ou une séquence atomique), aucune IRQ n'est traitée. Plus cette section est longue, plus la réactivité globale se dégrade.

---

## 3. Règle d'or : ISR courtes

Une **ISR** doit faire le **minimum** nécessaire pour réagir à l'événement, puis laisser le reste du travail au **programme principal** ou à une **tâche** (dans un RTOS). Concrètement :

**À faire dans l'ISR** :
- Lire la donnée (ex. octet reçu) et la mettre dans un **buffer** ou une **file**.
- Mettre à jour un **flag** (variable `volatile`) pour signaler qu'un événement s'est produit.
- **Acquitter** l'interruption (clear le bit « pending » dans le périphérique ou le NVIC) pour éviter de ré-entrer en boucle dans l'ISR.
- Éventuellement **réveiller** une tâche (dans un RTOS : donner un sémaphore, envoyer dans une queue).

**À éviter dans l'ISR** :
- **Calculs lourds** : les faire dans une tâche ou la boucle principale.
- **Appels bloquants** (delay, attente sur une queue avec timeout long) : risque de deadlock ou de latence excessive.
- **printf** ou affichage : lent et souvent non thread-safe ; à faire en dehors de l'ISR.
- **Allocation dynamique** (malloc) : imprévisible et risqué.

---

## 4. Désactiver les interruptions : le moins longtemps possible

Parfois on doit **désactiver** les interruptions pour protéger une **section critique** (ex. lecture-modification-écriture d'une variable partagée sans atomicité matérielle). Il faut garder cette section **la plus courte possible** et la **réactiver** dès que c'est fini. Une désactivation trop longue augmente la latence de toutes les autres interruptions.

Plus tard (module RTOS), on verra des mécanismes plus propres : **mutex**, **sections critiques** du RTOS, ou **opérations atomiques** quand le matériel les supporte.

---

## Points clés à retenir

- Les **interruptions** permettent de réagir à un événement en suspendant le programme en cours et en exécutant une **ISR**.
- **Réactivité** = réagir vite ; elle dépend des priorités, de la durée des ISR et des sections où les interruptions sont désactivées.
- **ISR courtes** : bufferiser, flagger, acquitter, éventuellement réveiller une tâche ; pas de traitement lourd ni de blocage.

---

## Tester sa compréhension

Un **scénario classique** (bug ISR / charge CPU) et les **éléments de réponse** (analyse, solution, piège du rebond) permettent de vérifier que la leçon est bien comprise :

→ [**Scénarios – Interruptions**](scenarios/interruptions.md) (questions) · → [**Éléments de réponse**](reponses/interruptions.md) (analyse, solution, autre piège)

---

**Suite** : [Leçon 4 – Boucle principale vs RTOS](04-boucle-vs-rtos.md)
