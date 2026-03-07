# Réponse – SPI : configuration et échange

Voir [scénario](../scenarios/01-spi-configuration-echange.md).

---

## Réponse Scénario 1 : Modes CPOL/CPHA

**Identiques** : L'esclave **échantillonne** et **change** ses données sur des **fronts** d'horloge précis. Si le maître utilise un autre mode, les fronts ne coïncident pas → données **décalées** ou **inversées** (lecture incorrecte).

**CPOL** : niveau de SCK au **repos** (0 = bas, 1 = haut). **CPHA** : 0 = échantillonner au premier front, changer au second ; 1 = inverse. Quatre combinaisons (modes 0 à 3).

**Où trouver** : **Datasheet** de l'EEPROM (section « SPI interface », « Mode 0 » ou « CPOL/CPHA »). **Reference Manual** du MCU pour configurer le contrôleur SPI (registres CR1 ou équivalent).

---

## Réponse Scénario 2 : Séquence d'échange et CS

**Ordre** : (1) **CS actif** (0). (2) **Écrire** l'octet dans **DR** (lance le transfert). (3) **Attendre** la fin du transfert : lire le flag **RXNE** (donnée reçue disponible) ou **BSY** (busy) selon le MCU — quand le transfert est fini, la valeur reçue est dans DR. (4) **Lire DR** pour récupérer l'octet reçu. (5) **CS inactif** (1).

**CS** : L'esclave ne « voit » les données que tant que **CS est actif** ; chaque front SCK échange un bit. Si on désactive CS trop tôt, le **dernier bit** (ou plus) peut être perdu ou mal pris en compte. **Hold time** : respecter le délai entre le dernier front SCK et la désactivation de CS (datasheet).

---

**Retour** : [Scénarios](../scenarios/README.md) · [Leçon 1](../01-spi-configuration-echange.md)
