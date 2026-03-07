# Scénario – Séquence au reset

Pour la leçon [01 – Séquence au reset](../01-sequence-reset.md).

---

## Scénario 1 : Premier accès mémoire

Au reset, le processeur doit exécuter la première instruction. Il lit deux valeurs à des adresses fixes.

**Questions** : À quel **offset** de la table des vecteurs se trouve la valeur initiale du **SP** ? À quel offset se trouve l'adresse du **Reset_Handler** ? Pourquoi la table doit-elle être en **flash** (ou mappée) à l'adresse attendue au boot ?

---

## Scénario 2 : Rôle du Reset_Handler

Avant d'appeler **main()**, le Reset_Handler effectue des étapes d'initialisation.

**Questions** : Que fait la **copie de .data** (flash vers RAM) et pourquoi (variables initialisées) ? Que fait le **zero-fill de .bss** ? Pourquoi **main()** ne doit-il pas retourner normalement (boucle infinie ou RTOS) ?

---

**Réponse** : [../reponses/01-sequence-reset.md](../reponses/01-sequence-reset.md) · **Retour** : [Vue d'ensemble](../README.md)
