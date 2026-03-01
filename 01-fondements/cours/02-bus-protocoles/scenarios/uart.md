# Scénarios – UART

Situations pour vérifier votre compréhension de la [Leçon 2 – UART en détail](../02-uart-en-detail.md).

---

## Scénario 1 : Baudrate différent entre émetteur et récepteur

L'**émetteur** (MCU) est configuré à **115200 bauds**, le **récepteur** (terminal sur PC, ou un second MCU) à **9600 bauds**. On envoie le caractère `'A'` (0x41).

**Questions** : Que observe-t-on côté récepteur (caractère reçu, stabilité) ? Pourquoi ? Quelle règle en déduire ?

---

## Scénario 2 : Réception sans buffer ni interruption

Un programme lit l'UART en **polling** dans une boucle : à chaque tour, il teste « un caractère est-il arrivé ? » et, si oui, le lit. Pendant ce temps, il fait aussi un **traitement long** (calcul, délai de 100 ms) avant de revenir tester l'UART.

**Questions** : Quel risque pour les caractères reçus pendant le traitement ? Quelle approche recommandée pour ne pas perdre de données ?

---

*Après avoir réfléchi, consultez les* [**Éléments de réponse – UART**](../reponses/uart.md).

---

**Retour** : [Leçon 2 – UART en détail](../02-uart-en-detail.md) · [Vue d'ensemble du cours Bus](../README.md)
