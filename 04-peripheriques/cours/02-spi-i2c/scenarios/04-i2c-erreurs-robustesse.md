# Scénario – I2C : erreurs et robustesse

Pour la leçon [04 – I2C : erreurs et robustesse](../04-i2c-erreurs-robustesse.md).

---

## Scénario 1 : Timeout et esclave absent

L'application envoie une transaction I2C vers un esclave (capteur) qui peut être **débranché** ou en panne. Le maître reste bloqué en attente d'ACK et l'application ne répond plus.

**Questions** : Pourquoi une attente **sans limite** est dangereuse (pas d'ACK, clock stretching infini) ? Comment configurer un **timeout** (HAL, timer logiciel) ? Que faire en cas de timeout (générer STOP, retour d'erreur, réinitialiser le périphérique si besoin) ?

---

## Scénario 2 : Bus busy après une erreur

Après un crash ou un timeout mal géré, les transactions I2C suivantes échouent : le driver indique « bus busy ». SDA ou SCL restent dans un état anormal.

**Questions** : Quelle peut être la cause (esclave qui tire SDA à 0, transfert interrompu) ? Quelle **procédure de récupération** existe sur beaucoup de MCU (impulsions sur SCL pour que l'esclave relâche, puis STOP) ? Où trouver la description (Reference Manual, section I2C / error recovery) ?

---

**Réponse** : [../reponses/04-i2c-erreurs-robustesse.md](../reponses/04-i2c-erreurs-robustesse.md) · **Retour** : [Vue d'ensemble](../README.md)
