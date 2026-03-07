# Scénario – Envoi et réception en polling

Pour la leçon [02 – Envoi et réception en polling](../02-polling.md).

---

## Scénario 1 : Envoi d'une chaîne

Une tâche doit envoyer la chaîne `"OK\r\n"` sur l'UART. Le code fait une boucle qui écrit chaque caractère dans le registre **DR** sans attendre.

**Questions** : Pourquoi les caractères peuvent-ils être **tronqués** ou mélangés ? Quel **flag** doit être à 1 avant d'écrire l'octet suivant (TXE) ? Où trouver ce flag dans le Reference Manual ?

---

## Scénario 2 : Réception bloquante

Le code appelle une fonction **uart_recv_byte()** qui fait une boucle `while (!(USART1->SR & USART_SR_RXNE));` puis lit DR. L'application doit aussi réagir à un **bouton** toutes les 10 ms.

**Questions** : Pourquoi le bouton ne sera-t-il pas réactif si on attend un caractère (polling bloquant) ? Dans quels cas le polling UART reste-t-il acceptable ? Que préférer pour une application réactive (interruption, RTOS) ?

---

**Réponse** : [../reponses/02-polling.md](../reponses/02-polling.md) · **Retour** : [Vue d'ensemble](../README.md)
