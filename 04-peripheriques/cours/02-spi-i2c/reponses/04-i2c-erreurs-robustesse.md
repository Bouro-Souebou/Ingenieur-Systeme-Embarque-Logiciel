# Réponse – I2C : erreurs et robustesse

Voir [scénario](../scenarios/04-i2c-erreurs-robustesse.md).

---

## Réponse Scénario 1 : Timeout et esclave absent

**Danger** : Si l'esclave ne répond pas, le maître peut attendre indéfiniment → application freeze.

**Timeout** : Configurer une limite de temps (HAL : Timeout ; bas niveau : timer). À l'expiration : abandonner, générer STOP, réinitialiser le contrôleur si besoin, retour d'erreur.

---

## Réponse Scénario 2 : Bus busy après une erreur

**Cause** : Un esclave peut retenir SDA à 0 après une interruption brutale. Bus busy.

**Récupération** : Générer 9 impulsions sur SCL (recovery) pour que l'esclave relâche ; puis STOP. Reference Manual : section I2C, error recovery.

---

**Retour** : [Scénarios](../scenarios/README.md) · [Leçon 4](../04-i2c-erreurs-robustesse.md)
