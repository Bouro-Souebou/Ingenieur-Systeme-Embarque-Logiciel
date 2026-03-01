# Leçon 2 – UART en détail

## Objectif de la leçon

Comprendre le fonctionnement de l'**UART** (format de trame, paramètres, broches) et ses usages typiques en embarqué (debug, liaison avec un PC ou un module).

---

## 1. Rôle de l'UART

L'**UART** (Universal Asynchronous Receiver-Transmitter) est un **bloc matériel** (intégré au microcontrôleur ou en circuit externe) qui envoie et reçoit des **octets** de façon **asynchrone** : pas de fil d'horloge, uniquement un accord sur le **débit** et le **format** de chaque caractère.

En pratique, on utilise souvent **deux broches** : **TX** (émission) et **RX** (réception), plus la **masse (GND)** commune. Pour connecter deux appareils : TX de l'un vers RX de l'autre, et RX vers TX de l'autre (croisement), GND commun.

---

## 2. Format d'une trame (un caractère)

Une **trame** = un caractère (souvent 7 ou 8 bits de données). Elle est composée, dans l'ordre :

1. **Bit de start** : toujours **0** (niveau bas). Il permet au récepteur de se **recaler** sur le début du premier bit de donnée.
2. **Bits de données** : 7 ou 8 bits, en général **LSB en premier** (le bit de poids faible est envoyé en premier).
3. **Bit de parité** (optionnel) : none, even (parité paire) ou odd (parité impaire). Utilisé pour détecter une erreur sur un bit.
4. **Bit(s) d'arrêt** : 1 ou 2 bits à **1** (niveau haut). Marquent la fin de la trame et garantissent un front descendant pour le prochain bit de start.

Résumé visuel (exemple 8N1 : 8 bits, pas de parité, 1 bit d'arrêt) :

```
  ___   _   _   _   _   _   _   _   _   ___
     |_| |_| |_| |_| |_| |_| |_| |_| |_
     start  D0  D1  D2  D3  D4  D5  D6  D7  stop
```

---

## 3. Paramètres à configurer

| Paramètre | Signification | Valeurs courantes |
|-----------|----------------|-------------------|
| **Baudrate** | Nombre de bits par seconde (y compris start/stop) | 9600, 19200, 115200 |
| **Bits de données** | 7 ou 8 | Souvent 8 |
| **Parité** | None, Even, Odd | Souvent None |
| **Bits d'arrêt** | 1 ou 2 | Souvent 1 |

**Important** : l'émetteur et le récepteur **doivent** avoir exactement les **mêmes** paramètres. Sinon, les caractères reçus sont incorrects.

---

## 4. Broches et niveaux logiques

- **TX** : sortie de l'émetteur. Au repos (pas d'émission), la ligne est au niveau **1** (idle). Le bit de start met la ligne à 0, puis les bits de données et d'arrêt suivent.
- **RX** : entrée du récepteur. Il échantillonne la ligne au milieu de chaque bit (en théorie) pour lire la valeur.
- Les niveaux peuvent être **TTL** (0 V / 3,3 V ou 5 V) sur courte distance, ou **RS-232** (tensions inversées, ±12 V) pour des liaisons plus longues (convertisseur USB-série sur PC).

Sur une carte de développement, une puce **USB-série** (ex. CP2102, FT232) fait souvent l'interface entre l'USB du PC et les broches UART (TX/RX) du MCU.

---

## 5. Usages typiques en embarqué

- **Debug** : envoyer des messages texte (printf redirigé vers l'UART) pour suivre l'exécution.
- **Commande** : recevoir des ordres depuis un PC ou un autre appareil (ex. « LED ON », « SET 123 »).
- **Modules** : beaucoup de modules (GPS, GSM, WiFi, Bluetooth) communiquent en UART avec le MCU.
- **Échange point à point** : un émetteur, un récepteur (pas de bus multi-esclaves comme en I2C ; pour plusieurs appareils, il faut un bus autre ou plusieurs UART).

---

## 6. Limites et bonnes pratiques

- **Pas d'horloge** : les deux côtés doivent avoir des horloges suffisamment précises pour que le débit soit respecté (erreur typiquement < 2 %). Les quartz des MCU sont en général corrects.
- **Longueur de câble** : en TTL, rester court ; pour plus de distance ou environnement bruité, utiliser RS-232/RS-485 et des drivers adaptés.
- **Logiciel** : en réception, utiliser un **buffer** (circulaire) et des **interruptions** pour ne pas perdre de caractères ; ne pas bloquer en polling si d'autres tâches doivent tourner (ou utiliser un RTOS avec une tâche dédiée).

---

## Points clés à retenir

- **UART** = asynchrone, pas de fil d'horloge ; trame = start (0) + données (7/8 bits) + optionnel parité + stop (1).
- **Paramètres** : baudrate, 7/8 bits, parité, 1/2 bits d'arrêt ; identiques des deux côtés.
- **Broches** : TX, RX, GND ; usage typique : debug, commande, modules (GPS, GSM, etc.).

---

## Tester sa compréhension

→ [**Scénarios – UART**](scenarios/uart.md) · → [**Éléments de réponse**](reponses/uart.md)

---

**Suite** : [Leçon 3 – SPI en détail](03-spi-en-detail.md)
