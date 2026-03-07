# Scénario – Vue d'ensemble du Cortex-M

Pour la leçon [01 – Vue d'ensemble du Cortex-M](../01-vue-ensemble.md).

---

## Scénario 1 : Cœur pour l'embarqué

Un projet doit tourner sur **pile** avec **faible consommation** et **réactivité** aux événements (bouton, capteur). On hésite entre un processeur type PC et un MCU ARM.

**Questions** : Pourquoi un **Cortex-M** est-il adapté à l'embarqué (pas de MMU, NVIC intégré, RISC) ? En quoi l'absence de **MMU** simplifie le modèle (adresses physiques, pas de Linux classique) ?

---

## Scénario 2 : Thumb et taille du code

La **flash** du MCU est limitée (64 Ko). Le compilateur génère du code **Thumb-2** pour un Cortex-M4.

**Questions** : Quel avantage du **Thumb** (instructions 16 bits) pour la taille du code ? Qui choisit les instructions (programmeur ou compilateur) ? Que signifie Thumb-2 (mélange 16/32 bits) ?

---

**Réponse** : [../reponses/01-vue-ensemble.md](../reponses/01-vue-ensemble.md) · **Retour** : [Vue d'ensemble](../README.md)
