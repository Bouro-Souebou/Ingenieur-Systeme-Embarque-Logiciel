# Réponses – Startup et interruptions

Voir [scénarios](../scenarios/isr-activation.md).

---

## Scénario 1 : L'ISR n'est jamais appelée

**Problème** : L’**IRQ** doit être **activée dans le NVIC** (`NVIC_EnableIRQ(EXTI0_IRQn)`). Sans cela, le processeur n’exécute pas l’ISR même si le périphérique génère la requête.

**Solution** : Après la config du périphérique (GPIO, EXTI), appeler **NVIC_EnableIRQ** (et éventuellement NVIC_SetPriority). Les deux niveaux : enable dans le **périphérique** et enable dans le **NVIC**.

**Piège** : Oublier le bit enable côté périphérique (ex. ligne EXTI, interruption RXNE UART).

---

## Scénario 2 : HardFault au premier appui

**Problème** : Adresse dans la **table des vecteurs** incorrecte (ISR absente ou mauvais nom, table non initialisée, stack overflow).

**Solution** : **Nom exact** de l’ISR (celui du fichier startup, ex. `EXTI0_IRQHandler`). **Lier** le fichier startup (`.s`) qui définit la table. Vérifier la **taille de la stack** (linker script).

**Piège** : En sortie d’ISR, **acquitter** l’interruption (clear pending) pour éviter rappel en boucle.

---

**Retour** : [Scénarios](../scenarios/README.md) · [Startup et interruptions](../README.md)
