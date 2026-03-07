# Scénario – ADC : principes

Pour la leçon [01 – ADC : principes](../01-adc-principes.md).

---

## Scénario 1 : Tension et valeur numérique

L'ADC est en **12 bits**, **Vref = 3,3 V**. On lit la valeur **4095** dans le registre DR.

**Questions** : Quelle **tension** cela représente-t-il (formule V = valeur / (2^N - 1) × Vref) ? Si on lit **0**, quelle tension ? Quelle est la **résolution** en tension (plus petit pas) ?

---

## Scénario 2 : Trigger et canaux

On doit acquérir un **capteur de température** (canal 5) une fois par seconde, et un **potentiomètre** (canal 2) à la demande (bouton).

**Questions** : Quel **trigger** pour le capteur (logiciel SWSTART, ou timer pour 1 Hz) ? Quel trigger pour le potentiomètre (SWSTART sur événement bouton) ? Les broches des canaux doivent être en quel mode GPIO (analog) ?

---

**Réponse** : [../reponses/01-adc-principes.md](../reponses/01-adc-principes.md) · **Retour** : [Vue d'ensemble](../README.md)
