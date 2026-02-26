# Leçon 4 – I2C en détail

## Objectif de la leçon

Comprendre le bus **I2C** (I²C) : deux fils (SDA, SCL), adressage des esclaves, séquences START/STOP/ACK, et usages typiques.

---

## 1. Rôle de l'I2C

**I2C** (Inter-Integrated Circuit) est un bus **synchrone** à **deux fils** : **SDA** (données) et **SCL** (horloge). Il permet de connecter **plusieurs esclaves** (capteurs, EEPROM, RTC, etc.) sur le même bus ; chaque esclave a une **adresse** sur 7 (ou 10) bits. Le **maître** génère l'horloge et initie les transactions ; les esclaves répondent quand leur adresse est appelée.

---

## 2. Les deux fils : SDA et SCL

- **SCL** (Serial Clock) : horloge générée par le **maître** (ou par l'esclave en « clock stretching » quand l'esclave a besoin de temps).
- **SDA** (Serial Data) : données **bidirectionnelles** ; selon la phase de la transaction, le maître ou l'esclave pilote la ligne.

Les deux lignes sont en **open-drain** (ou open-collector) : un dispositif ne peut que **tirer la ligne au niveau bas** (0) ou la **relâcher**. Des **résistances de pull-up** (souvent 4,7 kΩ vers Vcc) ramènent la ligne au niveau **1** quand personne ne la tire. Ainsi, plusieurs maîtres ou esclaves peuvent partager le bus sans court-circuit (arbitrage par wired-AND).

---

## 3. Adressage

Chaque esclave a une **adresse** sur **7 bits** (ou 10 bits en mode étendu). L'adresse est souvent **configurable** (broches sur le composant ou registres). Lors d'une transaction, le maître envoie d'abord l'**octet d'adresse** : 7 bits d'adresse + 1 bit de **direction** (0 = écriture, 1 = lecture). L'esclave dont l'adresse correspond répond par un **ACK** (bit 0 sur le 9e bit).

---

## 4. Séquence type

1. **START** : le maître fait un front **descendant** sur SDA alors que SCL est haut. Tous les esclaves notent le début d'une transaction.
2. **Adresse + R/W** : le maître envoie 8 bits (7 bits adresse + 1 bit lecture/écriture). L'esclave concerné répond par **ACK** (tire SDA à 0 pendant le cycle d'horloge du 9e bit).
3. **Données** : selon la direction, le maître ou l'esclave envoie des octets ; après chaque octet, le récepteur envoie ACK (0) ou NACK (1).
4. **STOP** : le maître fait un front **montant** sur SDA alors que SCL est haut. Fin de la transaction.

**Repeated START** : au lieu d'envoyer STOP, le maître peut envoyer un nouveau START pour enchaîner une autre transaction (sans libérer le bus). Utile pour changer de direction (écriture puis lecture) sans STOP entre les deux.

---

## 5. Exemple : lire un registre d'un capteur

1. START.
2. Adresse esclave + **Write** (0) → ACK.
3. Envoyer l'**adresse du registre** à lire → ACK.
4. **Repeated START**.
5. Adresse esclave + **Read** (1) → ACK.
6. L'esclave envoie un ou plusieurs octets ; le maître répond ACK (sauf au dernier octet où il envoie NACK), puis STOP.

---

## 6. Débit et contraintes

- **Débit** : 100 kHz (standard), 400 kHz (fast mode), 1 MHz (fast mode+) selon le MCU et les composants. Plus le bus est long ou chargé (capacité), plus il faut réduire le débit ou adapter les pull-up.
- **Pull-up** : indispensables (souvent 4,7 kΩ ; à adapter si bus long ou beaucoup d'esclaves).
- **Longueur** : bus court (quelques dizaines de cm en 400 kHz) ; pour plus de distance, d'autres bus (CAN, RS-485) sont préférables.

---

## 7. Usages typiques

- **Capteurs** (température, pression, accéléromètre) avec interface I2C.
- **EEPROM** (mémoire de configuration).
- **RTC** (Real-Time Clock).
- **Convertisseurs** ADC/DAC I2C.
- **Écrans** (petits écrans OLED, etc.).

---

## Points clés à retenir

- **I2C** = 2 fils (SDA, SCL), **open-drain** + **pull-up** ; **adressage** 7 (ou 10) bits.
- **Séquences** : START → adresse + R/W → ACK → données (octets + ACK/NACK) → STOP (ou repeated START).
- **Débit** limité (100–400 kHz souvent) ; respecter les pull-up et la longueur du bus.

---

**Suite** : [Leçon 5 – Comparaison et choix](05-comparaison-choix.md)
