# Leçon 7 – Pièges et bonnes pratiques

## Objectif de la leçon

Identifier les **pièges** courants en C (comportement indéfini, overflow, décalages) et établir une **checklist** de bonnes pratiques pour le code embarqué.

---

## 1. Comportement indéfini (undefined behavior)

La norme C laisse certains cas **non définis** : le compilateur n'a aucune obligation sur le résultat. Le programme peut sembler marcher chez toi et planter (ou donner des résultats faux) ailleurs.

### Décalage (shift) invalide

- **Décaler à gauche** un entier **signé** de façon à ce que le résultat ne soit pas représentable → undefined behavior.
- **Décalage à droite** d'une valeur **négative** → undefined behavior.
- **Décalage** d'un nombre de bits **≥ taille du type** (ex. `1u << 32` sur un `uint32_t`) → undefined behavior.

**Pratique** : utiliser des types **non signés** pour les décalages et masques, et s'assurer que le nombre de bits de décalage est **strictement inférieur** à la taille du type (ex. 0–31 pour un `uint32_t`).

### Overflow / underflow sur entiers signés

En C, **overflow** (dépassement) ou **underflow** sur un type **signé** est undefined behavior. Exemple : `int32_t x = 0x7FFFFFFF; x++;`

**Pratique** : pour les compteurs ou valeurs qui peuvent dépasser une plage, utiliser des types **non signés** quand c'est possible (overflow sur unsigned est défini : wrap-around). Sinon, vérifier les bornes avant les opérations.

### Accès mémoire invalide

Lire ou écrire en dehors d'un tableau, ou via un pointeur non initialisé / libéré, est undefined behavior.

**Pratique** : vérifier les index et les bornes ; ne pas utiliser de pointeur après `free` ; en embarqué, éviter `free` si on n'utilise pas le heap.

---

## 2. Pièges liés aux bits et aux registres

- **Oublier volatile** sur un registre ou une variable partagée avec une ISR → optimisations incorrectes, bugs difficiles à reproduire.
- **Lire-modifier-écrire** non atomique : entre la lecture et l'écriture d'un registre, une interruption peut modifier le registre. Pour un **seul bit**, certains MCU offrent un registre **BSRR** (Set/Reset) qui permet une écriture atomique d'un bit ; sinon, il faudra plus tard des sections critiques (désactivation d'interruptions) ou des mutex.
- **Ordre des octets** (endianness) : quand on assemble des octets en un mot (ex. sur un bus), l'ordre peut être little-endian ou big-endian selon le matériel ; être cohérent avec le protocole.

---

## 3. Checklist « C embarqué » (résumé du cours)

Avant de considérer un module « C pour l'embarqué » comme acquis, vérifier que tu appliques les points suivants :

| Thème | Bonne pratique |
|-------|-----------------|
| Types | Utiliser `stdint.h` (uint8_t, uint32_t, etc.) pour les registres et compteurs ; éviter de supposer la taille de `int` / `long`. |
| Volatile | Toute donnée lue/écrite par le matériel ou une ISR doit être `volatile` (ou accédée via un pointeur volatile). |
| Bits | Set: `\|= (1u << n)` ; Clear: `&= ~(1u << n)` ; lecture: `(*reg >> n) & 1u` ; constantes en `u`. |
| Adresses | Pointeurs sur adresses fixes avec cast `(volatile uint32_t *)` ; adresses en macros ou constantes nommées. |
| Mémoire | Pas de gros tableaux locaux (stack limitée) ; éviter malloc/free ; privilégier const/static quand c'est pertinent. |
| Pièges | Pas de décalage invalide (unsigned, bits < taille du type) ; pas d'overflow signé non maîtrisé ; pas d'accès hors bornes. |

---

## 4. Aller plus loin

- **MISRA C** : ensemble de règles pour le C en contexte critique (automobile, aéronautique). Une partie s'applique directement à l'embarqué (types, volatile, limites).
- **Tests** : compiler avec des options strictes (`-Wall -Wextra`, voire `-Werror`) pour détecter des imprécisions ou des bugs.
- **Documentation** : commenter les accès aux registres (nom du registre, manuel de référence) pour faciliter la relecture et la maintenance.

---

## Résumé du cours « C pour l'embarqué »

Tu as vu : **pourquoi le C** en embarqué, **types à taille fixe** (stdint.h), **volatile**, **accès aux bits et champs**, **pointeurs et adresses**, **const/static** et **stack/heap**, et les **pièges** à éviter. Ces bases sont suffisantes pour aborder le module **Bus et protocoles** puis **Microcontrôleurs** en pratiquant sur de vrais registres.

---

**Fin du cours C pour l'embarqué.**  
Retour à la [vue d'ensemble](README.md) ou passage au cours [Bus et protocoles](../02-bus-protocoles/README.md).
