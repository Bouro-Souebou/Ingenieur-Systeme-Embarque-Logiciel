# Leçon 5 – Comparaison et choix

## Objectif de la leçon

**Comparer** SPI et I2C et **choisir** le bon bus selon le composant (capteur, EEPROM, écran) et les contraintes (débit, nombre de fils, multi-esclaves). Résumé du cours SPI et I2C.

---

## 1. Tableau comparatif

| Critère | SPI | I2C |
|--------|-----|-----|
| **Vitesse** | Élevée (MHz) | Moyenne (100–400 kHz, 1 MHz) |
| **Fils** | 3–4 par esclave (SCK, MOSI, MISO, CS) | 2 partagés (SDA, SCL) |
| **Adressage** | CS (broche par esclave) | Adresse 7/10 bits dans la trame |
| **Driver** | Mode CPOL/CPHA, CS, prescaler | Adresse, débit, timeouts, pull-up |
| **Usage typique** | Flash, écrans, capteurs rapides | Capteurs, EEPROM, RTC |

---

## 2. Quand choisir SPI

- **Débit** élevé nécessaire (mémoire flash, écran, capteur haute fréquence).
- **Full-duplex** utile (envoyer commande et recevoir données en même temps).
- Assez de **broches** disponibles (CS par esclave ou démultiplicateur).
- Composant disponible **uniquement** en SPI.

---

## 3. Quand choisir I2C

- **Peu de broches** : 2 fils partagés par tous les esclaves.
- **Multi-esclaves** (capteurs, EEPROM, RTC) avec adressage logiciel.
- Débit **suffisant** (100–400 kHz pour la plupart des capteurs).
- Composant disponible en I2C et contraintes de câblage court (pull-up, capacitance).

---

## 4. Résumé du cours SPI et I2C

- **SPI** : configuration (modes, débit, CS), échange (write/read DR), mutex si multi-tâches, respect des séquences composant.
- **I2C** : configuration (débit, pull-up), transactions (write/read registre, START/STOP/ACK), timeouts et récupération bus busy.

---

**Fin du cours SPI et I2C.**  
Retour à la [vue d'ensemble](README.md) ou passage au cours [Timers, PWM et capture](../../03-timers-pwm/README.md).
