# Leçon 5 – NVIC et vecteurs d'interruption

## Objectif de la leçon

Comprendre le rôle du **NVIC** (Nested Vectored Interrupt Controller) : numéros de vecteur, **priorités**, **handlers** (ISR), et le déroulement d'une interruption (sauvegarde contexte, appel du handler, retour).

---

## 1. Rôle du NVIC

Le **NVIC** (Nested Vectored Interrupt Controller) est le bloc matériel qui gère les **interruptions** sur le cœur Cortex-M. Il :

- Reçoit les signaux **IRQ** des périphériques (GPIO, UART, timers, etc.) et les **exceptions** du cœur (HardFault, SysTick, etc.).
- Compare les **priorités** pour décider quelle interruption peut être prise en charge (une interruption de priorité plus élevée peut en « interrompre » une autre).
- Déclenche le **saut** vers la bonne **routine de service** (handler) en utilisant la **table des vecteurs**.

« **Vectored** » signifie que chaque source a un **numéro de vecteur** qui pointe directement vers l'adresse du handler (pas de logiciel qui interroge « qui a déclenché ? »). « **Nested** » signifie que les interruptions peuvent s'imbriquer (handler interrompu par une IRQ de priorité plus haute).

---

## 2. Table des vecteurs

La **table des vecteurs** est un tableau en **flash** (souvent à l'adresse 0x0000_0000 ou 0x0800_0000 selon le boot). Chaque **entrée** est une **adresse 32 bits** (pointeur vers une fonction) :

- **Offset 0** : valeur initiale du **Stack Pointer** (SP).
- **Offset 4** : adresse du **Reset_Handler** (première fonction exécutée après reset).
- Ensuite : **NMI**, **HardFault**, **MemManage**, **BusFault**, **UsageFault**, etc. (exceptions système).
- Puis les **IRQ** fournies par le fabricant : **SysTick**, **EXTI0**, **EXTI1**, **USART1**, etc. Le **numéro de vecteur** est l'index dans cette table (ex. 15 = IRQ numéro 15 = première IRQ fabricant après les exceptions réservées).

Le **fichier startup** (fourni par le fabricant ou généré par CubeMX) déclare cette table : des symboles **Weak** (défauts vides) pour les handlers non implémentés, et le **Reset_Handler** qui initialise les données et appelle `main()`.

---

## 3. Priorités

Chaque source d'interruption a une **priorité** (sur quelques bits, ex. 4 bits = 16 niveaux). En ARM Cortex-M : **plus le nombre de priorité est petit, plus la priorité est élevée**. Par exemple priorité 0 = la plus haute, priorité 15 = la plus basse.

Quand une IRQ se déclenche :
- Si la priorité de cette IRQ est **strictement supérieure** (nombre plus petit) à la priorité courante (celle du code en cours ou d'une ISR en cours), le processeur **suspend** l'exécution, sauvegarde le contexte minimal, et appelle le **handler** de l'IRQ.
- Sinon, l'IRQ reste **en attente** (pending) jusqu'à ce que la priorité courante baisse (retour d'ISR ou fin de section critique).

On configure la priorité via les registres du **NVIC** (un registre par IRQ ou par groupe). Les fonctions CMSIS `NVIC_SetPriority(IRQn, priority)` et `NVIC_EnableIRQ(IRQn)` sont utilisées en pratique.

---

## 4. Déroulement d'une interruption

1. Un **événement** (front GPIO, caractère UART reçu, overflow timer, etc.) met le bit **pending** correspondant dans le NVIC (et/ou dans le périphérique).
2. Si les **interruptions sont activées** (pas de masque global) et que la **priorité** de cette IRQ est suffisante, le processeur :
   - **Sauvegarde** une partie du contexte (PC, LR, PSR, éventuellement R0–R3, R12) sur la stack Handler.
   - **Charge** l'adresse du handler depuis la table des vecteurs dans le PC.
   - **Exécute** le handler (ta fonction ISR en C).
3. À la **fin** du handler (instruction de retour spéciale, ex. `BX LR` avec une valeur EXC_RETURN dans LR), le processeur **restaure** le contexte et **reprend** le programme interrompu.

Tout cela est **automatique** : tu écris une fonction C dont le nom correspond au symbole de la table des vecteurs (ex. `EXTI0_IRQHandler`), et le compilateur génère le prologue/epilogue correct.

---

## 5. Règle : handlers courts

Comme vu dans le module **Temps réel** : le **handler** (ISR) doit être **court**. Mettre à jour un flag, copier une donnée dans un buffer, acquitter l'interruption (clear pending), éventuellement donner un sémaphore pour réveiller une tâche. Le traitement lourd se fait dans la boucle principale ou dans une tâche RTOS.

---

## Points clés à retenir

- **NVIC** = gestion des interruptions : vecteurs, priorité, appel automatique du handler.
- **Table des vecteurs** = en flash ; SP initial, Reset_Handler, puis handlers des exceptions et IRQ.
- **Priorité** : nombre **petit** = priorité **élevée** ; interruptions imbriquables.
- **Handler** = fonction C au nom fixe ; garder l'ISR **courte**.

---

## Tester sa compréhension

→ [Scénario – NVIC et vecteurs](scenarios/nvic-vecteurs.md) · [Réponse](reponses/nvic-vecteurs.md)

---

**Fin du cours Architecture Cortex-M.**  
Retour à la [vue d'ensemble](README.md) ou passage au cours [Modèle programme et registres](../../02-modele-programme-registres/README.md).
