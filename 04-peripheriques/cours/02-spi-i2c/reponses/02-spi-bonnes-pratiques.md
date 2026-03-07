# Réponse – SPI : bonnes pratiques

Voir [scénario](../scenarios/02-spi-bonnes-pratiques.md).

---

## Réponse Scénario 1 : CS et setup/hold

**Setup** : Si le premier front SCK arrive **trop tôt** après l'activation de CS, l'esclave peut ne pas avoir encore pris en compte la sélection (état interne pas stable) → premier bit ou octet **incorrect**.

**Hold** : Si on désactive CS **trop tôt** après le dernier front SCK, le dernier bit peut ne pas être correctement capté par l'esclave → **donnée tronquée** ou **instable**.

**Garantir** : Après avoir activé CS, insérer un **délai court** (boucle ou attente explicite, ou délai µs si disponible) avant le premier transfert. Après le dernier octet, **attendre** que le flag de fin de transfert soit à jour (RXNE/BSY), puis petit délai si besoin, puis désactiver CS.

---

## Réponse Scénario 2 : Deux tâches sur le même bus SPI

**Mélange** : Sans protection, la tâche 1 peut activer son CS et commencer à envoyer ; la tâche 2 est schedulée, active **son** CS (ou envoie sur le même bus sans CS dédié) → les octets se mélangent, les esclaves reçoivent des données incohérentes.

**Mutex** : **xSemaphoreTake(mutex_spi, timeout)** **avant** d'activer **tout** CS et de faire le transfert ; **xSemaphoreGive(mutex_spi)** **après** avoir désactivé CS et terminé la transaction. Ainsi une seule tâche utilise le bus à la fois. Prendre le mutex avant CS évite qu'une autre tâche s'intercale entre l'activation de CS et le premier octet.

---

**Retour** : [Scénarios](../scenarios/README.md) · [Leçon 2](../02-spi-bonnes-pratiques.md)
