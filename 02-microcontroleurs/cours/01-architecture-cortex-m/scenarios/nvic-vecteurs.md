# Scénarios – NVIC et vecteurs

Pour la leçon [NVIC et vecteurs](../05-nvic-vecteurs.md).

---

## Scénario 1 : Priorité

ISR timer **priorité 2**, ISR UART **priorité 5**. Pendant l’exécution de l’ISR UART, le timer déclenche. Le processeur interrompt-il l’ISR UART pour exécuter l’ISR timer ? (Plus le nombre est petit, plus la priorité est élevée.)

---

## Scénario 2 : Table des vecteurs

À quel offset : valeur initiale du **SP** ? Adresse du **Reset_Handler** ? Qui fournit cette table dans un projet STM32 ?

---

**Réponses** : [../reponses/nvic-vecteurs.md](../reponses/nvic-vecteurs.md) · **Retour** : [Architecture Cortex-M](../README.md)
