# Réponse – Le fichier startup

Voir [scénario](../scenarios/02-fichier-startup.md).

---

## Réponse Scénario 1 : Table et Weak

**Fournisseur** : Le **fichier startup** (fourni par le fabricant ou CubeMX) déclare la **table des vecteurs** et associe à chaque entrée un **symbole** (nom de fonction). Pour USART2, le startup met par exemple **USART2_IRQHandler**.

**Weak** : Le startup déclare ces handlers en **Weak** : si aucun autre fichier ne définit la fonction, le linker utilise cette définition (souvent une boucle infinie ou vide). Si on définit **notre** `USART2_IRQHandler` en C, le linker **remplace** le Weak par notre version (overwrite).

---

## Réponse Scénario 2 : Reset_Handler et sections

**Symboles** : Le **linker script** (.ld) définit **_sdata**, **_edata** (début et fin de .data en RAM), **_sidata** (adresse en **flash** des valeurs initiales), **_sbss**, **_ebss** pour .bss. Le Reset_Handler utilise ces symboles pour la copie et le zero-fill.

**_sidata** : Les valeurs initiales des variables globales sont stockées en **flash** (section .rodata ou incluse dans .text). **_sidata** pointe sur cette zone ; la boucle copie de _sidata vers _sdata.

**Ordre** : L'**architecture ARM** impose les **offsets** (0 = SP, 4 = Reset_Handler, puis NMI, HardFault, etc.). Changer l'ordre casserait le boot. On ne supprime pas les entrées obligatoires.

---

**Retour** : [Scénarios](../scenarios/README.md) · [Leçon 2](../02-fichier-startup.md)
