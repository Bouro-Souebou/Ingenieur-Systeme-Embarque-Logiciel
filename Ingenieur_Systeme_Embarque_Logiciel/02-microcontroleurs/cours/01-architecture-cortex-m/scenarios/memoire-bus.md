# Scénarios – Mémoire et bus

Pour vérifier votre compréhension des leçons [Mémoire et bus](../04-memoire-et-bus.md) et de la carte mémoire Cortex-M.

---

## Scénario 1 : Où se trouve le code ? Où sont les périphériques ?

Sur un STM32, on lit un registre GPIO avec `*(uint32_t *)0x40020010`. Une variable globale est placée en RAM.

**Questions** : Dans quelle **région** d’adressage se trouvent typiquement le **programme** (code), la **RAM** et les **périphériques** sur un Cortex-M ? Pourquoi utiliser des adresses **fixes** pour les périphériques ?

---

## Scénario 2 : Adresse invalide

Un développeur écrit par erreur dans l’adresse **0x08001000** en croyant modifier un registre.

**Question** : Que risque-t-il (quelle région, quel comportement) ?

---

**Réponses** : [../reponses/memoire-bus.md](../reponses/memoire-bus.md)

**Retour** : [Architecture Cortex-M](../README.md)
