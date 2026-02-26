# Leçon 2 – SPI : bonnes pratiques

## Objectif de la leçon

Appliquer les **bonnes pratiques** pour le SPI : contrôle de **CS** (setup/hold), **mutex** si plusieurs tâches utilisent le même bus, et respect des **séquences** de commande des composants (read register : adresse puis dummy + read).

---

## 1. Contrôle de CS (Chip Select)

- **CS** est en général une **sortie GPIO** : la piloter en **logiciel** (mettre à 0 avant le transfert, à 1 après). Certains MCU ont un CS matériel (NSS) ; vérifier le Reference Manual.
- **Setup/hold** : le datasheet de l'esclave impose souvent un temps **minimum** entre l'activation de CS et le premier front SCK (setup), et entre le dernier front SCK et la désactivation de CS (hold). En logiciel, un petit délai (quelques cycles) ou une lecture du flag de fin de transfert avant de désactiver CS suffit souvent.
- **Un esclave actif à la fois** : ne pas activer deux CS en même temps si deux esclaves partagent MOSI/MISO/SCK.

---

## 2. Mutex si plusieurs tâches

Si **plusieurs tâches** utilisent le **même** bus SPI (ex. une tâche pour un capteur, une autre pour une EEPROM), il faut **sériariser** les accès : une seule transaction à la fois. Utiliser un **mutex** : **xSemaphoreTake(mutex_spi)** avant d'activer CS et de faire le transfert, **xSemaphoreGive(mutex_spi)** après. Sinon, les données de deux tâches peuvent se mélanger (une tâche active CS, l'autre envoie des octets au mauvais moment).

---

## 3. Séquences de commande (exemple : lire un registre)

Beaucoup de composants SPI (capteurs, écrans) ont un **protocole** : d'abord envoyer une **commande** ou une **adresse**, puis lire la **réponse**. Exemple type « read register » :

1. CS actif.
2. **Envoyer** l'octet (ou mot) d'adresse du registre (ex. 0x0F).
3. **Envoyer** un ou plusieurs **dummy** octets (tout en recevant les octets renvoyés par l'esclave) ; la **valeur lue** est dans les octets reçus lors des dummy (ou au cycle suivant selon le composant).
4. CS inactif.

Consulter le **datasheet** du composant pour l'ordre exact (certains attendent 8 clocks de délai avant la réponse, etc.).

---

## Points clés à retenir

- **CS** : respecter setup/hold par rapport à SCK ; un seul esclave actif à la fois.
- **Mutex** sur le bus SPI si **plusieurs tâches** l'utilisent.
- **Séquences** : respecter le protocole du composant (commande, adresse, dummy, lecture).

---

**Suite** : [Leçon 3 – I2C : configuration et transactions](03-i2c-configuration-transactions.md)
