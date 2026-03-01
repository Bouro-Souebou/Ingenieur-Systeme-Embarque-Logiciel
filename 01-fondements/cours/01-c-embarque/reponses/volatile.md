# Éléments de réponse – Le qualificateur volatile

Réponses pour les [scénarios volatile](../scenarios/volatile.md).

---

## Scénario 1 : Flag modifié par l'ISR

### Analyse (ce qu'il faut comprendre)

- **Le problème** : La variable `bouton_appuye` est modifiée par l'**ISR** (contexte asynchrone). Le **compilateur** ne voit pas cette modification dans le fichier : pour lui, dans la boucle `while (1)`, aucune instruction du programme principal ne modifie `bouton_appuye` avant le `if`.
- **La conséquence** : En **release**, le compilateur peut **optimiser** en lisant `bouton_appuye` une seule fois (ou en la gardant en registre) et en supposant qu'elle ne change jamais. La condition `if (bouton_appuye)` reste alors toujours fausse (ou toujours vraie) → le programme ne réagit plus au bouton.
- **Le risque** : Bug **intermittent** selon les options de compilation : présent en release, absent en debug. Très difficile à reproduire si on ne connaît pas le rôle de `volatile`.

### La solution

Déclarer le flag en **volatile** pour forcer une **lecture en mémoire** à chaque accès :

```c
volatile uint8_t bouton_appuye = 0;
```

Règle : toute variable **lue dans le programme principal** et **écrite dans une ISR** (ou par le DMA, ou par le matériel) doit être **volatile** (ou accédée via un pointeur `volatile`).

### Un autre piège : volatile ne garantit pas l'atomicité

**volatile** évite les optimisations incorrectes ; il **ne protège pas** contre les **race conditions**. Si le programme principal fait une lecture-modification-écriture (ex. `bouton_appuye++`) pendant que l'ISR écrit, le résultat peut être incohérent. Pour des accès plus complexes, il faut une **section critique** (désactiver les interruptions le temps de l'accès) ou des mécanismes du RTOS (mutex, file). Pour un simple flag écrit en ISR et lu en main, `volatile` suffit.

---

## Scénario 2 : Attente sur un registre de statut

### Analyse

- **Le problème** : Le pointeur `p` pointe vers une **adresse de registre matériel**. La valeur à cette adresse est modifiée par le **périphérique** (bit 0 passe à 1 quand l'opération est terminée). Le compilateur ne voit aucune écriture dans le code vers `*p`.
- **La conséquence** : Il peut considérer que `*p` est **constant** dans la boucle et **ne jamais relire** la mémoire : la boucle devient **infinie** (ou il supprime la boucle en supposant que la condition est toujours vraie ou fausse). En pratique, le programme reste bloqué en attente même quand le périphérique a terminé.
- **Le risque** : Système bloqué, watchdog qui déclenche, ou comportement erratique.

### La solution

Utiliser un **pointeur volatile** pour forcer une lecture à chaque tour de boucle :

```c
volatile uint32_t *p = (volatile uint32_t *)0x40021018;
while ((*p & 1) == 0)
    ;
```

Ou avec une macro type « registre » :

```c
#define REG_STATUT  (*(volatile uint32_t *)0x40021018)
while ((REG_STATUT & 1) == 0)
    ;
```

Règle : tout **accès à un registre matériel** (ou à une zone modifiée par le DMA) doit se faire via un type ou un pointeur **volatile**.

### Un autre piège : oublier volatile sur les deux côtés d'une affectation

Si on lit un registre dans une variable « normale » puis on utilise cette variable dans la boucle, le compilateur peut encore optimiser. Il faut que la **lecture** soit volatile (pointeur volatile ou variable volatile). Une variable locale qui ne reçoit qu'une copie du registre n'est pas mise à jour par le matériel ; seule l'adresse du registre l'est. Donc la boucle doit lire **directement** via le pointeur volatile (comme dans l'exemple ci-dessus).

---

**Retour** : [Scénarios – volatile](../scenarios/volatile.md) · [Leçon 3 – volatile](../03-volatile.md)
