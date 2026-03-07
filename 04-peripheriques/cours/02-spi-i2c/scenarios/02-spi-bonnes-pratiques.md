# Scénario – SPI : bonnes pratiques

Pour la leçon [02 – SPI : bonnes pratiques](../02-spi-bonnes-pratiques.md).

---

## Scénario 1 : CS et setup/hold

Le datasheet d'un capteur SPI impose un **setup time** de 100 ns entre l'activation de CS et le premier front SCK, et un **hold time** de 50 ns après le dernier front SCK avant de désactiver CS. Le développeur active CS, envoie immédiatement le premier octet, et désactive CS dès la lecture du dernier octet reçu.

**Questions** : Que peut provoquer le non-respect du setup (données mal interprétées par l'esclave) ? Et du hold (dernier bit perdu ou instable) ? Comment garantir ces délais en logiciel (petit délai, ou attente explicite du flag de fin de transfert avant de toucher à CS) ?

---

## Scénario 2 : Deux tâches sur le même bus SPI

Une tâche lit un **capteur** (SPI) toutes les 100 ms ; une autre écrit dans une **EEPROM** SPI à la demande. Les deux utilisent le même bus (MOSI, MISO, SCK) avec des CS différents. Parfois les données du capteur sont mélangées avec des octets destinés à l'EEPROM.

**Questions** : Pourquoi le mélange (accès concurrent sans protection) ? Quelle primitive utiliser pour **sériariser** les accès (mutex) ? Où prendre et rendre le mutex (avant/après activation de CS, après désactivation de CS) ?

---

**Réponse** : [../reponses/02-spi-bonnes-pratiques.md](../reponses/02-spi-bonnes-pratiques.md) · **Retour** : [Vue d'ensemble](../README.md)
