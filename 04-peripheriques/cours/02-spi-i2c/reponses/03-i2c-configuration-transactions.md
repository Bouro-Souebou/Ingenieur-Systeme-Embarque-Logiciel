# Réponse – I2C : configuration et transactions

Voir [scénario](../scenarios/03-i2c-configuration-transactions.md).

---

## Réponse Scénario 1 : Broches et pull-up

**Open-drain** : En I2C, plusieurs maîtres ou esclaves peuvent partager le bus. Chacun peut tirer la ligne à 0 ; personne ne doit la forcer à 1. En open-drain, la broche tire à 0 ou relâche ; le pull-up externe ramène au 1 (wired-AND).

**Pull-up** : Sans résistance vers Vcc, quand tout le monde relâche, la ligne reste flottante → erreurs. Typ. 4,7 kΩ sur SDA et SCL.

**Oubli** : Lignes ne remontent pas au 1 ; timeouts, NACK, bus bloqué.

---

## Réponse Scénario 2 : Lire un registre (séquence)

**Repeated START** : Pour lire un registre, il faut d'abord écrire l'adresse du registre (adresse+W, adresse_reg), puis repasser en lecture : Repeated START, adresse+R, puis lecture des octets.

**Séquence** : START ; adresse+W ; ACK ; adresse_reg ; ACK ; Repeated START ; adresse+R ; ACK ; lecture octet(s) ; NACK sur le dernier ; STOP.

**NACK** : Sur le dernier octet lu, le maître envoie NACK pour indiquer qu'il ne veut plus de données ; puis STOP.

---

**Retour** : [Scénarios](../scenarios/README.md) · [Leçon 3](../03-i2c-configuration-transactions.md)
