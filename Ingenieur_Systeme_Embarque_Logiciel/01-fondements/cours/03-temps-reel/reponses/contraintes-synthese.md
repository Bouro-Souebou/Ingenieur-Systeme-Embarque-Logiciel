# Éléments de réponse – Contraintes à garder en tête

Réponses pour les [scénarios Contraintes et synthèse](../scenarios/contraintes-synthese.md).

---

## Scénario 1 : Buffer partagé sans protection

### Analyse (ce qu'il faut comprendre)

- **Le problème** : **Race condition** (condition de concurrence). Les deux exécutions (tâche ou ISR) accèdent au **même** buffer **sans coordination**. La tâche qui lit peut lire **pendant** que l’autre écrit : données **mélangées** (moitié anciennes, moitié nouvelles), ou lecture d’un **indice** (taille, compteur) incohérent avec les données.
- **La conséquence** : Comportement **imprévisible** : parfois correct, parfois faux, selon l’**ordre d’exécution** (scheduling, timing des interruptions). Très difficile à reproduire en debug (effet « heisenbug »).
- **Le risque** : Données corrompues, commandes erronées, crash ou sécurité compromise selon l’application.

### La solution

- **Mutex** (en RTOS) : une seule tâche (ou la tâche + l’ISR avec une section critique courte) à la fois peut accéder au buffer. La tâche qui écrit prend le mutex, écrit, libère ; la tâche qui lit prend le mutex, lit, libère.
- **File d’attente (queue)** : au lieu de partager un buffer « à la main », la tâche productrice **envoie** des messages (ou des pointeurs vers des blocs) dans une **queue** ; la tâche consommatrice **reçoit** depuis la queue. Le noyau gère la synchronisation ; plus propre et évite les race conditions sur le buffer.
- **Section critique** (si pas de RTOS) : désactiver les interruptions le temps de lire ou d’écrire le buffer — à garder **très court** pour ne pas dégrader la réactivité.

En résumé : **toute ressource partagée** (variable, buffer, périphérique) entre plusieurs exécutions doit être **protégée** (mutex, queue, section critique).

### Un autre piège : double entrée en section critique

En RTOS, si une tâche **prend un mutex** qu’elle a déjà pris (sans l’avoir libéré), **deadlock** : elle s’attend elle-même. Même chose si la tâche A attend le mutex 1 (détenu par B) et la tâche B attend le mutex 2 (détenu par A). **Règle** : toujours prendre les mutex dans le **même ordre** partout, et ne jamais oublier de **rendre** le mutex (y compris en cas d’erreur ou de return anticipé).

---

## Scénario 2 : Stack sous-dimensionnée et printf

### Analyse

- **Le problème** : **printf** (et les fonctions de formatage comme **sprintf**) utilisent beaucoup de **stack** : buffers internes, gestion des arguments variadiques, appels à des sous-fonctions (conversion, écriture). Souvent **plusieurs centaines d’octets** voire plus selon la librairie et les options (flottants, longueur des chaînes).
- **La conséquence** : Avec seulement **128 words** (512 octets) pour la tâche, la stack peut **déborder** (stack overflow) lors de l’appel à printf. On écrit en dehors de la zone allouée → écrasement de la mémoire (autre tâche, structures du noyau) → **crash** (souvent HardFault), comportement aléatoire, ou détection par FreeRTOS si `configCHECK_FOR_STACK_OVERFLOW` est activé.
- **Le risque** : Bug **intermittent** (printf n’est peut-être pas appelé à chaque cycle) ou qui n’apparaît qu’avec certaines chaînes plus longues. En production, le système peut tomber après quelques minutes ou heures.

### La solution

- **Dimensionner** la stack de la tâche en conséquence : pour une tâche qui fait du **printf** ou du **sprintf**, prévoir au moins **256 à 512 words** (1–2 Ko), voire plus selon la doc de la librairie. Utiliser **uxTaskGetStackHighWaterMark** pour mesurer l’utilisation réelle et ajuster.
- **Détecter** en développement : activer **configCHECK_FOR_STACK_OVERFLOW** (1 ou 2) et implémenter **vApplicationStackOverflowHook** pour arrêter ou logger en cas de débordement.
- **Alternative** : éviter **printf** dans les tâches temps réel (lent, non déterministe). Préférer un **buffer** rempli par la tâche et envoyé par une autre (UART, log asynchrone), ou un **trace** dédié (SWO, RTT) avec peu de stack.

### Un autre piège : récursion ou gros tableaux locaux

Même sans printf, une tâche qui fait des **appels récursifs** (ou des chaînes d’appels profondes) ou qui déclare un **gros tableau local** (ex. `uint8_t buf[1024]`) consomme beaucoup de stack. **Règle** : pas de gros tableaux **locaux** dans les tâches ; utiliser des buffers **globaux**, **static** ou alloués au démarrage, et limiter la profondeur des appels.

---

**Retour** : [Scénarios – Contraintes](../scenarios/contraintes-synthese.md) · [Leçon 5](../05-contraintes-synthese.md)
