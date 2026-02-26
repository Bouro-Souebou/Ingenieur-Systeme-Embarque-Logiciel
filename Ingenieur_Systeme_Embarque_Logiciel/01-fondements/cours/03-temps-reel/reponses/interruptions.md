# Éléments de réponse – Interruptions et réactivité

Ce document donne l'**analyse**, la **solution** et les **pièges** pour chaque [scénario Interruptions](../scenarios/interruptions.md).

---

## Scénario 1 : lecture du capteur dans l'ISR (10 ms, période 5 ms)

### Analyse (ce qu'il faut comprendre)

- **Le problème** : L'interruption **dure plus longtemps** (10 ms) que la **période** entre deux interruptions (5 ms).
- **La conséquence** : Le processeur va passer **100 % de son temps** dans l'ISR. Il n'aura jamais le temps de revenir au programme principal (`main`). Le système semble **« gelé »**.
- **Le risque** : C'est ce qu'on appelle une **famine du CPU** (CPU starvation) : le traitement prévu dans l'ISR consomme plus de temps que celui qui est disponible entre deux déclenchements.

### La solution

1. **Déchargement** : Dans l'ISR, lever un **drapeau (flag)** ou utiliser le **DMA** pour transférer la donnée sans bloquer le CPU.
2. **Traitement différé** : Faire le calcul lourd (les 10 ms) dans la **boucle principale** ou dans une **tâche** (RTOS).

### Un autre piège : le rebond (debouncing)

Pour un **bouton** : ne pas mettre de `HAL_Delay()` dans l'ISR. Utiliser un **condensateur** (matériel) ou un **timestamp** + fenêtre d’ignorance (ex. 20 ms) en logiciel.

---

## Scénario 2 : printf dans une ISR

### Analyse

- **Le problème** : **printf** est **lent** (formatage, buffer, accès au périphérique UART ou SVC). Il n’est en général **pas thread-safe** ni **réentrant** : être appelé depuis une ISR alors que le programme principal l’utilise aussi peut corrompre des buffers internes ou provoquer un **deadlock** (ex. mutex déjà pris par le code interrompu).
- **La conséquence** : L’ISR s’allonge beaucoup → **jitter** et **latence** pour les autres interruptions. En charge (beaucoup d’appels), le système **rame** ou **plante** (crash, blocage).
- **Le risque** : Comportement intermittent difficile à reproduire ; en production, désactiver le printf ne suffit pas si d’autres appels bloquants ou lourds restent dans l’ISR.

### La solution

- **Ne pas utiliser printf** (ni sprintf, puts, etc.) **dans une ISR**. Pour le debug : copier la donnée dans un **buffer** ou une **file** en sortie d’ISR, et faire l’affichage dans la **boucle principale** ou une **tâche** dédiée.
- Alternative : **trace asynchrone** (SWO, RTT, buffer circulaire lisible par le debugger) avec peu de code dans l’ISR (écriture d’un octet ou d’un mot).

### Un autre piège : appels non réentrants

Même principe pour toute **fonction de bibliothèque** qui utilise des buffers statiques ou des mutex (malloc, certaines fonctions CRT). En ISR, s’en tenir à du code **simple** : lecture/écriture registre, buffer circulaire, flag volatile, acquittement.

---

## Scénario 3 : Oubli d'acquitter l'interruption

### Analyse

- **Le problème** : À la fin de l’ISR, le **bit « pending »** (interruption en attente) n’est pas **cleared** dans le NVIC ou dans le périphérique. Le processeur considère qu’il reste une interruption à traiter.
- **La conséquence** : Dès la sortie de l’ISR (retour au code interrompu), le processeur **ré-enregistre immédiatement** la même interruption et **ré-entre dans l’ISR**. Comportement typique : **boucle infinie** dans l’ISR (le programme principal ne reprend jamais) ou **ré-entrées en rafale** qui saturent le CPU.
- **Le risque** : Système gelé, watchdog qui déclenche, ou traitements exécutés des centaines de fois au lieu d’une.

### La solution

- **Toujours acquitter** l’interruption avant de sortir de l’ISR : clear le bit **pending** dans le **NVIC** (ex. `NVIC_ClearPendingIRQ(...)`) et/ou dans le **périphérique** (ex. bit de statut du timer, flag RXNE de l’UART après lecture du registre de données).
- L’ordre peut dépendre du MCU : parfois lire un registre (ex. DR de l’UART) suffit à clear le pending ; parfois il faut une écriture explicite. Consulter la **Reference Manual** du composant.

### Un autre piège : acquitter trop tôt

Si on clear le pending **avant** d’avoir lu la donnée (ex. registre DR de l’UART), un nouvel événement peut être perdu ou un nouveau pending généré tout de suite. En règle générale : **lire/ sauvegarder** ce qu’il faut (donnée, flag), **puis** acquitter.

---

## Scénario 4 : Variable partagée sans volatile

### Analyse

- **Le problème** : Le **compilateur** ne voit pas que `donnee_prete` est modifiée par l’**ISR** (contexte asynchrone). Il peut **optimiser** en supposant que la variable ne change pas dans la boucle `while (!donnee_prete)` et ne **jamais relire** la valeur en mémoire : la boucle devient une **boucle infinie** ou est supprimée.
- **La conséquence** : En **release** (optimisations activées), le programme reste **bloqué** dans la boucle même quand l’ISR a mis le flag à 1. En debug (souvent sans optimisations), le bug peut ne pas apparaître.
- **Le risque** : Bug **subtil** qui n’apparaît qu’en production ; toute variable **lue en tâche principale** et **écrite en ISR** (ou inverse) doit être déclarée **volatile** pour forcer une lecture/écriture réelle à chaque accès.

### La solution

- Déclarer le flag en **volatile** : `volatile uint8_t donnee_prete = 0;`. Le compilateur ne pourra pas supprimer les lectures en boucle.
- Pour des **données** plus complexes (buffer, compteur), **volatile** assure des accès non optimisés mais **ne garantit pas l’atomicité** : pour une lecture-modification-écriture (ex. incrément), il faudra une section critique ou des opérations atomiques (voir cours C embarqué et RTOS).

### Un autre piège : volatile ne suffit pas pour la synchronisation

**volatile** dit « cette variable change en dehors du flot normal » ; ça **n’évite pas** les race conditions (lecture partielle pendant une écriture, ordre d’opérations). Pour une **synchronisation** propre entre ISR et tâche, privilégier une **file** (queue) ou un **sémaphore** fourni par le RTOS, ou une section critique **très courte** si on reste en bare-metal.

---

**Retour** : [Scénarios – Interruptions](../scenarios/interruptions.md) · [Leçon 3 – Interruptions et réactivité](../03-interruptions-reactivite.md)
