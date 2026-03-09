# TP 3 – Bouton + LED (polling)

**Objectif** : lire l’état du **bouton utilisateur B1** (PC13) et piloter la **LED LD2** (PA5) en **polling** (boucle principale).

## Cible NUCLEO-F446RE

- Bouton B1 = **PC13** (entrée). Câblage actif à 0 : appuyé = niveau bas (GND).
- LED LD2 = **PA5** (sortie), comme au TP 2.

## Comportement attendu

- Tant que le bouton n’est **pas** appuyé : LED éteinte (ou fixe).
- Quand le bouton est **appuyé** : LED allumée (ou inverse, au choix).

Variante : inverser l’état de la LED à chaque **front** détecté (simple anti-rebond par délai) pour un effet toggle.

## Fichiers

- **main.c** : initialisation GPIO A (sortie PA5) et GPIO C (entrée PC13, optionnel pull-up), boucle qui lit PC13 et met à jour PA5.

## Références

- Cours 02 (GPIO entrée, registre IDR).
- Reference Manual : GPIO IDR, MODER (mode entrée).

**Suite** : [TP 4 – Interruption EXTI](../04-interruption-exti/README.md) (réaction au bouton par ISR).
