# Éléments de réponse – Types et stdint.h

Réponses pour les [scénarios Types et stdint](../scenarios/types-stdint.md).

---

## Scénario 1 : Dépassement (overflow) avec un petit type

### Analyse (ce qu'il faut comprendre)

- **Le problème** : **`uint8_t`** peut stocker des valeurs de **0 à 255** (8 bits). Une valeur sur **10 bits** va de 0 à **1023**. Dès que le capteur renvoie une valeur **> 255**, elle ne tient pas dans un `uint8_t`.
- **La conséquence** : En C, le résultat est **tronqué** (on garde les 8 bits de poids faibles). Par exemple : 300 en binaire → les 8 bits bas donnent 44 (300 - 256) ; 500 → 244. Les mesures sont **fausses** sans message d'erreur.
- **Le risque** : Bug **silencieux** : le programme tourne mais les données sont incorrectes. En embarqué (capteurs, régulation), cela peut conduire à des décisions erronées.

### La solution

Utiliser un type dont la **plage** couvre toutes les valeurs possibles du capteur :

- Pour **0 à 1023** (10 bits) : **`uint16_t`** (0 à 65 535) convient.
- En général : choisir le type **stdint** dont la taille correspond au **nombre de bits** du capteur ou du registre (8 bits → `uint8_t`, 12 bits ADC → `uint16_t`, etc.).

```c
uint16_t valeur_capteur;
valeur_capteur = lire_capteur_10_bits();  /* 0..1023, pas de perte */
```

Règle : toujours vérifier que la **plage du type** (min/max) englobe toutes les valeurs possibles de la donnée (capteur, registre, calcul intermédiaire).

### Un autre piège : les calculs intermédiaires

Même avec un `uint16_t` pour le capteur, une expression comme `valeur_capteur * 1000 / 1023` peut dépasser la capacité de `int` (souvent 32 bits) si `valeur_casteur` est grand. Il faut alors caster en type plus large pour le calcul (ex. `(uint32_t)valeur_capteur * 1000u / 1023u`) ou utiliser des types suffisants pour les **résultats intermédiaires**.

---

## Scénario 2 : Portabilité et taille de `long`

### Analyse

- **Le problème** : En C, la taille de **`long`** dépend de la **plateforme** : souvent 32 bits sur MCU 32 bits, souvent 64 bits sur PC 64 bits. Une **adresse de registre** (32 bits) doit rester sur 32 bits partout.
- **La conséquence** : Sur PC 64 bits, un `long` à 64 bits peut stocker l'adresse sans perte, mais les **masques**, **décalages** ou le **format d'impression** (ex. `printf("%lx", adresse)`) peuvent donner des résultats différents. Pire : si on utilise `long` pour des calculs de masques (ex. `~(1L << 5)`), la valeur peut changer entre 32 et 64 bits.
- **Le risque** : Comportement différent selon la cible (MCU vs PC), bugs subtils en simulation ou en tests sur PC.

### La solution

Pour les **adresses**, **registres** et toute valeur dont la taille doit être **fixe** (souvent 32 bits sur Cortex-M), utiliser les types **stdint** :

- **`uint32_t`** pour une adresse ou un registre 32 bits (ex. ARM).
- **`uintptr_t`** pour une adresse « générique » (taille d'un pointeur sur la cible), utile pour du code portable qui manipule des adresses.

```c
uint32_t reg_base = 0x40021018u;   /* toujours 32 bits, partout */
```

Pour les **masques** et **décalages** sur des registres 32 bits : utiliser des littéraux en **`u`** ou **`ul`** et des types `uint32_t` pour que le comportement soit identique sur toutes les plateformes.

### Un autre piège : littéraux et suffixes

`1 << 20` peut être de type `int` ; sur une cible 16 bits (ou en cas de décalage trop grand), comportement indéfini. Pour des masques 32 bits, écrire **`1u << 20`** ou **`1UL << 20`** pour forcer un type non signé de taille suffisante.

---

**Retour** : [Scénarios – Types et stdint](../scenarios/types-stdint.md) · [Leçon 2 – Types et stdint.h](../02-types-et-stdint.md)
