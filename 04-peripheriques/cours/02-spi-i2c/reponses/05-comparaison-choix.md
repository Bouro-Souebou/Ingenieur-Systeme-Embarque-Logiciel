# Réponse – Comparaison SPI et I2C

Voir [scénario](../scenarios/05-comparaison-choix.md).

---

## Réponse Scénario 1 : Choisir le bus pour un capteur

**I2C** : **2 fils** (SDA, SCL) **partagés** avec EEPROM et RTC ; **adressage** 7 bits (pas de broche CS par esclave) ; **débit** 400 kHz suffisant pour un capteur de température (quelques lectures par seconde). Moins de broches, câblage simple.

**SPI** : Préférer si on a besoin de **très haut débit** (streaming capteur à haute fréquence) ou si le composant n’est disponible qu’en SPI. Pour un capteur de température classique, l’I2C est en général le bon choix si le bus est déjà présent.

---

## Réponse Scénario 2 : Écran et mémoire flash

**SPI adapté** : **Débit** élevé (MHz) pour remplir un framebuffer ou lire des blocs flash. **Full-duplex** : envoi commande + réception données en même temps (utile pour la flash). Deux **CS** : un pour l’écran, un pour la flash → pas de conflit d’esclave, mais **un seul** bus physique (MOSI, MISO, SCK).

**Mutex** : Les **deux tâches** ne doivent pas utiliser le bus **en même temps**. **Mutex** : Take avant toute transaction (activation CS, transfert), Give après. Ou une **tâche dédiée** qui reçoit des requêtes (queue) et effectue les transferts SPI. Sinon mélange d’octets et échecs.

**I2C** : Débit limité (100–400 kHz, 1 MHz max) ; pour un **écran** avec beaucoup de données, souvent **insuffisant**. I2C adapté aux commandes (petits paquets), pas au flux vidéo.

---

**Retour** : [Scénarios](../scenarios/README.md) · [Leçon 5](../05-comparaison-choix.md)
