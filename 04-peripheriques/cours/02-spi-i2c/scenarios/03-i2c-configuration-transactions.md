# Scénario – I2C : configuration et transactions

Pour la leçon [03 – I2C : configuration et transactions](../03-i2c-configuration-transactions.md).

---

## Scénario 1 : Broches et pull-up

On branche **SDA** et **SCL** du MCU sur un capteur I2C. Les broches du MCU sont configurées en **push-pull**. Le bus ne fonctionne pas (pas d'ACK, lignes bloquées).

**Questions** : Pourquoi l'I2C nécessite-t-il des broches en **open-drain** (plusieurs maîtres/esclaves peuvent tirer à 0) ? À quoi servent les **résistances de pull-up** (4,7 kΩ) sur SDA et SCL ? Que se passe-t-il si on oublie les pull-up (niveau haut non garanti) ?

---

## Scénario 2 : Lire un registre (séquence)

Pour lire un registre d'adresse **0x22** sur un esclave d'adresse **0x48**, le développeur envoie : START, 0x48|0 (Write), 0x22, puis lit un octet et envoie STOP.

**Questions** : Pourquoi la **lecture** d'un registre nécessite-t-elle un **Repeated START** et l'adresse avec bit **Read (1)** ? Quelle est la séquence correcte (START, adresse+W, adresse_reg, Repeated START, adresse+R, lecture octet(s), NACK sur le dernier, STOP) ? À quoi sert le NACK sur le dernier octet lu ?

---

**Réponse** : [../reponses/03-i2c-configuration-transactions.md](../reponses/03-i2c-configuration-transactions.md) · **Retour** : [Vue d'ensemble](../README.md)
