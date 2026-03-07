# Réponse – Synthèse et bonnes pratiques

Voir [scénario](../scenarios/05-synthese-bonnes-pratiques.md).

---

## Réponse Scénario 1 : Checklist

**Étapes** : (1) **Handler** : nom exact, signature void isr(void). (2) **Acquittement** : clear pending dans le périphérique (et NVIC si doc). (3) **Activation** : config périphérique pour générer l'IRQ + **NVIC_EnableIRQ(IRQn)** (et priorité si besoin). (4) **ISR courte** : flag, buffer, clear ; pas de printf ni attente bloquante.

**volatile** : L'ISR et le code principal accèdent à la **même** variable. Sans **volatile**, le compilateur peut optimiser (cache en registre) et le code principal ne « voit » pas la mise à jour faite dans l'ISR. En RTOS : préférer **queue** ou **sémaphore** pour communiquer.

**ISR longue** : **Latence** pour les autres IRQ ; **perte** de données (ex. UART si le buffer déborde) ; risque de **dépassement** de délais temps réel.

---

## Réponse Scénario 2 : Nom incorrect

**Pourquoi** : Le **nom** doit être **exactement** celui du startup (**EXTI0_IRQHandler**). **Exti0_IRQHandler** (casse différente) est un **autre** symbole pour le linker. La table des vecteurs pointe toujours vers le handler déclaré dans le startup (Weak).

**Version utilisée** : Le **Weak** du fichier startup : souvent une boucle infinie, une fonction vide ou un **Default_Handler**. Notre fonction n'est jamais appelée.

**Vérifier** : Ouvrir le **fichier startup** (.s) et chercher le nom du vecteur pour EXTI0 (ex. EXTI0_IRQHandler). Ou **Reference Manual** / header CMSIS pour la liste des symboles d'interruption.

---

**Retour** : [Scénarios](../scenarios/README.md) · [Leçon 5](../05-synthese-bonnes-pratiques.md)
