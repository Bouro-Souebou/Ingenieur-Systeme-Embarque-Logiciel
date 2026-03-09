# TP 1 – Prise en main des outils de développement

**Objectif** : installer l’environnement, créer un premier projet pour la **NUCLEO-F446RE**, le compiler, le flasher et lancer une session de débogage.

---

## 1. Matériel et logiciel

- Carte **NUCLEO-F446RE** (câble USB vers le PC).
- **STM32CubeIDE** (recommandé) : [téléchargement ST](https://www.st.com/en/development-tools/stm32cubeide.html).  
  Alternative : **VS Code** + extension Cortex-Debug + **Makefile** ou **CMake** + toolchain `arm-none-eabi-gcc` (voir [chaine-compilation-deploiement](../../ressources/chaine-compilation-deploiement.md)).

---

## 2. Installation STM32CubeIDE (recommandé)

1. Télécharger et installer **STM32CubeIDE**.
2. Au premier lancement, accepter le répertoire workspace (ou en choisir un).
3. Vérifier que le **ST-Link** est reconnu : brancher la NUCLEO, sous Windows vérifier dans le Gestionnaire de périphériques qu’un périphérique ST-Link apparaît (pilote fourni avec l’IDE si besoin).

---

## 3. Créer un projet pour la NUCLEO-F446RE

1. **File → New → STM32 Project**.
2. Dans le sélecteur de MCU, choisir **STM32F446RE** (ou chercher « F446RE »).
3. Nom du projet : par ex. `tp-nucleo-f446re`.
4. **Targeted Project Type** : **Empty (C)** (ou « Empty ») pour un projet sans HAL, si vous voulez tout faire en registres.  
   Pour un projet avec HAL : **STM32Cube** (vous pourrez réutiliser le projet pour les TP suivants et activer HAL si besoin).
5. Cliquer **Finish**. Si une demande d’ouverture de perspective « C/C++ » apparaît, accepter.

Vous obtenez un projet avec au moins :
- `Core/Startup/` (fichier startup `.s` et éventuellement `syscalls.c`),
- `Core/Inc/` et `Core/Src/` (ou un seul `main.c` à la racine),
- un fichier de lien (`.ld`) pour le STM32F446RE.

---

## 4. Premier programme (vide ou minimal)

Dans `main.c`, garder ou mettre par exemple :

```c
#include <stdint.h>

int main(void)
{
	for (;;) {
		/* rien pour l’instant, ou appel à une fonction de test */
	}
	return 0;
}
```

- **Project → Build Project** (ou Ctrl+B) : le projet doit compiler sans erreur.
- Vérifier dans **Console** qu’il n’y a pas d’erreur de compilation ou de lien.

---

## 5. Flasher la carte

1. Brancher la NUCLEO en USB (prise « ST-Link » sur la carte).
2. **Run → Run** (ou bouton Run) : l’IDE build, flashe le `.elf` sur la carte et lance le programme.
3. Pour ce main vide, rien ne se passe à l’écran : c’est normal. L’objectif est de vérifier que le **flash** fonctionne.

En cas d’erreur « No ST-Link found » : vérifier le câble, le pilote, et qu’aucun autre logiciel (STM32CubeProgrammer, autre IDE) n’utilise le ST-Link.

---

## 6. Débogage

1. **Run → Debug** (ou bouton Debug) : build, flash, puis passage en mode débogueur.
2. Mettre un **breakpoint** dans `main` (double-clic dans la marge à gauche de la ligne `for (;;)`).
3. **Resume** (F8) : le programme s’arrête sur le breakpoint. Vérifier les **Variables** (aucune pour l’instant), la **Call Stack** (on est dans `main`).
4. **Step Over** (F6) pour avancer ligne par ligne.

Cela confirme que la chaîne **build → flash → debug** est opérationnelle.

---

## 7. Récapitulatif

| Étape | Action |
|-------|--------|
| 1 | Installer STM32CubeIDE (ou VS Code + toolchain) |
| 2 | Créer un projet vide pour STM32F446RE |
| 3 | Compiler (Build) |
| 4 | Flasher (Run) |
| 5 | Lancer une session Debug et tester un breakpoint |

**Suite** : [TP 2 – Blink LED](02-blink-led/README.md) : ajouter le code d’initialisation GPIO et faire clignoter la LED (PA5).

**Voir aussi** : [Chaîne de compilation et déploiement](../../ressources/chaine-compilation-deploiement.md).
