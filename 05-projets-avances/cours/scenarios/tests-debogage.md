# Scénarios – Tests, débogage et outillage

Situations pour vérifier votre compréhension du cours [5.2 – Tests, débogage et outillage](02-tests-debogage.md).

---

## Scénario 1 : Tester sans la carte

Vous voulez valider la **logique** d’un parser de commandes UART (ex. découpage des champs, conversion des valeurs) sans brancher la carte. Le code actuel appelle `UART_Receive()` et `UART_Send()` du HAL.

**Question** : Quelle approche permet de tester cette logique sur PC (ex. en CI) ? Quel rôle jouent les **mocks** ou **stubs** ?

---

## Scénario 2 : HardFault en production

Un firmware tourne correctement en développement. Après plusieurs heures en production, le MCU entre en **HardFault** sans message. Vous avez accès au débogueur une fois le fault déclenché.

**Questions** : Quelles **causes fréquentes** (mémoire, concurrence) ? Quels **outils** ou **informations** (registres, stack) utiliser pour localiser la cause ?

---

*Après avoir réfléchi, consultez les* [**Éléments de réponse – Tests et débogage**](../reponses/tests-debogage.md).

---

**Retour** : [5.2 – Tests, débogage](02-tests-debogage.md) · [Vue d’ensemble 05](../../README.md)
