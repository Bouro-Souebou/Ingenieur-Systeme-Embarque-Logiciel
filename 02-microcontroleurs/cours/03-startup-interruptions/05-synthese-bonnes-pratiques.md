# Leçon 5 – Synthèse et bonnes pratiques

## Objectif de la leçon

Récapituler le **parcours** reset → startup → main, la **chaîne** configuration → activation → handler, et les **bonnes pratiques** pour éviter les pièges courants. Préparer la suite vers le module **RTOS**.

---

## 1. Parcours complet : du reset à l’ISR

1. **Reset** : CPU charge SP et PC depuis la table des vecteurs (flash).
2. **Reset_Handler** : copie .data, zero .bss, appelle **main()**.
3. **main()** : initialise les périphériques (horloges, GPIO, etc.), **configure** les sources d’interruption (EXTI, UART, …), **active** les IRQ dans le NVIC, puis entre dans la boucle principale (ou démarre le RTOS).
4. Quand un **événement** se produit, le périphérique met son bit pending ; le **NVIC** envoie la requête au cœur ; le cœur **sauvegarde** le contexte, **charge** l’adresse du handler depuis la table des vecteurs, et **exécute** ton ISR.
5. L’**ISR** fait le minimum (flag, buffer, clear pending), puis **retourne** ; le cœur **restaure** le contexte et reprend le code interrompu.

---

## 2. Checklist « Interruptions »

- [ ] **Handler** : nom **exact** (celui du startup), signature `void isr(void)`.
- [ ] **Acquittement** : clear du bit pending dans le périphérique (et éventuellement dans le NVIC si documenté).
- [ ] **ISR courte** : pas de printf, pas de boucle longue, pas d’attente bloquante ; traitement lourd en tâche ou en boucle principale.
- [ ] **Activation** : périphérique configuré pour générer l’IRQ + `NVIC_EnableIRQ(IRQn)` (et priorité si besoin).
- [ ] **Variables partagées** avec l’ISR déclarées **volatile** (ou accès via une queue/sémaphore en RTOS).

---

## 3. Pièges courants

- **Oublier le clear pending** → rappel en boucle de l’ISR (boucle infinie, ou saturation du processeur).
- **Nom d’ISR incorrect** (typo, mauvaise casse) → le linker garde le symbole Weak ; ton code n’est jamais appelé (ou le Weak fait une boucle infinie).
- **Activer l’IRQ avant d’avoir un handler** (ou un handler qui n’acquitte pas) → comportement imprévisible.
- **ISR trop longue** → latence pour les autres interruptions, possible perte de données (ex. UART) ou dépassement de délais.

---

## 4. Suite : module RTOS

Avec les **interruptions**, tu peux réagir à des événements (bouton, UART, timer). Pour **structurer** le logiciel en plusieurs activités (acquisition, commande, communication), le module **03 – RTOS** (FreeRTOS) introduit les **tâches**, les **files d’attente** et les **sémaphores** : l’ISR donne un sémaphore ou envoie un message, et une **tâche** dédiée fait le traitement. Cela respecte la règle « ISR courte » et permet de gérer plusieurs échéances de façon claire.

---

## 5. Résumé du cours « Startup et interruptions »

- **Reset** : SP et PC chargés depuis la table des vecteurs ; **Reset_Handler** initialise .data/.bss puis appelle **main()**.
- **Startup** : fournit la table des vecteurs et le Reset_Handler ; handlers Weak pour le reste.
- **ISR** : fonction au **nom du vecteur**, **courte**, qui **acquitte** l’interruption.
- **Activation** : config du **périphérique** + **NVIC_EnableIRQ** (et priorité).

---

## Tester sa compréhension

→ [Scénario – Synthèse et bonnes pratiques](scenarios/05-synthese-bonnes-pratiques.md) · [Réponse](reponses/05-synthese-bonnes-pratiques.md)

---

**Fin du cours Startup, reset et vecteurs d’interruption.**  
Retour à la [vue d’ensemble](README.md) du module Microcontrôleurs ou au [README principal](../../README.md) du parcours.  
→ **Module suivant** : [03 – RTOS](../../../03-rtos/README.md).
