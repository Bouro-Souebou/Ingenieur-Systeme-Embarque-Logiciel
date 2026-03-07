# Scénario – Le fichier startup

Pour la leçon [02 – Le fichier startup](../02-fichier-startup.md).

---

## Scénario 1 : Table des vecteurs et Weak

Le projet ne définit pas de **USART2_IRQHandler**. Au démarrage, une IRQ USART2 est en attente. Que se passe-t-il ?

**Questions** : Qui fournit l'adresse pour l'entrée USART2 dans la table (fichier startup) ? Que signifie un handler **Weak** (défaut remplaçable) ? Si on définit `void USART2_IRQHandler(void) { ... }` en C, quelle version est utilisée (la nôtre) ?

---

## Scénario 2 : Reset_Handler et sections

Le Reset_Handler doit copier .data et mettre .bss à zéro avant main().

**Questions** : D'où viennent les symboles **_sdata**, **_edata**, **_sidata** (linker script) ? À quoi sert **_sidata** (adresse en flash des valeurs initiales de .data) ? Pourquoi ne pas modifier l'ordre des vecteurs dans le startup (architecture ARM impose offset 0 = SP, 4 = Reset_Handler, etc.) ?

---

**Réponse** : [../reponses/02-fichier-startup.md](../reponses/02-fichier-startup.md) · **Retour** : [Vue d'ensemble](../README.md)
