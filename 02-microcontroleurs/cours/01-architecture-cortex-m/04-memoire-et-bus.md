# Leçon 4 – Mémoire et bus

## Objectif de la leçon

Comprendre comment la **mémoire** et les **périphériques** sont organisés dans l'espace d'adressage 32 bits du Cortex-M : régions pour le code, les données et les registres matériels.

---

## 1. Espace d'adressage 32 bits

Le processeur utilise des **adresses sur 32 bits** : l'espace d'adressage va de **0x0000_0000** à **0xFFFF_FFFF** (4 Go). Cet espace est **découpé en régions** selon l'usage :

- Une région pour le **code** (programme, constantes).
- Une région pour la **RAM** (données globales, stack, heap éventuel).
- Une région pour les **périphériques** (registres des blocs matériels : GPIO, UART, timers, etc.).

Chaque **MCU** (STM32, LPC, etc.) définit les **adresses de base** et la **taille** de chaque bloc dans son **Reference Manual** et sa **datasheet**. La « carte mémoire » (memory map) est donc spécifique au composant.

---

## 2. Région Code (ROM / Flash)

Le **programme** (instructions) et les **constantes** (données en lecture seule) sont stockés en **flash** (mémoire non volatile). Typiquement :

- Début de la flash à **0x0800_0000** (STM32) ou **0x0000_0000** selon le mode de boot.
- Les **vecteurs d'interruption** (table des adresses des handlers) sont placés au tout début (offset 0 = SP initial, offset 4 = Reset_Handler, etc.).

À ces adresses, le processeur fait des **lectures** (fetch des instructions, lecture de constantes). Les écritures en flash sont possibles mais via un mécanisme spécifique (flash controller), pas par un simple store.

---

## 3. Région RAM

La **RAM** contient les **variables globales** (et locales si elles ne sont pas optimisées en registres), la **stack**, et éventuellement le **heap**. Typiquement :

- Début de la RAM à **0x2000_0000** (STM32) ; taille variable selon le MCU (quelques Ko à plusieurs centaines de Ko).
- Au démarrage, le **Reset_Handler** copie les variables initialisées (section `.data`) de la flash vers la RAM et met à zéro la section `.bss` (variables globales non initialisées). Ensuite la stack est utilisée par les appels de fonction et les variables locales.

---

## 4. Région Périphériques (Memory-Mapped I/O)

Les **périphériques** (GPIO, UART, SPI, timers, ADC, etc.) sont accessibles à des **adresses fixes** dans une région dédiée (souvent à partir de **0x4000_0000** sur STM32). Chaque **bloc** a une **adresse de base** ; les **registres** du bloc sont à des **offsets** fixes par rapport à cette base (voir le Reference Manual).

Exemple (simplifié) :

- **GPIOA** : base 0x4001_0800 ; ODR à l'offset 0x0C → adresse 0x4001_080C.
- **USART1** : base 0x4001_1000 ; registre DR (data) à l'offset 0x04.

En C, on accède à ces adresses avec des **pointeurs** `volatile` (voir module Fondements, cours C pour l'embarqué). La **lecture** ou l'**écriture** à ces adresses ne lit/écrit pas de la RAM : ce sont des **accès au matériel**, qui déclenchent des actions (ex. écriture dans ODR = changement d'état des broches de sortie).

---

## 5. Consulter la carte mémoire

Pour connaître les adresses exactes de ton MCU :

- **Reference Manual** du MCU (document long, chapitre « Memory map » ou « Register map »).
- **Headers** fournis par le fabricant (ex. `stm32f4xx.h`) : les bases et les structures sont déjà définies (ex. `GPIOA_BASE`, `GPIOA->ODR`).

---

## Points clés à retenir

- **Espace 32 bits** : code (flash), données (RAM), périphériques (adresses fixes).
- **Flash** : programme et constantes ; vecteurs au début.
- **RAM** : variables, stack, heap optionnel.
- **Périphériques** : mappés en mémoire ; accès par adresse (pointeurs volatile).

---

**Suite** : [Leçon 5 – NVIC et vecteurs d'interruption](05-nvic-vecteurs.md)
