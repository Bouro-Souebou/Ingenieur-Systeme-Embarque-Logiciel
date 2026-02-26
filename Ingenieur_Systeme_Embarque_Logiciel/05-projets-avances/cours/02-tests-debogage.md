# 5.2 – Tests, débogage et outillage

## Objectifs

- Tester le **logiciel** (unit tests sur PC, tests d’intégration sur cible).
- Utiliser le **débogueur** (breakpoints, watch, step) et les **traces** (SWO, UART).
- Connaître les **outils** (GDB, OpenOCD, analyseur logique, oscilloscope).

---

## 1. Tests unitaires (sur PC)

- **Framework** : Unity, CppUTest, ou script (Python + sous-process pour exécuter un binaire de test). Les fonctions « pures » (sans accès matériel) peuvent être compilées pour une cible PC (x86) et testées rapidement.
- **Mocks** : remplacer les accès matériels (registres, UART) par des stubs qui enregistrent les appels et renvoient des valeurs configurables. Permet de tester la logique sans carte.
- **CI** : lancer les tests à chaque commit (GitHub Actions, GitLab CI) pour détecter les régressions.

---

## 2. Tests sur cible

- **Test manuel** : scénarios (boutons, séquence de commandes) et vérification des sorties (LED, UART, oscilloscope).
- **Test automatisé** : script qui envoie des commandes via UART/USB et vérifie les réponses (Python + pySerial). Utile pour les variants (plusieurs boards).
- **Hardware-in-the-loop** : si la cible pilote un actionneur ou lit un capteur, on peut simuler des entrées (générateur, autre MCU) et vérifier le comportement.

---

## 3. Débogage

- **Breakpoints** : arrêt à une ligne ou une adresse ; inspection des variables (watch), pas à pas (step, step over, step out).
- **GDB + OpenOCD** : connexion à la cible (ST-Link, J-Link) ; `target remote :3333`, `load`, `monitor reset halt`. Scripts GDB pour automatiser (reset, load, run).
- **SWO** (Serial Wire Output) : trace printf ou événements envoyés sur une broche dédiée sans bloquer l’UART applicatif. Outils : STM32CubeIDE, Segger RTT, ou analyseur de protocole.
- **Logs UART** : en développement, envoyer des messages formatés (timestamp, niveau, message) vers un terminal ; désactiver ou réduire en production pour les perfs et la sécurité.

---

## 4. Analyse des pannes

- **HardFault** : analyser le stack et les registres (LR, PC) au moment du fault ; souvent pointeur nul, stack overflow, accès illégal.
- **Comportement erratique** : vérifier les **volatile**, les **sections critiques** (interruptions, mutex), les **tailles de buffer** et les **priorités** des tâches.
- **Oscilloscope / analyseur logique** : vérifier les signaux (UART, SPI, I2C) : niveaux, timing, contenu des trames.

---

## Résumé

- **Tests** : unitaires sur PC (mocks), intégration sur cible (UART, scripts).
- **Débogage** : GDB + OpenOCD, breakpoints, SWO ou UART pour la trace.
- **Pannes** : HardFault (stack, PC), concurrence (volatile, mutex), signaux (scope, logic analyzer).

---

**Suite** : [5.3 – Sécurité, robustesse et maintenabilité](03-securite-robustesse.md)
