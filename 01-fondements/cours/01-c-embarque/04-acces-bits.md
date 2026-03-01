# Leçon 4 – Accès aux bits et aux champs

## Objectif de la leçon

Savoir **manipuler** les bits d'un registre matériel : mettre un bit à 1, à 0, le lire, et modifier un **champ** de plusieurs bits sans toucher aux autres. C'est une opération quotidienne en pilotage de GPIO, timers, UART, etc.

---

## 1. Pourquoi manipuler des bits ?

Les **registres** des périphériques sont des mots mémoire (souvent 32 bits). Chaque **bit** (ou groupe de bits) a une signification précise définie dans le **Reference Manual** du MCU, par exemple :

- Bit 0 : activer l'horloge d'un périphérique.
- Bits 2–3 : mode d'une broche (entrée, sortie, alternative).
- Bits 8–15 : valeur d'un prédiviseur.

Pour configurer le matériel, on doit donc **lire** le registre, **modifier** uniquement les bits concernés, puis **réécrire** le registre (pour ne pas écraser les autres champs).

---

## 2. Mettre un bit à 1 (SET)

On utilise l'opérateur **OU** (`|`) avec un masque : un seul bit à 1 à la position voulue.

```c
/* Mettre le bit 3 à 1 (les autres bits inchangés) */
*reg |= (1u << 3);
```

Explication :

- `1u << 3` donne la valeur binaire `...001000` (1 décalé de 3 positions vers la gauche) = **masque** pour le bit 3.
- `*reg |= ...` équivaut à `*reg = *reg | ...` : on fait un OU bit à bit. Tous les bits qui sont à 1 dans le masque passent à 1 dans `*reg` ; les autres restent tels quels.

---

## 3. Mettre un bit à 0 (CLEAR)

On utilise l'opérateur **ET** (`&`) avec un **masque inversé** : tous les bits à 1 sauf celui qu'on veut mettre à 0.

```c
/* Mettre le bit 3 à 0 */
*reg &= ~(1u << 3);
```

Explication :

- `1u << 3` = bit 3 à 1.
- `~(1u << 3)` = **inversion** : tous les bits à 1 sauf le bit 3 (qui devient 0).
- `*reg &= ~(...)` : on garde tous les bits de `*reg` sauf le bit 3, qui est forcé à 0.

---

## 4. Inverser un bit (TOGGLE)

On utilise le **OU exclusif** (`^`) : 1 XOR 1 = 0, 1 XOR 0 = 1.

```c
/* Inverser le bit 5 */
*reg ^= (1u << 5);
```

---

## 5. Lire un bit

On **décale** le registre pour amener le bit voulu en position 0, puis on masque avec `& 1u` :

```c
/* Lire le bit 2 (0 ou 1) */
uint32_t val = (*reg >> 2) & 1u;
```

- `*reg >> 2` : décalage à droite de 2 (le bit 2 devient le bit 0).
- `& 1u` : ne garder que le bit 0 (résultat 0 ou 1).

---

## 6. Modifier un champ de plusieurs bits

Un **champ** est un groupe de bits consécutifs (ex. bits 4 à 7). Pour les modifier sans toucher au reste :

1. **Effacer** le champ (AND avec un masque qui met ces bits à 0).
2. **Mettre** la nouvelle valeur (décalée au bon endroit) avec un OR.

```c
/* Modifier les bits 4..7 (4 bits) avec la valeur 'nouvelle_valeur' (0..15) */
uint32_t nouvelle_valeur = 3;  /* par exemple */

*reg = (*reg & ~(0xFu << 4)) | (nouvelle_valeur << 4);
```

Explication :

- `0xFu` = 15 en décimal = binaire `1111` (4 bits).
- `0xFu << 4` = masque sur les bits 4, 5, 6, 7.
- `~(0xFu << 4)` = masque qui met les bits 4–7 à 0 et laisse le reste.
- `*reg & ~(0xFu << 4)` = on efface les bits 4–7.
- `nouvelle_valeur << 4` = on place la valeur sur les bits 4–7.
- `|` = on combine : ancien registre avec bits 4–7 à 0, plus la nouvelle valeur sur 4–7.

Pour un champ de **2 bits** (ex. bits 10–11) : utiliser `0x3u << 10` et `(valeur & 0x3u) << 10`.

---

## 7. Toujours utiliser des constantes non signées

Pour les décalages et masques, utiliser le suffixe **`u`** (unsigned) : `1u`, `0xFu`. Les décalages sur types **signés** ont un comportement qui dépend du compilateur et de la valeur (undefined behavior pour décalage négatif ou trop grand). En **unsigned**, le comportement est bien défini.

---

## 8. Résumé des opérations

| Action | Code |
|--------|------|
| Mettre le bit n à 1 | `*reg \|= (1u << n);` |
| Mettre le bit n à 0 | `*reg &= ~(1u << n);` |
| Inverser le bit n | `*reg ^= (1u << n);` |
| Lire le bit n | `val = (*reg >> n) & 1u;` |
| Écrire un champ de 4 bits à la position pos | `*reg = (*reg & ~(0xFu << pos)) \| ((valeur & 0xFu) << pos);` |

---

## Points clés à retenir

- **SET** : `|= (1u << n)` ; **CLEAR** : `&= ~(1u << n)` ; **TOGGLE** : `^= (1u << n)`.
- **Lire** un bit : `(*reg >> n) & 1u`.
- **Champ** : effacer avec AND + masque inversé, puis OR avec la nouvelle valeur décalée.
- Toujours **unsigned** pour les constantes de masque/décalage (`1u`, `0xFu`).

---

**Suite** : [Leçon 5 – Pointeurs et adresses mémoire](05-pointeurs-et-adresses.md)
