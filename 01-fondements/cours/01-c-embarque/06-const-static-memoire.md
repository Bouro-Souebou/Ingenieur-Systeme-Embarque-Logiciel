# Leçon 6 – Const, static et mémoire (stack/heap)

## Objectif de la leçon

Comprendre les qualificateurs **const** et **static** en C, et les notions de **stack** (pile) et **heap** (tas) en contexte embarqué pour éviter les débordements et les mauvaises surprises.

---

## 1. const : donnée en lecture seule

Le qualificateur **const** indique qu'une donnée ne doit **pas être modifiée** après son initialisation.

### Variables

```c
const uint32_t frequence_max = 1000000;
/* frequence_max = 0;  -> erreur de compilation */
```

- Le compilateur peut placer la variable en **mémoire lecture seule** (ROM/flash) si possible, ce qui économise la RAM.
- C'est aussi une **documentation** : le lecteur du code sait que la valeur ne change pas.

### Paramètres de fonction

```c
void afficher(const char *message) {
    /* message peut être lu mais pas modifié */
    /* message[0] = 'X';  -> interdit */
}
```

Utile pour les chaînes et les buffers qu'on ne doit pas altérer.

### Pointeurs

```c
const uint8_t *p;   /* pointeur vers des données constantes : on ne modifie pas *p */
uint8_t *const p;   /* pointeur constant : p ne change pas, mais *p peut être modifié */
const uint8_t *const p;  /* les deux */
```

En embarqué, **const** sur des tableaux de constantes (lookup tables, messages) est très courant et recommandé.

---

## 2. static : persistance et visibilité

**static** a deux usages principaux.

### Variable locale static : persistance

Une variable **locale** déclarée **static** garde sa valeur entre deux appels de la fonction (elle n'est pas sur la stack, elle est en mémoire statique).

```c
void compteur(void) {
    static uint32_t count = 0;
    count++;
    /* count garde sa valeur au prochain appel */
}
```

À utiliser avec discernement : en embarqué, cela peut compliquer les tests et le raisonnement sur l'état. Utile pour des compteurs ou des états locaux à une fonction.

### Variable ou fonction static (au niveau fichier) : visibilité

En dehors des fonctions, **static** limite la **visibilité** au fichier courant. La variable (ou la fonction) n'est pas visible par les autres fichiers (pas d'export du symbole). Cela évite les conflits de noms et documente l'intention « usage interne à ce fichier ».

```c
static uint8_t buffer[64];   /* visible uniquement dans ce fichier */

static void helper(void) {   /* fonction interne, pas appelable depuis un autre .c */
    /* ... */
}
```

---

## 3. Stack (pile)

La **stack** est la zone mémoire où sont stockées les **variables locales** et les **adresses de retour** des appels de fonctions. À chaque appel de fonction, des données sont **empilées** ; au return, elles sont **dépilées**.

Sur un microcontrôleur, la stack est souvent **très limitée** (1 à 8 Ko selon le MCU et la configuration). Conséquences :

- **Éviter** les gros tableaux locaux : préférer des buffers **globaux** (ou static) ou passés en paramètre.
- **Éviter** la récursion profonde : chaque appel consomme de la stack.
- **Éviter** les fonctions avec beaucoup de paramètres et de variables locales volumineuses.

Exemple à éviter :

```c
void fonction(void) {
    uint8_t gros_buffer[4096];  /* 4 Ko sur la stack : risque de débordement ! */
    /* ... */
}
```

Mieux : buffer global ou static (ou alloué autrement), ou buffer plus petit.

Un **stack overflow** (débordement de pile) provoque en général un comportement imprévisible ou un **HardFault**. Il faut dimensionner la stack au lien (lien de script ou options du projet) et surveiller l'utilisation (option de remplissage, ou analyse statique).

---

## 4. Heap (tas)

Le **heap** est la zone utilisée pour l'allocation **dynamique** (`malloc`, `calloc`, `realloc`, `free`). En embarqué :

- Souvent **pas de heap** du tout (pas de `malloc`), pour éviter la fragmentation et le comportement non déterministe.
- Si un heap existe, il est **petit** et réservé à des usages très contrôlés (ex. une allocation au démarrage, jamais libérée).

**Recommandation** pour les débutants et les systèmes temps réel : **ne pas utiliser** `malloc`/`free` ; utiliser des buffers **statiques** (globaux ou static) ou des pools de taille fixe si besoin.

### Conseil de sécurité : embarqué critique

Dans les **systèmes embarqués critiques** (automobile, médical, industrie, objets connectés en continu), on **évite en général l'allocation dynamique** (`malloc`/`free`) pour plusieurs raisons :

- **Fuites de mémoire** : un `malloc` sans `free` correspondant (oubli, chemin d'erreur non géré) consomme de la RAM à chaque occurrence. Après des heures ou des jours de fonctionnement, la mémoire peut être **épuisée** → crash ou comportement erratique.
- **Fragmentation** : une succession d'allocations et de libérations de tailles différentes **fragmente** le heap : des « trous » apparaissent. Même s'il reste assez de mémoire libre au total, il peut ne plus exister de **bloc contigu** assez grand pour une nouvelle allocation → `malloc` échoue et le système peut planter.
- **Non-déterminisme** : le temps d'exécution de `malloc`/`free` dépend de l'état du heap ; en temps réel, cela complique les garanties de délai et la certification.

En résumé : pour un système qui doit tourner **plusieurs jours ou en continu** sans redémarrage, privilégier des **buffers statiques** (globaux ou static) ou des **pools de blocs de taille fixe** plutôt que `malloc`/`free`.

---

## 5. Où sont stockées les variables ?

| Type | Emplacement typique |
|------|----------------------|
| Variable globale (non static) | Mémoire statique (BSS ou data) |
| Variable globale static | Mémoire statique |
| Variable locale | **Stack** |
| Variable locale static | Mémoire statique |
| Constantes (const) | Souvent en **ROM/flash** |
| malloc | **Heap** (à éviter en embarqué classique) |

---

## 6. Résumé des bonnes pratiques

- Utiliser **const** pour les données qui ne changent pas (constantes, tables, paramètres en lecture seule).
- Utiliser **static** pour limiter la visibilité (fichier) ou pour une variable locale qui doit persister.
- **Limiter l'usage de la stack** : pas de gros tableaux locaux, pas de récursion profonde.
- **Éviter le heap** (malloc/free) en bare-metal / temps réel ; préférer des buffers statiques. En **embarqué critique**, éviter l'allocation dynamique pour prévenir fuites et fragmentation (risque de crash après plusieurs jours).

---

## Points clés à retenir

- **const** = lecture seule ; **static** = persistance (locale) ou visibilité limitée au fichier.
- La **stack** est limitée sur MCU : variables locales raisonnables, pas de gros tableaux.
- Le **heap** est souvent absent ou à éviter ; privilégier l'allocation statique. En **critique** : fuites et fragmentation peuvent faire planter le système après des heures ou des jours.

---

## Tester sa compréhension

→ [**Scénarios – Stack et heap**](scenarios/stack-heap.md) · → [**Éléments de réponse**](reponses/stack-heap.md)

---

**Suite** : [Leçon 7 – Pièges et bonnes pratiques](07-pieges-et-bonnes-pratiques.md)
