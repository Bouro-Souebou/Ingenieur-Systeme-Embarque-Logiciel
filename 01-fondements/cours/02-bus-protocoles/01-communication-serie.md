# Leçon 1 – Communication série : notions de base

## Objectif de la leçon

Comprendre ce qu'est une **communication série** par rapport au parallèle, et la différence entre **synchronisation** par horloge partagée (**synchrone**) et par accord sur le débit (**asynchrone**). Ces notions permettent d'aborder sereinement UART, SPI et I2C.

---

## 1. Série vs parallèle

### Communication parallèle

Plusieurs **bits** sont transmis **en même temps** sur plusieurs fils (ex. 8 fils pour 8 bits = 1 octet par cycle). Avantage : débit élevé par cycle. Inconvénients : beaucoup de broches, câbles plus coûteux et sensibles aux interférences et aux décalages de temps entre fils.

### Communication série

Les bits sont transmis **un par un** sur **un ou deux fils** (données, et éventuellement horloge). Avantages : peu de broches, câbles simples, longueur possible plus grande. Inconvénient : il faut plus de cycles pour envoyer un octet, donc le débit par fil est en général plus faible qu'en parallèle, mais on compense par la simplicité et le coût.

En **embarqué**, la **série** est la règle : UART, SPI, I2C, CAN, USB, etc. Le parallèle est réservé à des interfaces très spécifiques (écrans, mémoires rapides).

---

## 2. Problème de la synchronisation

Quand on envoie des bits **un par un**, le **récepteur** doit savoir **à quel moment** lire chaque bit. Deux grandes familles de solutions :

### Communication synchrone

Un **signal d'horloge** (une broche dédiée) est partagé entre l'émetteur et le récepteur. À chaque **front** (montant ou descendant) de l'horloge, un bit est échantillonné ou changé. Le récepteur est donc **cadencé** par l'émetteur (ou par une horloge commune).

- **Avantage** : pas d'ambiguïté sur le moment où lire le bit.
- **Exemples** : SPI (SCK), I2C (SCL).

### Communication asynchrone

Il **n'y a pas** de fil d'horloge. L'émetteur et le récepteur se sont **mis d'accord à l'avance** sur le **débit** (nombre de bits par seconde, ex. 9600 ou 115200). Chaque **trame** commence par un bit de **départ** (start) qui permet au récepteur de se **recaler** sur le début du premier bit, puis les bits suivent à intervalles réguliers calculés à partir de ce débit.

- **Avantage** : seulement **deux fils** (données + masse) pour une liaison simple.
- **Inconvénient** : sensibilité aux **erreurs de débit** (les deux côtés doivent utiliser exactement le même réglage) et aux dérives d'horloge.
- **Exemple** : UART.

---

## 3. Schéma récapitulatif (texte)

```
SÉRIE
  ├── SYNCHRONE (horloge partagée)
  │     ├── SPI  (SCK + MOSI + MISO + CS)
  │     └── I2C  (SCL + SDA)
  │
  └── ASYNCHRONE (accord sur le débit)
        └── UART (TX + RX + GND)
```

---

## 4. Notions utiles pour la suite

- **Full-duplex** : émission et réception **en même temps** (deux fils de données, ou un bus bidirectionnel géré dans le temps).
- **Half-duplex** : soit on envoie, soit on reçoit (un seul fil de données partagé, ou un bus comme I2C où SDA alterne sens).
- **Maître / Esclave** : le **maître** pilote l'échange (génère l'horloge en SPI, initie les transactions en I2C) ; les **esclaves** répondent.
- **Débit** : en **bit/s** (ex. 115200 bit/s pour un UART). Ne pas confondre avec le nombre d'**octets** utiles par seconde (par exemple 115200 bit/s avec 10 bits par caractère ≈ 11520 octets/s).

---

## Points clés à retenir

- **Série** = les bits se suivent sur un (ou deux) fil(s) ; **parallèle** = plusieurs bits en même temps sur plusieurs fils. En embarqué, la série domine.
- **Synchrone** = une horloge partagée indique quand lire/écrire les bits (SPI, I2C).
- **Asynchrone** = pas d'horloge ; accord sur le débit et bit de start pour recaler le récepteur (UART).

---

**Suite** : [Leçon 2 – UART en détail](02-uart-en-detail.md)
