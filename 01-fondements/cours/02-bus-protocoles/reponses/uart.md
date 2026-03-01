# Éléments de réponse – UART

Réponses pour les [scénarios UART](../scenarios/uart.md).

---

## Scénario 1 : Baudrate différent entre émetteur et récepteur

### Analyse (ce qu'il faut comprendre)

- **Le problème** : En UART asynchrone, il n'y a pas de fil d'horloge commun. Chaque côté échantillonne la ligne en supposant une durée de bit fixe (baudrate). Si l'émetteur envoie à 115200 bauds et le récepteur attend 9600 bauds, le récepteur échantillonne beaucoup plus lentement et interprète le signal comme un nombre de bits différent.
- **La conséquence** : Les caractères reçus sont erronés (symboles bizarres, données aléatoires). La liaison est instable.
- **Le risque** : Données ou commandes corrompues ; debug difficile si on ne vérifie pas le baudrate.

### La solution

**Règle** : l'émetteur et le récepteur doivent avoir **exactement les mêmes paramètres** : baudrate, bits de données (7/8), parité, bits d'arrêt. Vérifier la configuration du MCU et du terminal (ou du second appareil).

### Un autre piège : TX/RX croisés

Pour connecter deux UART : **TX** de l'un vers **RX** de l'autre (et inversement). Si on connecte TX–TX et RX–RX, aucun signal n'est reçu. Toujours croiser TX et RX ; GND commun.

---

## Scénario 2 : Réception sans buffer ni interruption

### Analyse

- **Le problème** : Les données UART arrivent en continu. Si le logiciel est bloqué ailleurs (traitement long, délai), il ne lit pas le registre de réception à temps. Le périphérique a en général un seul registre (ou un petit buffer) : un nouveau caractère **écrase** le précédent non lu → **perte**.
- **La conséquence** : Perte de caractères. Trames invalides, commandes tronquées.
- **Le risque** : Bugs intermittents selon la charge du processeur.

### La solution

Utiliser un **buffer** (circulaire) et des **interruptions** : à chaque caractère reçu, l'ISR place l'octet dans le buffer ; le programme principal (ou une tâche) lit et traite les données. En RTOS : tâche dédiée + file alimentée par l'ISR. Ne pas compter sur un simple polling si d'autres traitements retardent la lecture.

### Un autre piège : débit trop élevé pour le logiciel

Même avec un buffer, si le traitement est plus lent que le débit d'arrivée, le buffer **déborde**. Dimensionner le buffer, réduire le débit ou accélérer le traitement (ou DMA).

---

**Retour** : [Scénarios – UART](../scenarios/uart.md) · [Leçon 2 – UART en détail](../02-uart-en-detail.md)
