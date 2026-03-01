# Éléments de réponse – Stack et heap (mémoire)

Réponses pour les [scénarios Stack et heap](../scenarios/stack-heap.md).

---

## Scénario 1 : Gros buffer local sur la stack

### Analyse (ce qu'il faut comprendre)

- **Le problème** : La **stack** du MCU est limitée (ici 4 Ko). Chaque appel de fonction **empile** les variables locales et l'adresse de retour. Un tableau local de **2048 octets** consomme la moitié de la stack **d'un seul coup** pour cette fonction. Si `main` et les fonctions appelées (UART, timers) ont déjà utilisé une partie de la stack, il ne reste plus assez d'espace → **débordement** (stack overflow).
- **La conséquence** : On écrit **en dehors** de la zone stack (souvent dans des données ou du code) → **HardFault** ou comportement imprévisible. Le bug peut être **intermittent** : selon la profondeur d'appels au moment de `traiter_trame()`, la stack peut ou non dépasser.
- **Le risque** : Crash en production, difficile à reproduire en debug si la chaîne d'appels n'est pas la même.

### La solution

- **Éviter** les gros tableaux **locaux**. Déplacer le buffer en **mémoire statique** (global ou `static`) pour qu'il ne soit pas sur la stack :

```c
static uint8_t trame[2048];   /* en .bss, pas sur la stack */

void traiter_trame(void) {
    /* remplir trame, puis l'envoyer */
}
```

- Ou utiliser un buffer **global** (éventuellement dans un module dédié) si plusieurs fonctions doivent y accéder.
- **Dimensionner** la stack dans le script de lien si on a beaucoup de fonctions ; surveiller l'utilisation (option de remplissage, high water mark) pour détecter les débordements en développement.

Règle : sur MCU, garder les **variables locales** de taille **raisonnable** (quelques centaines d'octets max selon la cible) ; pour les gros buffers, utiliser du **statique** ou un pool.

### Un autre piège : récursion

Une fonction qui s'appelle elle-même (récursion) consomme de la stack à **chaque** appel. Une récursion trop profonde ou non bornée provoque un stack overflow. En embarqué, préférer une **boucle** ou une **machine à états** à la récursion quand la profondeur peut être importante.

---

## Scénario 2 : malloc dans un système embarqué critique

### Analyse

- **Le problème** : En embarqué **critique** (système qui tourne des jours sans redémarrage), **malloc/free** répétés posent deux problèmes majeurs. (1) **Fuites** : un chemin d'erreur ou un oubli de `free()` fait perdre de la mémoire à chaque occurrence ; après des heures ou des jours, la RAM est épuisée. (2) **Fragmentation** : les allocations et libérations de tailles différentes créent des « trous » dans le heap ; même avec de la mémoire libre au total, il peut ne plus y avoir de **bloc contigu** assez grand pour un nouveau `malloc()` → échec d'allocation, crash ou comportement dégradé.
- **La conséquence** : Le système peut **planter** ou **refuser** de nouvelles allocations après un temps de fonctionnement imprévisible. Les bugs sont difficiles à reproduire (dépendent de l'ordre et du nombre d'allocations).
- **Le risque** : Inacceptable dans un système critique (automobile, médical, industrie) ; les normes (MISRA, certification) restreignent ou interdisent l'allocation dynamique dans les parties critiques.

### La solution

- **Éviter** `malloc`/`free` dans les parties critiques. Utiliser des **buffers statiques** (globaux ou `static`) ou des **pools** de blocs de taille fixe alloués au démarrage.
- Pour le datalogger : par exemple **un ou plusieurs buffers fixes** (ex. `static uint8_t buffer_serie[256];`) réutilisés pour chaque série de mesures ; pas d'allocation dynamique à chaque série.
- Si un heap existe (ex. fourni par le RTOS), le réserver à des usages **très contrôlés** (ex. une seule allocation au démarrage, jamais libérée).

Règle : en embarqué critique, **déterminisme** et **prévisibilité** de la mémoire ; l'allocation dynamique est à proscrire ou à cantonner à des cas très limités et documentés.

### Un autre piège : taille du heap

Même avec peu d'allocations, un **heap trop petit** peut faire échouer un `malloc` unique au démarrage. Vérifier la taille du heap dans le script de lien ou la configuration du RTOS, et s'assurer qu'aucune allocation en boucle ne « fuit » (toujours apparier malloc et free, ou ne jamais free si c'est voulu une seule fois).

---

**Retour** : [Scénarios – Stack et heap](../scenarios/stack-heap.md) · [Leçon 6 – Const, static et mémoire](../06-const-static-memoire.md)
