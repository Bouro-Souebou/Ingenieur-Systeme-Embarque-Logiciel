# Chaîne de compilation et de déploiement

Ce document décrit comment passer **du code source au programme qui s’exécute sur la carte** : compilation, édition de liens, génération du binaire, flash et débogage. Il complète les cours des modules 02 (Microcontrôleurs) et 05 (Projets avancés).

---

## 1. Vue d’ensemble

```
Sources (.c, .h)  →  Compilation  →  Objets (.o)  →  Édition de liens  →  .elf  →  .bin
                                                                              ↓
                                                                         Flash (carte)
                                                                              ↓
                                                                         Exécution / Débogage
```

- **Compilation** : chaque fichier `.c` est transformé en **fichier objet** (`.o`) contenant du code machine pour la cible (ex. ARM Cortex-M). Le **compilateur** (ex. `arm-none-eabi-gcc`) connaît l’architecture et les options (optimisation, options du MCU).
- **Édition de liens** : le **linker** combine les `.o`, le **startup** (souvent en .s ou .o), les **bibliothèques** (libc, libgcc, éventuellement FreeRTOS) en un seul **fichier exécutable** (`.elf`). Le **script de lien** (`.ld`) indique où placer le code (flash), les données (RAM), la stack, et l’emplacement de la table des vecteurs.
- **Binaire** : à partir du `.elf`, on peut extraire un **fichier binaire** (`.bin`) qui est le contenu brut à écrire en flash (sans en-têtes ELF). Certains flashers utilisent le `.elf` (pour les symboles et le débogage), d’autres le `.bin`.
- **Flash** : un **programmeur** (ST-Link, J-Link) ou un outil (OpenOCD, `st-flash`) écrit le `.elf` ou le `.bin` dans la **flash** du MCU à l’adresse prévue (ex. 0x08000000 pour STM32). Au **reset**, le processeur exécute le code à cette adresse.
- **Débogage** : un **débogueur** (GDB + OpenOCD ou intégré à l’IDE) se connecte au MCU, charge le `.elf` (pour les symboles), permet de mettre des **breakpoints**, d’exécuter pas à pas et d’inspecter les variables.

---

## 2. Toolchain (chaîne d’outils)

Pour une cible **ARM Cortex-M** (ex. STM32), on utilise en général :

- **Compilateur** : **GCC pour ARM** (`arm-none-eabi-gcc`) — gratuit, open source. Alternatives : Keil, IAR (commerciaux).
- **Linker** : fourni avec le compilateur (`arm-none-eabi-ld` ou via `gcc`).
- **Objcopy** : `arm-none-eabi-objcopy` pour générer le `.bin` à partir du `.elf`.
- **Script de lien** : fichier `.ld` (ex. `STM32F407VG_FLASH.ld`) qui décrit les **régions mémoire** (flash, RAM), la **taille** de la stack, l’emplacement des sections `.text`, `.data`, `.bss`, et les symboles utilisés par le startup (`_estack`, `_sdata`, `_edata`, `_sidata`, `_sbss`, `_ebss`).

Sous **Windows**, on peut installer la toolchain GNU Arm via le site ARM ou via MSYS2 / Chocolatey. **STM32CubeIDE** intègre déjà une toolchain GCC et gère le build et le flash.

---

## 3. Étapes détaillées (ligne de commande type)

### Compilation

```bash
arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O2 -c main.c -o main.o
arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O2 -c startup_stm32f4xx.s -o startup.o
# ... pour chaque .c et .s
```

Options importantes : `-mcpu=...` (cœur cible), `-mthumb` (jeu d’instructions Thumb), `-I...` (chemins des headers), `-D...` (macros).

### Édition de liens

```bash
arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -T script.ld -Wl,--gc-sections \
  main.o startup.o ... -o firmware.elf -lgcc -lc
```

`-T script.ld` : script de lien. `-Wl,--gc-sections` : supprimer les sections non utilisées. Le **linker** produit `firmware.elf` (exécutable avec symboles).

### Génération du binaire

```bash
arm-none-eabi-objcopy -O binary firmware.elf firmware.bin
```

`firmware.bin` est le contenu de la flash à transférer (à partir de l’adresse de chargement définie dans le script de lien).

### Flash (exemple avec OpenOCD + ST-Link)

```bash
openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program firmware.elf verify reset exit"
```

Ou avec **st-flash** (outil stlink) : `st-flash write firmware.bin 0x08000000`.

---

## 4. Avec un IDE (STM32CubeIDE, VS Code)

- **STM32CubeIDE** : basé sur Eclipse + GCC + GDB. Le **projet** définit les sources, le script de lien (souvent généré), les options de compilation. Un clic sur **Run** ou **Debug** : build automatique, puis flash et lancement (ou connexion du débogueur). Pas besoin de taper les commandes à la main.
- **VS Code** : extensions (C/C++, Cortex-Debug) + **Makefile** ou **CMake** pour le build ; **OpenOCD** + **Cortex-Debug** pour le flash et le débogage. La chaîne (compile → link → flash) est la même, elle est pilotée par le build system et les tâches VS Code.

---

## 5. Script de lien (.ld) : à quoi il sert

Le **linker script** définit notamment :

- **Mémoire** : une région **FLASH** (origine 0x08000000, longueur 512K) et une région **RAM** (origine 0x20000000, longueur 128K) par exemple.
- **Sections** :
  - `.isr_vector` (table des vecteurs) en tête de FLASH.
  - `.text` (code) en FLASH.
  - `.data` (variables initialisées) : chargement en FLASH, exécution en RAM (le startup les copie).
  - `.bss` (variables non initialisées) en RAM.
- **Symboles** : `_estack` (fin de la RAM = sommet de la stack), `_sdata`, `_edata`, `_sidata`, `_sbss`, `_ebss` pour que le **Reset_Handler** sache où copier `.data` et où zero-fill `.bss`.

Sans script de lien adapté au MCU (tailles de flash et RAM), le programme ne peut pas être placé correctement ni démarrer. Les templates de projet (CubeMX, SDK) fournissent un `.ld` pour chaque MCU.

---

## 6. Résumé

| Étape        | Outil / Fichier     | Résultat                    |
|-------------|---------------------|-----------------------------|
| Compilation | arm-none-eabi-gcc -c| Fichiers `.o`               |
| Édition de liens | arm-none-eabi-gcc -T script.ld | Fichier `.elf`        |
| Binaire     | arm-none-eabi-objcopy | Fichier `.bin`           |
| Flash       | OpenOCD, st-flash, IDE | Programme en flash du MCU |
| Débogage    | GDB + OpenOCD, IDE  | Breakpoints, pas à pas      |

En pratique : **créer un projet** (IDE ou Makefile/CMake) une fois, puis utiliser **Build** et **Run/Debug** ; la chaîne complète est exécutée automatiquement. Comprendre chaque étape permet de dépanner les erreurs de link, les problèmes de placement mémoire et les échecs de flash.

---

**Voir aussi** : module **02 – Microcontrôleurs** (startup, table des vecteurs, Reset_Handler) ; module **05 – Projets avancés** (tests, débogage, documentation du build).
