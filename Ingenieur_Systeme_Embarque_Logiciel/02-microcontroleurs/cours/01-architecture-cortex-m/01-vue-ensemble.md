# Leçon 1 – Vue d'ensemble du Cortex-M

## Objectif de la leçon

Comprendre ce qu'est un processeur **ARM Cortex-M** : un cœur 32 bits conçu pour l'embarqué, avec un jeu d'instructions efficace et un contrôleur d'interruptions intégré.

---

## 1. Qu'est-ce qu'ARM ?

**ARM** (Advanced RISC Machines) désigne à la fois une **architecture** de processeur et une **société** qui en licencie les designs. Les fabricants de puces (STMicroelectronics, NXP, Nordic, etc.) intègrent ces cœurs dans des **microcontrôleurs** (MCU) en y ajoutant de la mémoire (flash, RAM), des périphériques (GPIO, UART, timers, ADC) et des bus. Les **Cortex-M** sont une famille de cœurs ARM spécialement conçue pour le **contrôle** et l'**embarqué** : pas de MMU, faible consommation, excellente gestion des interruptions.

---

## 2. Cœur 32 bits RISC

- **32 bits** : le processeur travaille sur des données et des adresses sur 32 bits (espace d'adressage de 4 Go). Les registres généraux sont des 32 bits.
- **RISC** (Reduced Instruction Set Computer) : jeu d'instructions **réduit** et **régulier**. Les opérations arithmétiques et logiques s'effectuent sur des **registres** ; les accès à la mémoire se font via des instructions **load/store** dédiées. Cela simplifie le pipeline et permet des fréquences élevées avec une bonne efficacité énergétique.

---

## 3. Jeu d'instructions Thumb / Thumb-2

Les Cortex-M n'exécutent pas le jeu d'instructions ARM 32 bits « classique » (ARM mode) mais le **Thumb** et **Thumb-2** :

- **Thumb** : instructions sur **16 bits**, ce qui réduit la taille du code (important quand la flash est limitée).
- **Thumb-2** : mélange d'instructions 16 et 32 bits pour un bon compromis **densité / performance**. Le compilateur (GCC, Keil, IAR) génère du Thumb-2 par défaut pour Cortex-M.

En pratique, en C tu n'as pas à t'en soucier : le compilateur choisit les bonnes instructions.

---

## 4. Pas de MMU (Memory Management Unit)

Contrairement aux processeurs « applicatifs » (ex. Cortex-A dans les smartphones), les Cortex-M n'ont **pas de MMU**. Conséquences :

- Pas de **mémoire virtuelle** : les adresses sont **physiques**. Pas de changement de contexte avec remapping d'adresses comme sous Linux.
- Pas d'exécution de **Linux** classique (qui requiert une MMU). On utilise un **RTOS** (FreeRTOS, Zephyr) ou du **bare-metal**.
- Certains Cortex-M ont une **MPU** (Memory Protection Unit) : protection par régions (interdire l'écriture en flash, limiter l'accès à une zone), sans gestion de pagination.

---

## 5. NVIC intégré

Le **NVIC** (Nested Vectored Interrupt Controller) est un bloc **intégré au cœur** qui gère les **interruptions** (IRQ) et les **exceptions** (fautes, SysTick, etc.). Chaque source d'interruption a un **numéro de vecteur**, une **priorité** configurable et appelle une **fonction** (handler) dont l'adresse est stockée dans une **table des vecteurs**. Le passage en interruption et le retour sont **automatiques** (sauvegarde/restauration du contexte par le matériel). Cela rend la programmation des IRQ simple et performante.

Nous détaillerons le NVIC dans la leçon 5.

---

## Points clés à retenir

- **Cortex-M** = cœur ARM 32 bits RISC pour l'embarqué.
- **Thumb/Thumb-2** = jeu d'instructions compact et efficace.
- **Pas de MMU** = pas de Linux, adresses physiques ; possible MPU pour la protection.
- **NVIC** = contrôleur d'interruptions intégré, central pour la réactivité.

---

**Suite** : [Leçon 2 – Familles Cortex-M](02-familles-cortex-m.md)
