# Scénario – Comparaison SPI et I2C

Pour la leçon [05 – Comparaison et choix](../05-comparaison-choix.md).

---

## Scénario 1 : Choisir le bus pour un capteur

On doit connecter un **capteur de température** qui propose les deux interfaces : **SPI** (jusqu'à 10 MHz) et **I2C** (400 kHz). Le projet a déjà plusieurs esclaves I2C (EEPROM, RTC) et peu de broches libres.

**Questions** : Quels avantages de l'**I2C** ici (2 fils partagés, adressage logiciel, déjà en place) ? Dans quel cas préférer malgré tout le **SPI** (besoin de débit très élevé, composant critique en latence) ?

---

## Scénario 2 : Écran et mémoire flash

On doit connecter un **écran** (flux de données important) et une **mémoire flash** (lecture/écriture par blocs). Les deux sont disponibles en SPI. Le MCU a assez de broches pour deux CS.

**Questions** : Pourquoi le **SPI** est-il adapté (débit, full-duplex) ? Pourquoi un **mutex** (ou une tâche dédiée) est nécessaire si deux tâches utilisent le même bus SPI ? Comparer avec l'I2C pour ce cas (débit limité pour un écran, souvent insuffisant).

---

**Réponse** : [../reponses/05-comparaison-choix.md](../reponses/05-comparaison-choix.md) · **Retour** : [Vue d'ensemble](../README.md)
