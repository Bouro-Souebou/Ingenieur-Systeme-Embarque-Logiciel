# Scénario – SPI : configuration et échange

Pour la leçon [01 – SPI : configuration et échange](../01-spi-configuration-echange.md).

---

## Scénario 1 : Modes CPOL/CPHA

On connecte une **EEPROM SPI** dont le datasheet indique « Mode 0 » (CPOL=0, CPHA=0). Le MCU est configuré en Mode 1. Les données lues sont incorrectes.

**Questions** : Pourquoi le mode doit-il être **identique** côté maître et esclave ? Que définissent CPOL et CPHA (front d'échantillonnage et de changement) ? Où trouver la bonne valeur (datasheet esclave, Reference Manual MCU) ?

---

## Scénario 2 : Séquence d'échange et CS

Le code active **CS** (met à 0), écrit un octet dans **DR**, lit immédiatement **DR** sans attendre la fin du transfert, puis désactive CS. La valeur lue est parfois l'ancienne ou indéfinie.

**Questions** : Dans quel ordre faut-il : écrire DR, attendre fin du transfert (flag RXNE ou BSY), lire DR ? Pourquoi **CS** doit rester actif pendant toute la séquence (un front SCK = un bit échangé) ? Que risque-t-on si on désactive CS trop tôt (hold time) ?

---

**Réponse** : [../reponses/01-spi-configuration-echange.md](../reponses/01-spi-configuration-echange.md) · **Retour** : [Vue d'ensemble](../README.md)
