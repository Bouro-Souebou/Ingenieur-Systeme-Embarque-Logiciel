# TP 4 – Interruption EXTI (bouton)

**Objectif** : réagir au **bouton B1** (PC13) par **interruption** : configurer EXTI et NVIC, dans l’**ISR** inverser l’état de la LED (toggle).

## Cible NUCLEO-F446RE

- PC13 = ligne **EXTI13**. IRQ partagée : **EXTI15_10** (vecteur EXTI15_10_IRQn).
- Bouton actif à 0 : utiliser **front descendant** (FTSR) pour déclencher l’IRQ à l’appui.

## Étapes

1. Activer l’horloge **SYSCFG** (APB2ENR).
2. Relier PC13 à EXTI13 : **SYSCFG_EXTICR4** (broche 13 = port C => 2).
3. **EXTI** : masque ligne 13 (IMR), front descendant (FTSR), pas RTSR.
4. **NVIC** : activer EXTI15_10_IRQn.
5. Dans l’**ISR** : effacer le flag (EXTI_PR bit 13), puis inverser la LED (variable `volatile` ou accès direct ODR).

Le **fichier startup** doit déclarer le symbole du vecteur (ex. `EXTI15_10_IRQHandler`) ; selon le projet, il peut déjà être présent avec une version faible. Déclarer votre handler dans `main.c` ou un fichier dédié.

## Fichiers

- **main.c** : init RCC/GPIO/SYSCFG/EXTI/NVIC, variable `volatile` pour l’état LED si le toggle est fait dans l’ISR, et `EXTI15_10_IRQHandler`.

## Références

- Cours 01 (NVIC), 03 (startup, déclaration ISR).
- Reference Manual : SYSCFG_EXTICR4, EXTI (IMR, FTSR, PR), NVIC.
