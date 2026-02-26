# Leçon 5 – Comparaison et choix

## Objectif de la leçon

Savoir **comparer** UART, SPI et I2C et **choisir** le protocole adapté à une application (débit, nombre de fils, nombre d'esclaves, type de composant).

---

## 1. Tableau comparatif

| Critère | UART | SPI | I2C |
|---------|------|-----|-----|
| **Nombre de fils** | 2 + GND (TX, RX) | 3–4 par esclave (SCK, MOSI, MISO, CS) | 2 (SDA, SCL) partagés |
| **Synchronisation** | Asynchrone (accord sur débit) | Synchrone (horloge SCK) | Synchrone (horloge SCL) |
| **Débit** | Moyen (typ. 9600–3 Mbit/s) | Élevé (MHz) | Faible à moyen (100–400 kHz, 1 MHz) |
| **Multi-esclaves** | Non natif (point à point) | Oui via CS (une ligne par esclave) | Oui via adresse 7/10 bits |
| **Adressage** | Aucun | Par broche CS | Logiciel (adresse dans la trame) |
| **Full-duplex** | Oui (TX et RX séparés) | Oui (MOSI + MISO) | Half-duplex (SDA partagée) |
| **Gestion d'erreur** | Parité optionnelle | Aucune | ACK/NACK par octet |
| **Usage typique** | Debug, liaison PC, modules (GPS, GSM) | Flash, écrans, capteurs rapides | Capteurs, EEPROM, RTC |

---

## 2. Quand choisir quoi ?

### UART

- **Debug** : envoyer des logs, printf vers un terminal.
- **Liaison point à point** avec un PC (USB-série), un module (GPS, GSM, Bluetooth).
- Quand le **débit** n'a pas besoin d'être très élevé et qu'on veut **peu de broches** (2 + GND).
- Quand il n'y a **qu'un seul** interlocuteur (pas de bus multi-esclaves).

### SPI

- **Débit élevé** : mémoires flash, écrans, capteurs rapides.
- **Full-duplex** utile (envoyer commande et recevoir données en même temps).
- Quand on a **assez de broches** (plusieurs CS si plusieurs esclaves) et qu'on veut un protocole **simple** (pas d'adressage dans la trame).
- **Bit-banging** possible si pas de SPI matériel (débit plus faible).

### I2C

- **Peu de broches** : seulement 2 fils partagés par tous les esclaves.
- **Beaucoup d'esclaves** de type capteur, EEPROM, RTC (adressage 7 bits).
- Quand le **débit** n'a pas besoin d'être très élevé (100–400 kHz suffisent souvent).
- Environnement **proche** (carte unique, câble court) à cause de la capacité et des pull-up.

---

## 3. Bonnes pratiques communes

- Toujours consulter le **datasheet** du MCU et du **composant** pour les timings (setup/hold, fréquence max), les modes (SPI CPOL/CPHA) et les adresses (I2C).
- **I2C** : respecter la valeur des pull-up (souvent 4,7 kΩ), limiter la longueur et la charge du bus.
- **SPI** : vérifier le mode (CPOL/CPHA) du composant et le configurer identiquement côté MCU.
- En **logiciel** (bit-banging) : éviter les interruptions pendant les séquences critiques, ou utiliser des délais très reproductibles.

---

## 4. Aller plus loin

- **CAN** : bus robuste pour l'automobile et l'industrie (differential, priorité des messages).
- **RS-485** : liaison série différentielle pour longue distance et multi-point.
- **USB** : pour connexion PC ou périphériques (plus complexe, souvent géré par une librairie ou un OS).

---

## Points clés à retenir

- **UART** : simple, point à point, debug et modules ; asynchrone.
- **SPI** : rapide, full-duplex, un maître, esclaves sélectionnés par CS.
- **I2C** : 2 fils, adressage, adapté aux capteurs et circuits intégrés proches ; débit limité.

---

**Fin du cours Bus et protocoles.**  
Retour à la [vue d'ensemble](README.md) ou passage au cours [Temps réel et contraintes](../03-temps-reel/README.md).
