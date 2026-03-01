# Éléments de réponse – SPI et I2C

Réponses pour les [scénarios SPI et I2C](../scenarios/spi-i2c.md).

---

## Scénario 1 (SPI) : Mode CPOL/CPHA incorrect

### Analyse (ce qu'il faut comprendre)

- **Le problème** : En SPI, CPHA définit à quel **front** d'horloge on **échantillonne** (lit) et à quel front on **change** (écrit). Si le maître et l'esclave ne sont pas dans le **même mode**, les bits lus et écrits sont **décalés** (un demi-cycle).
- **La conséquence** : Données reçues et envoyées **erronées**. Lecture incohérente (ex. capteur qui renvoie toujours 0), commandes mal interprétées.
- **Le risque** : Le système semble ne pas répondre ; il faut vérifier le datasheet du composant pour le mode SPI.

### La solution

**Règle** : le maître (MCU) et l'esclave doivent être dans le **même mode** SPI (CPOL, CPHA). Consulter le **datasheet** du composant (section SPI timing / interface) et configurer le périphérique SPI du MCU en conséquence.

### Un autre piège : oublier de désélectionner l'esclave (CS)

Entre deux transferts, **CS** doit être remis à **1** (inactif). Sinon l'esclave peut rester dans un état intermédiaire. Toujours CS = 0 avant le transfert, CS = 1 après.

---

## Scénario 2 (I2C) : Pas de résistances de pull-up

### Analyse

- **Le problème** : En I2C, SDA et SCL sont en **open-drain** : un dispositif ne peut que tirer la ligne à 0 ou la relâcher. Pour que la ligne passe à 1, il faut des **résistances de pull-up** vers Vcc. Sans pull-up (ou valeurs trop grandes, lignes trop longues), la ligne monte trop lentement ou pas au niveau 1.
- **La conséquence** : Niveaux logiques mal définis ; séquences START/STOP/ACK mal détectées ; esclaves ne répondent pas, données aléatoires, bus bloqué.
- **Le risque** : Communication I2C non fiable ; bugs intermittents.

### La solution

**Toujours** mettre des **résistances de pull-up** sur SDA et SCL (souvent **4,7 kΩ** vers Vcc pour 100–400 kHz). Adapter si bus long ou beaucoup d'esclaves (datasheet). Limiter la longueur et la capacité du bus.

### Un autre piège : conflit d'adresses I2C

Si deux esclaves ont la **même adresse** sur le bus, conflit et données corrompues. Vérifier les adresses des composants (datasheet) et choisir des adresses différentes ou configurables (broches, registres).

---

**Retour** : [Scénarios – SPI et I2C](../scenarios/spi-i2c.md) · [Leçon 3 – SPI](../03-spi-en-detail.md) · [Leçon 4 – I2C](../04-i2c-en-detail.md)
