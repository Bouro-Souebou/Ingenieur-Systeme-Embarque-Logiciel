# Leçon 3 – I2C : configuration et transactions

## Objectif de la leçon

Configurer un bloc **I2C** sur le MCU : **SDA**, **SCL** (broches en alternate, open-drain), **débit** (100/400 kHz), et effectuer des **transactions** : écriture dans un registre, lecture d'un registre (START, adresse, ACK, données, STOP).

## 1. Broches et configuration

- **SDA** et **SCL** : broches GPIO en **fonction alternative** (open-drain). Des **résistances de pull-up** externes (souvent 4,7 kΩ vers Vcc) ramènent les lignes au niveau 1 quand personne ne les tire à 0.
- **Débit** : 100 kHz (standard), 400 kHz (fast), 1 MHz (fast+) selon le MCU et le bus. Configurer le prescaler du contrôleur I2C. Activer l'horloge du périphérique I2C (RCC) et des GPIO.

## 2. Adresse et sens (R/W)

Chaque esclave a une **adresse** sur **7 bits** (ou 10 bits). Le maître envoie un **octet** : 7 bits d'adresse + 1 bit **0** = écriture (W), **1** = lecture (R). L'esclave concerné répond par **ACK** (bit 0 sur le 9e bit).

## 3. Écrire dans un registre

1. **START**
2. **Adresse esclave + Write (0)** puis ACK
3. **Adresse du registre** (1 ou 2 octets selon composant) puis ACK
4. **Octet(s) de données** puis ACK
5. **STOP**

## 4. Lire un registre

1. **START** ; **Adresse + Write (0)** ; **Adresse registre** ; ACK
2. **Repeated START** ; **Adresse + Read (1)** ; ACK
3. **Lecture** d'un ou plusieurs octets ; **NACK** sur le dernier octet ; **STOP**

Consulter le datasheet du composant pour l'ordre des octets et les adresses.

## Points clés à retenir

- **I2C** : SDA, SCL (open-drain + pull-up) ; adresse 7 bits + bit R/W ; ACK/NACK après chaque octet.
- **Write registre** : START, adresse(W), adresse_reg, data, STOP.
- **Read registre** : START, adresse(W), adresse_reg, Repeated START, adresse(R), read + NACK + STOP.

---

## Tester sa compréhension

→ [Scénario – I2C : configuration et transactions](scenarios/03-i2c-configuration-transactions.md) · [Réponse](reponses/03-i2c-configuration-transactions.md)

---

**Suite** : [Leçon 4 – I2C : erreurs et robustesse](04-i2c-erreurs-robustesse.md)
