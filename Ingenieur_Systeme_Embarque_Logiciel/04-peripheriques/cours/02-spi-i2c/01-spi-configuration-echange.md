# Leçon 1 – SPI : configuration et échange

## Objectif de la leçon

Configurer un bloc **SPI** sur le MCU : **fils** (SCK, MOSI, MISO, CS), **modes** CPOL/CPHA, **débit** (prescaler), et effectuer un **échange** d'octets (write + read) avec un esclave.

---

## 1. Fils et rôle

- **SCK** : horloge générée par le **maître** (le MCU). Fréquence = horloge du bus (APB) / prescaler.
- **MOSI** : Maître Out, Slave In — données envoyées par le MCU vers l'esclave.
- **MISO** : Maître In, Slave Out — données envoyées par l'esclave vers le MCU.
- **CS** (Chip Select) : sélection de l'esclave. Souvent une **sortie GPIO** du MCU ; à 0 (actif) pendant le transfert, à 1 au repos. Un esclave n'émet sur MISO que lorsque son CS est actif.

Le MCU et l'esclave doivent être sur le **même mode** (CPOL, CPHA) ; consulter le **datasheet** du composant.

---

## 2. Modes CPOL et CPHA

- **CPOL** (Clock Polarity) : niveau de SCK au **repos** (entre transferts). 0 = bas, 1 = haut.
- **CPHA** (Clock Phase) : **0** = échantillonner sur le premier front, changer sur le second ; **1** = échantillonner sur le second front, changer sur le premier.

Cela définit **4 modes** (0 à 3). Le **Reference Manual** du MCU et le **datasheet** de l'esclave indiquent les valeurs à utiliser. Une mauvaise configuration donne des données incorrectes.

---

## 3. Séquence d'échange (polling)

Pour envoyer **un octet** et recevoir **un octet** (full-duplex) :

1. **Activer CS** (mettre à 0).
2. **Écrire** l'octet dans le registre **DR** (Data Register) du SPI.
3. **Attendre** que le transfert soit terminé (flag RXNE ou BSY selon le MCU).
4. **Lire** le registre DR (valeur reçue en même temps que l'émission).
5. **Désactiver CS** (mettre à 1).

Certains MCU ont un buffer RX séparé : lire DR après la fin du transfert. Respecter les timings **setup/hold** de CS par rapport à SCK (datasheet esclave).

---

## 4. Débit (prescaler)

Le débit SPI est réglé par un **prescaler** (diviseur) par rapport à l'horloge du bus (APB). Ne pas dépasser le **maximum** supporté par l'esclave (ex. 10 MHz pour une EEPROM). En mode interruption ou DMA : même principe, avec une séquence d'octets (buffer TX, buffer RX, interruption en fin de transfert).

---

## Points clés à retenir

- **SPI** : SCK, MOSI, MISO, CS ; **CPOL/CPHA** identiques côté MCU et esclave.
- **Échange** : CS actif → write DR → attendre fin → read DR → CS inactif.
- **Débit** : prescaler selon l'horloge APB ; ne pas dépasser le max de l'esclave.

---

**Suite** : [Leçon 2 – SPI : bonnes pratiques](02-spi-bonnes-pratiques.md)
