# Leçon 4 – I2C : erreurs et robustesse

## Objectif de la leçon

Gérer les **erreurs** I2C : **timeout** (esclave ne répond pas, NACK, clock stretching trop long), **bus busy** après une erreur, et **pull-up** adaptés. Remettre le bus dans un état propre pour les transactions suivantes.

---

## 1. Timeout

Si l'esclave **ne répond pas** (mauvais câblage, composant coupé, adresse incorrecte), le maître peut rester bloqué en attente d'un ACK ou d'un bit sur SDA/SCL (clock stretching). Les contrôleurs I2C modernes (STM32, etc.) ont un **timeout** matériel ou logiciel : après un délai maximum sans progression, on **abandonne** la transaction et on remet le bus dans un état connu (générer STOP, libérer les lignes).

Configurer un **timeout** dans le driver (HAL : paramètre Timeout ; en bas niveau : timer ou compteur). En cas de timeout : log d'erreur, réinitialisation du périphérique I2C si nécessaire, retry ou retour d'erreur à l'appelant.

---

## 2. Bus busy

Après une **erreur** (crash en plein transfert, timeout mal géré), SDA ou SCL peuvent rester à un niveau anormal (ex. esclave qui tire SDA à 0). Le bus est alors **busy** et les transactions suivantes échouent. Certains MCU proposent une **procédure de récupération** : générer des impulsions sur **SCL** (9 pulses ou plus) jusqu'à ce que l'esclave qui bloquait relâche SDA, puis envoyer un **STOP**. Consulter le Reference Manual (section I2C, error recovery ou bus recovery).

---

## 3. Pull-up

Les résistances de **pull-up** (typ. 4,7 kΩ vers Vcc) sont **nécessaires** pour que les lignes remontent au niveau 1. Si le bus est **long** ou très **chargé** (capacité), il faut réduire la valeur des pull-up (ex. 2,2 kΩ) ou réduire le **débit** (100 kHz au lieu de 400 kHz) pour respecter les temps de montée. Inversement, des pull-up trop faibles (résistance élevée) ralentissent la montée et peuvent provoquer des erreurs à 400 kHz.

---

## Points clés à retenir

- **Timeout** : ne pas attendre indéfiniment ; après timeout, STOP et retour d'erreur.
- **Bus busy** : procédure de récupération (clock sur SCL, puis STOP) si le bus reste bloqué.
- **Pull-up** : typ. 4,7 kΩ ; adapter si bus long ou débit élevé.

---

## Tester sa compréhension

→ [Scénario – I2C : erreurs et robustesse](scenarios/04-i2c-erreurs-robustesse.md) · [Réponse](reponses/04-i2c-erreurs-robustesse.md)

---

**Suite** : [Leçon 5 – Comparaison et choix](05-comparaison-choix.md)
