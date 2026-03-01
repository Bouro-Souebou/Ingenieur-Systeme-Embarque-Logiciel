# Leçon 2 – Le fichier startup

## Objectif de la leçon

Comprendre le rôle du **fichier startup** (fourni par le fabricant ou généré par CubeMX) : déclaration de la **table des vecteurs**, définition du **Reset_Handler**, et symboles **Weak** pour les handlers non implémentés.

---

## 1. Rôle du fichier startup

Le **fichier startup** (souvent nommé `startup_stm32f4xx.s`, `startup_xxx.s` en assembly, ou parfois en C) est le **point d’entrée** du programme après le reset. Il :

- Déclare la **table des vecteurs** : un tableau d’adresses (fonctions) aligné au début de la section code, avec la valeur initiale du SP en première entrée et l’adresse du Reset_Handler en deuxième.
- Définit le **Reset_Handler** : code qui copie .data, zero-fill .bss, puis appelle `main()`.
- Déclare des **handlers par défaut** (Weak) pour toutes les autres exceptions et IRQ, pour que la table des vecteurs soit complète même si tu n’implémentes pas toutes les interruptions. Un handler Weak peut être une boucle infinie (pour attraper une IRQ non gérée) ou un symbole vide ; si tu définis ta propre fonction avec le **même nom** dans un fichier C, le linker utilisera ta version (elle « écrase » le Weak).

---

## 2. Table des vecteurs (contenu type)

Les premières entrées sont **fixées** par l’architecture ARM :

| Offset | Nom / Rôle |
|--------|-------------|
| 0x00 | SP initial (valeur, pas une adresse de fonction) |
| 0x04 | Reset_Handler |
| 0x08 | NMI_Handler |
| 0x0C | HardFault_Handler |
| 0x10 | MemManage_Handler |
| … | … |
| 0x3C | SysTick_Handler |
| 0x40+ | IRQ du fabricant (EXTI0, EXTI1, USART1, …) |

Chaque IRQ du MCU a un **numéro de vecteur** (documenté dans le Reference Manual ou le header CMSIS). La position dans la table = offset 0x40 + (numéro_IRQ × 4) en général. Le fichier startup du fabricant liste tous les noms de handlers dans l’ordre attendu.

---

## 3. Reset_Handler : copie .data et .bss

Le Reset_Handler doit :

- **Copier .data** : les symboles `_sdata`, `_edata` (définis par le linker script) délimitent la section .data en RAM ; `_sidata` (ou équivalent) est l’adresse en flash où sont stockées les valeurs initiales. Une boucle copie de `_sidata` vers `_sdata` jusqu’à `_edata`.
- **Zero-fill .bss** : les symboles `_sbss`, `_ebss` délimitent la section .bss en RAM. Une boucle met à zéro chaque mot de `_sbss` à `_ebss`.
- **Appeler main** : en général via `bl main` (assembly) ou `main();` en C. Après l’appel, si main retourne (ce qu’il ne devrait pas), on peut boucler ou appeler une fonction de fin.

Le **linker script** (.ld) définit les sections .data, .bss, .text et les symboles _sdata, _edata, _sidata, _sbss, _ebss, ainsi que la position de la table des vecteurs (souvent en tête de .text).

---

## 4. Handlers Weak

Les autres entrées de la table pointent vers des **symboles** (noms de fonctions). Pour éviter une erreur de liaison « symbole non défini », le fichier startup les déclare en **Weak** : si aucun autre fichier ne définit une fonction avec le même nom, le linker utilise cette définition (souvent une boucle infinie ou une fonction vide). Si tu définis dans ton code C par exemple `void EXTI0_IRQHandler(void) { … }`, le linker utilisera **ta** version.

Ne **pas supprimer** les vecteurs obligatoires (Reset, NMI, HardFault, etc.) ni changer leur ordre ; tu peux en revanche **remplacer** n’importe quel handler Weak par ta propre implémentation en définissant la fonction au bon nom.

---

## Points clés à retenir

- Le **fichier startup** fournit la **table des vecteurs** et le **Reset_Handler** (copie .data, zero .bss, appel à main).
- Les **handlers** non implémentés sont déclarés **Weak** ; tu peux les « surcharger » en définissant la même fonction en C.
- Ne pas modifier l’**ordre** des vecteurs ni supprimer les entrées obligatoires.

---

**Suite** : [Leçon 3 – Déclarer et implémenter une ISR](03-declarer-implementer-isr.md)
