# Scénario – Familles Cortex-M

Pour la leçon [02 – Familles Cortex-M](../02-familles-cortex-m.md).

---

## Scénario 1 : Choisir un cœur pour un projet

On développe un **régulateur PID** avec calculs en **float** et boucle à 10 kHz. Le MCU doit être raisonnable en coût.

**Questions** : Quelle famille Cortex-M privilégier (M3, M4, M7) et pourquoi (FPU pour le float) ? Quelle différence entre M3 et M4 côté calcul flottant (FPU optionnelle en M4) ?

---

## Scénario 2 : M0+ vs M4

Un capteur **IoT** sur pile doit envoyer une trame toutes les minutes et dormir le reste du temps. Un autre projet pilote un **moteur** avec FOC (calculs trigo et flottant en temps réel).

**Questions** : Pour l'IoT sur pile : quel type de cœur (M0/M0+) et pourquoi (ultra faible consommation, coût) ? Pour le moteur FOC : quel type (M4 avec FPU ou M7) et pourquoi (calculs flottants, débit) ?

---

**Réponse** : [../reponses/02-familles-cortex-m.md](../reponses/02-familles-cortex-m.md) · **Retour** : [Vue d'ensemble](../README.md)
