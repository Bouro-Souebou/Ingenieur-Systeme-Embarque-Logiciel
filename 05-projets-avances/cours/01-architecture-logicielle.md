# 5.1 – Architecture logicielle embarquée

## Objectifs

- Structurer un **projet** en couches (pilotes, HAL, application).
- Séparer **configuration** (broches, fréquences) et **logique métier**.
- Organiser le **code** pour la maintenabilité et les tests.

---

## 1. Couches typiques

- **Hardware / BSP** : accès direct aux registres ou à un HAL du fabricant (GPIO, UART, SPI, etc.). Une couche par famille de MCU ou par board.
- **Drivers / Middleware** : pilotes de périphériques externes (capteur I2C, écran SPI, module WiFi). Interfaces stables (init, read, write, callback).
- **Application / Services** : logique métier (contrôle, acquisition, protocole). Appelle les drivers et le BSP, ne connaît pas les adresses de registres.
- **Configuration** : fichiers header ou source centralisant les broches, fréquences, tailles de buffers (pour faciliter le portage et les variantes).

---

## 2. Interfaces stables

- Chaque module expose une **API** réduite (peu de fonctions, paramètres clairs).
- Éviter les dépendances circulaires : les couches basses ne doivent pas dépendre des couches hautes.
- Utiliser des **callbacks** ou des **queues** pour remonter les événements (donnée reçue, erreur) sans couplage fort.

---

## 3. Gestion de la configuration

- **Broches** : `#define LED_PORT GPIOA` et `#define LED_PIN  5` dans un `board_config.h` ; le reste du code utilise ces symboles.
- **Fréquences** : une seule source de vérité (ex. `SystemClock_Config`) ; les prescalers des timers et de l’UART sont dérivés de cette horloge.
- **Features** : compilation conditionnelle (`#ifdef USE_FREERTOS`) pour inclure ou non des modules (RTOS, réseau, écran).

---

## 4. Build et réutilisabilité

- **Makefile** ou **CMake** : séparer les sources par répertoire (bsp, drivers, app) ; un seul exécutable par cible (board + MCU).
- **Librairies** : réutiliser des drivers en les compilant comme lib (.a) avec une interface documentée.
- **Documentation** : README par projet, schéma des modules (ASCII ou outil), commentaires sur les APIs publiques.

---

## Résumé

- **Couches** : BSP → Drivers → Application ; configuration centralisée.
- **Interfaces** : API stables, pas de dépendances circulaires.
- **Build** : structure de dossiers claire, une cible = un board + un MCU.

---

## Tester sa compréhension

- **Scénarios** : [scenarios/architecture.md](scenarios/architecture.md) · **Réponses** : [reponses/architecture.md](reponses/architecture.md).

---

**Suite** : [5.2 – Tests, débogage et outillage](02-tests-debogage.md)
