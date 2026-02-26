# SPI et I2C – Vue d'ensemble

Ce sous-dossier contient le cours **SPI et I2C** : configuration et échange sur les deux bus, bonnes pratiques, et choix selon le composant.

## Objectifs pédagogiques

- Configurer un bus **SPI** (mode CPOL/CPHA, débit, CS) et échanger des octets.
- Configurer un bus **I2C** (adresse, débit) et effectuer des transactions read/write.
- Appliquer les bonnes pratiques (CS, mutex, timeouts, pull-up).
- Choisir entre SPI et I2C selon le composant et les contraintes.

## Ordre de lecture

1. [SPI : configuration et échange](01-spi-configuration-echange.md)
2. [SPI : bonnes pratiques](02-spi-bonnes-pratiques.md)
3. [I2C : configuration et transactions](03-i2c-configuration-transactions.md)
4. [I2C : erreurs et robustesse](04-i2c-erreurs-robustesse.md)
5. [Comparaison et choix](05-comparaison-choix.md)

## Prérequis

Modules 02 et 03 (registres, RTOS). Cours Fondements – Bus (SPI, I2C) recommandé.

**Commencer par** : [01 – SPI : configuration et échange](01-spi-configuration-echange.md)
