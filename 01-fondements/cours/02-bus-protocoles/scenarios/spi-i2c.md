# Scénarios – SPI et I2C

Situations pour vérifier votre compréhension des [Leçon 3 – SPI](../03-spi-en-detail.md) et [Leçon 4 – I2C](../04-i2c-en-detail.md).

---

## Scénario 1 (SPI) : Mode CPOL/CPHA incorrect

Un **capteur** SPI indique dans son datasheet qu'il utilise le **mode 1** (CPOL=0, CPHA=1). Le MCU est configuré en **mode 0** (CPOL=0, CPHA=0).

**Questions** : Que se passe-t-il pour les données échangées (lecture/écriture) ? Quelle règle appliquer pour SPI ?

---

## Scénario 2 (I2C) : Pas de résistances de pull-up

Sur un bus **I2C**, on oublie de mettre les **résistances de pull-up** sur SDA et SCL (ou elles sont trop grandes, ou les lignes sont trop longues). Le maître envoie une séquence START puis l'adresse de l'esclave.

**Questions** : Quel comportement peut-on observer (niveaux logiques, réponse de l'esclave) ? Pourquoi les pull-up sont-elles indispensables en I2C ?

---

*Après avoir réfléchi, consultez les* [**Éléments de réponse – SPI et I2C**](../reponses/spi-i2c.md).

---

**Retour** : [Leçon 3 – SPI](../03-spi-en-detail.md) · [Leçon 4 – I2C](../04-i2c-en-detail.md) · [Vue d'ensemble du cours Bus](../README.md)
