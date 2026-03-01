# Réponses – Mémoire et bus

Voir [scénarios](../scenarios/memoire-bus.md).

---

## Scénario 1 : Régions d’adressage

**Réponse** : Sur Cortex-M (ex. STM32), l’espace 32 bits est découpé en **régions** : **Code** (flash, ex. 0x0800_0000) pour le programme et les constantes ; **RAM** (ex. 0x2000_0000) pour variables globales, stack, heap ; **Périphériques** (ex. 0x4000_0000) pour les registres (GPIO, UART, etc.). Les adresses des périphériques sont **fixes** et définies dans le Reference Manual : le logiciel accède toujours au même bloc à la même adresse (memory-mapped I/O).

---

## Scénario 2 : Adresse invalide

**Réponse** : 0x0800_1000 est typiquement en **flash** (région code). Écrire dans cette zone sans passer par le contrôleur de flash peut provoquer un **BusFault** ou un comportement indéfini. Les écritures en flash nécessitent un protocole spécifique (déblocage, programmation). Ne pas confondre adresses périphériques (0x4xxx_xxxx) et adresses flash (0x08xx_xxxx).

---

**Retour** : [Scénarios](../scenarios/README.md) · [Architecture Cortex-M](../README.md)
