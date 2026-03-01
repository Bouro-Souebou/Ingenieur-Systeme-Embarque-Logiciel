# Scénarios – Registres et GPIO

Pour le cours [Modèle programme et registres](../README.md).

---

## Scénario 1 : La LED ne s'allume pas

PA5 en sortie, on écrit 1 dans ODR. La LED reste éteinte. Quelle cause fréquente (horloge) ? Où configurer ?

---

## Scénario 2 : Lire une entrée

On écrit `REG(GPIOB_ODR) & (1u << 3)` pour lire le bouton PB3. Problème ? Quel registre pour lire une entrée ?

---

**Réponses** : [../reponses/registres-gpio.md](../reponses/registres-gpio.md) · **Retour** : [Vue d’ensemble](../README.md)
