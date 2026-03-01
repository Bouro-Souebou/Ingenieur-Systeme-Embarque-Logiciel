# Leçon 3 – Modèle de programmation : registres

## Objectif de la leçon

Connaître les **registres** du cœur ARM Cortex-M accessibles au programmeur : registres généraux (R0–R12), Stack Pointer (SP), Link Register (LR), Program Counter (PC). Ces notions aident à comprendre le fonctionnement du processeur et le débogage (affichage des registres dans GDB).

---

## 1. Registres à usage général : R0–R12

Le processeur dispose de **13 registres à usage général** (R0 à R12), chacun sur **32 bits**. Ils servent à :

- Stocker des **opérandes** et des **résultats** des opérations (add, sub, load, store).
- Passer des **arguments** aux fonctions (conventions d'appel : en général R0–R3 pour les 4 premiers arguments, le reste sur la stack).
- Stocker des **variables** temporaires.

En C, le compilateur décide quels registres utiliser ; tu n'as pas à les manipuler directement sauf en **assembly** ou dans du code très spécifique (démarrage, contexte RTOS).

---

## 2. R13 (SP) – Stack Pointer

**R13** est le **Stack Pointer** (SP). Il contient l'**adresse** du sommet actuel de la **pile** (stack). La pile sert à :

- Stocker les **variables locales** des fonctions.
- Sauvegarder l'**adresse de retour** lors d'un appel de fonction (en plus du registre LR quand il y a des appels imbriqués).
- Sauvegarder les **registres** que la fonction modifie (convention d'appel : la fonction appelée doit préserver certains registres).

Sur Cortex-M, il existe **deux** stacks : une pour le **mode Thread** (programme normal) et une pour le **mode Handler** (interruptions). Chacune a son propre SP. Au reset, le processeur charge la **valeur initiale** du SP depuis la **table des vecteurs** (première entrée en flash).

---

## 3. R14 (LR) – Link Register

**R14** est le **Link Register** (LR). Lors d'un **appel de fonction** (instruction BL), l'adresse de retour est stockée dans LR. Au **retour** (instruction BX LR ou POP {PC}), le processeur reprend à cette adresse. En cas d'**appels imbriqués**, la fonction appelante doit sauvegarder LR sur la stack si elle appelle une autre fonction (sinon l'adresse de retour serait perdue).

En **interruption** : le processeur sauvegarde automatiquement LR avec une valeur spéciale (EXC_RETURN) pour savoir comment revenir (retour en mode Thread ou Handler). Tu n'as en général pas à modifier LR en C.

---

## 4. R15 (PC) – Program Counter

**R15** est le **Program Counter** (PC). Il contient l'**adresse** de la prochaine instruction à exécuter. En lecture, il renvoie souvent l'adresse courante + 4 (pour des raisons historiques ARM). En écriture, on fait un **saut** (branch). En C, les sauts sont générés par les `if`, `switch`, appels de fonctions, etc.

En **débogage** (GDB, trace), afficher le **PC** au moment d'un crash permet de savoir où le programme s'est arrêté (instruction qui a provoqué une faute).

---

## 5. Registres spéciaux (PSR, CONTROL, etc.)

Le cœur possède d'autres registres pour le **statut** et le **contrôle** :

- **PSR** (Program Status Register) : regroupement de flags (N, Z, C, V pour les conditions, etc.) et d'état du processeur.
- **CONTROL** : choix de la stack (Thread/Handler), mode privilégié/utilisateur (si MPU).
- **PRIMASK, FAULTMASK, BASEPRI** : masques pour désactiver certaines interruptions (sections critiques).

Le détail se trouve dans le *ARMv7-M Architecture Reference Manual* ou le *Cortex-M Generic User Guide*. En C « normal », tu n'as pas à les modifier ; un RTOS ou du code de démarrage peut utiliser PRIMASK/BASEPRI pour les sections critiques.

---

## Points clés à retenir

- **R0–R12** : registres à usage général (opérandes, arguments, temporaires).
- **R13 (SP)** : sommet de la pile ; chargé au reset depuis la table des vecteurs.
- **R14 (LR)** : adresse de retour des appels de fonction.
- **R15 (PC)** : adresse de la prochaine instruction ; utile en débogage.

---

**Suite** : [Leçon 4 – Mémoire et bus](04-memoire-et-bus.md)
