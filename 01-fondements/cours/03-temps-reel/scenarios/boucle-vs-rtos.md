# Scénarios – Boucle principale vs RTOS

Situations pour vérifier votre compréhension de la [Leçon 4 – Boucle principale vs RTOS](../04-boucle-vs-rtos.md).

---

## Scénario 1 : Deux périodes dans une super-loop

Vous devez réaliser un système qui :
- **Lit un capteur** toutes les **10 ms** (pour une régulation).
- **Envoie un résumé sur l'UART** toutes les **100 ms** (pour un moniteur).

Vous implémentez tout dans une **boucle principale** avec deux `delay` : d'abord `delay_ms(10)` et lecture du capteur, puis `delay_ms(100)` et envoi UART.

**Questions** :
1. Quel est le **problème** avec cette approche ?
2. À quelle **période réelle** le capteur est-il lu ? Et l'UART ?
3. Quelle(s) solution(s) proposeriez-vous (sans forcément passer à un RTOS) ?

---

## Scénario 2 : Faut-il un RTOS pour un blink LED ?

Un stagiaire propose d'utiliser **FreeRTOS** pour un projet très simple : une LED clignote toutes les 500 ms et un bouton permet de changer la fréquence. « Comme ça, on est prêts pour la suite. »

**Question** : Est-ce une bonne idée ? Argumentez en termes d’avantages / inconvénients (complexité, ressources, maintenabilité).

---

*Après avoir réfléchi, consultez les* [**Éléments de réponse – Boucle vs RTOS**](../reponses/boucle-vs-rtos.md).

---

**Retour** : [Leçon 4 – Boucle principale vs RTOS](../04-boucle-vs-rtos.md) · [Vue d'ensemble](../README.md)
