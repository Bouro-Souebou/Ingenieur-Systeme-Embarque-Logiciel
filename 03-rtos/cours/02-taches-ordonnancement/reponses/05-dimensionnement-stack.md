# Réponse – Dimensionnement stack

Voir [scénario](../scenarios/05-dimensionnement-stack.md).

---

## Réponse Scénario 1 : HardFault après plusieurs heures

**Cause** : **Stack overflow** d'une tâche (zone stack débordée → corruption / HardFault).

**Détection** : configCHECK_FOR_STACK_OVERFLOW (1 ou 2) + **vApplicationStackOverflowHook** (breakpoint ou LED).

**Dimensionner** : selon profondeur d'appels et variables locales ; **marge** en dev ; **uxTaskGetStackHighWaterMark** pour voir la marge réelle et ajuster.

---

## Réponse Scénario 2 : Stack trop grande « au cas où »

**Compromis** : Trop petit → overflow ; trop grand → **gaspillage de RAM** (plus de tâches ou moins de heap). Il faut **juste assez** avec une marge.

**Méthode** : Estimer (taille des variables locales + profondeur d'appels × frame) ; démarrer avec une valeur raisonnable (ex. 256–512 words) ; en dev, activer **uxTaskGetStackHighWaterMark** : après des tests représentatifs, lire la marge restante ; ajuster la taille (ex. high water = 50 → on peut réduire un peu, avec marge de sécurité).

---

**Retour** : [Scénarios](../scenarios/README.md) · [Leçon 5](../05-dimensionnement-stack.md)
