# Réponses – Tests et débogage

Voir [scénarios](../scenarios/tests-debogage.md).

---

## Scénario 1 : Tester sans la carte

**Problème** : La logique du parser est couplée aux appels UART ; pas de test sur PC.

**Solution** : Découpler : le parser travaille sur des **buffers** fournis par l’appelant. Sur PC, l’appelant fournit des chaînes de test. **Mocks** : remplacer UART_Receive/Send par des stubs qui renvoient des données configurables. Compiler le parser pour PC (Unity, CppUTest) et lancer en CI.

**Piège** : Pour l’intégration, automatiser avec scripts (Python + pySerial) qui envoient des commandes et vérifient les réponses.

---

## Scénario 2 : HardFault en production

**Problème** : Causes possibles : stack overflow, pointeur invalide, race (variable partagée sans volatile/mutex), buffer overflow.

**Solution** : Au moment du fault, examiner **PC**, **LR**, **SP** et la stack (GDB + OpenOCD) pour la chaîne d’appels. Vérifier tailles de stack, accès pointeurs, usage volatile/mutex, bornes des buffers (snprintf au lieu de sprintf). SWO ou logs UART pour tracer les derniers événements.

**Piège** : En RTOS, vérifier la stack de chaque tâche et les priorités.

---

**Retour** : [Scénarios Tests](../scenarios/tests-debogage.md) · [5.2](../02-tests-debogage.md)
