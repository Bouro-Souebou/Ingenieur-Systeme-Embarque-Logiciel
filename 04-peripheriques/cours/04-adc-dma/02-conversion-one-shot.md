# Leçon 2 – Conversion one-shot

## Objectif de la leçon

Lancer **une** conversion ADC (one-shot) : activer l'horloge et configurer le **canal**, lancer la conversion (**SWSTART**), attendre la **fin** (flag EOC) en polling ou par **interruption**, puis **lire** le registre de résultat (DR).

## 1. Configuration

1. **Activer l'horloge** de l'ADC (et du bus, ex. APB2).
2. **Configurer** la broche en **analog** (mode GPIO analog).
3. **Sélectionner** le canal (registre SQR ou équivalent : numéro du canal dans la séquence).
4. **Régler** le temps d'échantillonnage (sample time) selon le datasheet ADC pour une mesure correcte (impédance de source).

## 2. Lancer et attendre (polling)

1. **Lancer** la conversion : mettre à 1 le bit **SWSTART** (Software Start).
2. **Attendre** que le flag **EOC** (End Of Conversion) soit à 1 (boucle while ou délai borné avec timeout).
3. **Lire** le registre **DR** (Data Register) : contient la valeur sur N bits (alignée à droite en général).
4. Optionnel : **clear** EOC (certains MCU le font à la lecture de DR).

En **interruption** : activer l'IT EOC ; dans l'**ISR**, lire DR et stocker dans un buffer ou envoyer dans une queue pour une tâche de traitement.

## 3. Formule tension

V_tension = (valeur_lue × Vref) / (2^N - 1). Ex. 12 bits, Vref = 3,3 V : valeur 2048 → 3,3 × 2048 / 4095 ≈ 1,65 V.

---

## Tester sa compréhension

→ [Scénario – Conversion one-shot](scenarios/02-conversion-one-shot.md) · [Réponse](reponses/02-conversion-one-shot.md)

---

**Suite** : [Leçon 3 – Mode continu et scan](03-mode-continu-scan.md)
