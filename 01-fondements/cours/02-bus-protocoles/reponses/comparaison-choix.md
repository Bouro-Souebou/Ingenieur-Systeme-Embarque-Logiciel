# Éléments de réponse – Comparaison et choix du protocole

Réponses pour les [scénarios Comparaison et choix](../scenarios/comparaison-choix.md).

---

## Scénario 1 : Plusieurs capteurs, peu de broches

### Analyse (ce qu'il faut comprendre)

- **Contexte** : Trois capteurs, peu de broches, débit non critique (1 mesure/s). Il faut un bus qui permette **plusieurs esclaves** avec **peu de fils**.
- **UART** : point à point ; pour trois capteurs il faudrait **3 UART** (3 × TX, 3 × RX + GND) → beaucoup de broches. Peu adapté ici.
- **SPI** : un maître, plusieurs esclaves possibles, mais avec **une ligne CS par esclave** (plus SCK, MOSI, MISO communs) → 3 + 3 = 6 broches minimum. Possible mais plus de broches qu’I2C.
- **I2C** : **2 fils** (SDA, SCL) partagés par tous les esclaves, **adressage** logiciel (7 bits) → seulement **2 broches** + GND pour trois capteurs. Débit 100–400 kHz suffit pour une lecture par seconde.

### La solution

- **Recommandation** : **I2C**, car peu de broches (2 + GND), multi-esclaves natif par adresse, débit suffisant pour des capteurs lus périodiquement.
- **À vérifier** : (1) que chaque capteur a une **adresse I2C** différente (datasheet ; certaines ont des broches pour choisir l’adresse). (2) Pull-up sur SDA et SCL (4,7 kΩ typ.). (3) Distance courte (carte unique ou câble court) pour limiter la capacité du bus.

### Un autre piège : mélanger les broches I2C et GPIO

Sur un MCU, les broches I2C sont souvent **multiplexées** avec d’autres fonctions. Il faut **configurer** les broches en mode **I2C** (alternate function) dans les registres GPIO, et activer l’horloge du périphérique I2C. Sinon, les lignes ne sont pas pilotées correctement par le bloc I2C.

---

## Scénario 2 : Debug vers PC et flash externe rapide

### Analyse

- **Debug vers PC** : liaison **point à point** avec un terminal sur PC ; débit modéré (9600–115200 souvent suffisant). Pas besoin de multi-esclaves ni de très haut débit. **Usage typique** : UART (souvent via USB-série sur la carte).
- **Flash externe rapide** : **gros volumes** de données, **débit élevé** pour réduire le temps d’écriture/lecture. Full-duplex utile (envoyer commande + adresse, recevoir données en parallèle). **Usage typique** : **SPI** (débit MHz, full-duplex, une ligne CS pour la flash).

### La solution

- **Debug** : **UART** (TX, RX vers convertisseur USB-série). Simple, standard pour les terminaux, peu de broches.
- **Flash externe** : **SPI** (SCK, MOSI, MISO, CS). Vérifier le **mode** SPI (CPOL/CPHA) et la **fréquence max** supportée par la flash (datasheet).
- Les deux peuvent coexister sur la même carte : un **périphérique UART** pour le debug, un **périphérique SPI** pour la flash (broches différentes).

### Un autre piège : partager un bus SPI entre flash et autre esclave

Si la flash et un autre composant (ex. écran) sont sur le **même** bus SPI, ils ont chacun leur **CS**. Il faut **désélectionner** l’un (CS à 1) avant de **sélectionner** l’autre (CS à 0), et ne jamais avoir deux CS actives en même temps. Bien gérer les séquences pour éviter de envoyer des commandes au mauvais composant.

---

**Retour** : [Scénarios – Comparaison et choix](../scenarios/comparaison-choix.md) · [Leçon 5 – Comparaison et choix](../05-comparaison-choix.md)
