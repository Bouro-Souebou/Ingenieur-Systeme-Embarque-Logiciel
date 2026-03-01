# Scénarios – Comparaison et choix du protocole

Situations pour vérifier votre compréhension de la [Leçon 5 – Comparaison et choix](../05-comparaison-choix.md).

---

## Scénario 1 : Plusieurs capteurs, peu de broches

Vous devez connecter **trois capteurs** (température, pression, humidité) à un MCU qui a **peu de broches** disponibles. Les capteurs n'ont pas besoin d'un débit très élevé ; les données sont lues périodiquement (ex. une fois par seconde).

**Question** : Quel bus recommanderiez-vous (UART, SPI, I2C) et pourquoi ? Que faut-il vérifier côté composants (adresses, broches) ?

---

## Scénario 2 : Debug vers un PC et flash externe rapide

Sur la même carte, vous avez besoin de : (1) envoyer des **messages de debug** vers un PC (terminal série) ; (2) lire/écrire une **mémoire flash** externe à **débit élevé** pour enregistrer des blocs de données.

**Questions** : Quel(s) protocole(s) utiliser pour chaque usage ? Justifiez en une phrase (nombre de fils, débit, usage typique).

---

*Après avoir réfléchi, consultez les* [**Éléments de réponse – Comparaison et choix**](../reponses/comparaison-choix.md).

---

**Retour** : [Leçon 5 – Comparaison et choix](../05-comparaison-choix.md) · [Vue d'ensemble du cours Bus](../README.md)
