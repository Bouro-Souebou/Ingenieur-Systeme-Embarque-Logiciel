# Réponse – Déclarer et implémenter une ISR

Voir [scénario](../scenarios/03-declarer-implementer-isr.md).

---

## Réponse Scénario 1 : Nom et signature

**Nom** : **EXTI0_IRQHandler** (exactement comme dans le startup : casse et orthographe). Une typo ou une autre casse fait que le linker garde le symbole **Weak** et notre code n'est jamais appelé.

**Signature** : `void EXTI0_IRQHandler(void)` — **sans** paramètre, **sans** valeur de retour. Le compilateur génère le prologue/epilogue et l'instruction de retour adaptée au mode Handler.

**Linker** : Si on définit une fonction avec le **même nom** que le symbole Weak du startup, le linker choisit **notre** définition (overwrite). L'adresse de notre fonction est alors dans la table des vecteurs.

---

## Réponse Scénario 2 : Acquittement et ISR courte

**Cause** : Le bit **pending** de l'IRQ n'est pas **effacé**. À la sortie du handler, le NVIC voit encore l'IRQ en attente et rappelle le handler → **boucle infinie**.

**Acquitter** : Dans le **périphérique** : pour EXTI, écrire **1** dans le bit correspondant du registre **EXTI->PR** (Pending Register) efface le pending. Référence : Reference Manual, section EXTI.

**Contenu ISR** : **Minimum** : flag ou buffer, puis **clear pending**. Traitement lourd (printf, calculs, attente) dans une **tâche** ou la **boucle principale**, déclenchée par le flag ou une queue/sémaphore.

---

**Retour** : [Scénarios](../scenarios/README.md) · [Leçon 3](../03-declarer-implementer-isr.md)
