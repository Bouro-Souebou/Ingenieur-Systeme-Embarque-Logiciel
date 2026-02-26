# Leçon 3 – SPI en détail

## Objectif de la leçon

Comprendre le fonctionnement du bus **SPI** : rôle des fils (SCK, MOSI, MISO, CS), échange synchrone, modes (CPOL/CPHA), et maître/esclave.

---

## 1. Rôle du SPI

**SPI** (Serial Peripheral Interface) est un bus **synchrone** : un signal d'**horloge** (SCK) rythme l'échange des bits. Un **maître** génère l'horloge et pilote la communication ; un ou plusieurs **esclaves** (capteurs, mémoires, écrans) répondent. Le bus est **full-duplex** : on peut envoyer et recevoir des bits **en même temps** (une broche pour chaque sens sur le maître).

---

## 2. Les quatre fils (par esclave)

| Fil | Sens (côté maître) | Rôle |
|-----|---------------------|------|
| **SCK** | Sortie | Horloge générée par le maître. |
| **MOSI** | Sortie | Maître Out, Slave In : données envoyées par le maître vers l'esclave. |
| **MISO** | Entrée | Maître In, Slave Out : données envoyées par l'esclave vers le maître. |
| **CS** (ou SS) | Sortie | Chip Select (ou Slave Select) : sélection de l'esclave. À 0 (actif), l'esclave est sélectionné ; à 1, il est désactivé. |

En pratique, on a **une ligne CS par esclave** (ou un démultiplexeur) pour choisir avec qui on parle. Plusieurs esclaves peuvent partager SCK, MOSI, MISO, mais un seul CS actif à la fois.

---

## 3. Principe de l'échange

- Le maître met **CS** à 0 pour sélectionner l'esclave.
- Le maître génère des **impulsions** sur **SCK**.
- À chaque **front** (montant ou descendant, selon le mode), le maître met un bit sur **MOSI** et l'esclave le lit ; l'esclave met un bit sur **MISO** et le maître le lit. Donc à chaque cycle d'horloge, **un bit part dans chaque sens**.
- À la fin du transfert, le maître remet **CS** à 1.

Les données sont en général organisées en **octets** (8 bits) ou en **mots** de 16 bits, selon le composant. Beaucoup de composants SPI sont « 8 bits » : on envoie un ou plusieurs octets (commande, adresse, données) et on lit la réponse sur MISO en même temps.

---

## 4. Modes SPI (CPOL et CPHA)

Deux paramètres définissent **quand** on échantillonne (on lit) et **quand** on change (on écrit) la donnée par rapport à l'horloge :

- **CPOL** (Clock Polarity) : niveau de SCK au **repos** (entre deux transferts). 0 = bas, 1 = haut.
- **CPHA** (Clock Phase) :  
  - 0 = échantillonner sur le **premier** front, changer sur le **second** front.  
  - 1 = échantillonner sur le **second** front, changer sur le **premier** front.

Cela donne **4 modes** (0, 1, 2, 3). Le **maître et l'esclave doivent être dans le même mode** ; le datasheet du composant indique le(s) mode(s) supporté(s).

---

## 5. Avantages et inconvénients

**Avantages** :
- **Débit** élevé (souvent jusqu'à plusieurs MHz).
- **Full-duplex** : envoi et réception simultanés.
- Protocole **simple** (pas d'adressage logiciel : c'est le CS qui sélectionne l'esclave).
- Facile à implémenter en **bit-banging** (logiciel) si le MCU n'a pas de SPI matériel.

**Inconvénients** :
- **3 à 4 fils par esclave** (si on ne partage pas les données, au moins SCK + MOSI + MISO + CS par esclave).
- Pas de **standard d'adressage** : chaque esclave est choisi par une broche CS dédiée (ou un démultiplicateur).
- Pas de **gestion d'erreur** intégrée (pas d'ACK comme en I2C) : il faut des protocoles applicatifs si besoin.

---

## 6. Usages typiques

- **Mémoires flash** (EEPROM, flash SPI).
- **Écrans** (petits écrans LCD, OLED).
- **Capteurs** (accéléromètres, gyroscopes, pression) quand le débit ou la simplicité prime.
- **Converseurs** ADC/DAC série.

---

## Points clés à retenir

- **SPI** = synchrone, 4 fils (SCK, MOSI, MISO, CS) ; le **maître** pilote SCK et CS ; échange **full-duplex** bit à bit.
- **CS** = sélection de l'esclave (un CS par esclave ou partagé avec adressage).
- **Modes** CPOL/CPHA : définissent les fronts d'échantillonnage et de changement ; maître et esclave doivent être compatibles.

---

**Suite** : [Leçon 4 – I2C en détail](04-i2c-en-detail.md)
