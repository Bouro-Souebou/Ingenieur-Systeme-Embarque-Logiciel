# Leçon 5 – Contraintes à garder en tête

## Objectif de la leçon

Récapituler les **contraintes** importantes pour concevoir et maintenir un système embarqué temps réel : stack, charge CPU, ressources partagées, et synthèse du cours.

---

## 1. Dimensionner la stack

Chaque **tâche** (en RTOS) et le **contexte d'interruption** ont une **stack** dédiée. Si une fonction utilise beaucoup de variables locales ou appelle des fonctions profondes, la stack peut **déborder** (écraser d'autres zones mémoire) et provoquer un **crash** (souvent HardFault). Il faut donc :

- **Dimensionner** la stack de chaque tâche en fonction du pire cas (appels imbriqués, variables locales).
- **Surveiller** l'utilisation (option « stack overflow check » de FreeRTOS, ou remplissage de la stack avec un motif et lecture du « high water mark »).
- **Éviter** les gros tableaux locaux et la récursion non bornée (voir cours C pour l'embarqué).

---

## 2. Charge CPU

En temps réel, on s'assure que le processeur peut **tenir** toutes les échéances. Si plusieurs tâches sont **périodiques**, la **somme** des temps d'exécution (WCET) de chaque tâche sur sa **période** ne doit pas dépasser 100 % (avec une marge pour le noyau et les interruptions). Sinon, des tâches vont régulièrement dépasser leur délai. Des outils d'**analyse d'ordonnançabilité** (taux d'utilisation) aident à vérifier cela.

---

## 3. Ressources partagées

Quand **plusieurs tâches** (ou une tâche et une ISR) accèdent à la **même** donnée (variable, buffer, périphérique), il faut **protéger** cet accès pour éviter les **race conditions** (résultat dépendant de l'ordre d'exécution). Les mécanismes usuels sont :

- **Section critique** : désactiver les interruptions le temps de lire/modifier/écrire (à garder très court).
- **Mutex** (en RTOS) : une seule tâche à la fois peut détenir le mutex et accéder à la ressource.
- **Files d'attente** : au lieu de partager un buffer « à la main », une tâche produit des messages et l'autre les consomme ; la queue gère la synchronisation.

Ces points sont détaillés dans le module **03 – RTOS** (FreeRTOS).

---

## 4. Synthèse du cours « Temps réel et contraintes »

| Notion | Signification |
|--------|----------------|
| **Temps réel** | Réponse correcte seulement si livrée dans le délai imparti ; dur (critique) vs mou (qualité). |
| **Latence** | Délai entre l'événement et le début du traitement ; à minimiser et borner. |
| **Jitter** | Variation de ce délai ; à réduire pour la stabilité. |
| **Déterminisme** | Comportement reproductible ; éviter heap, boucles non bornées. |
| **ISR courtes** | Traitement minimal en interruption ; le reste en tâche ou en boucle principale. |
| **Super-loop vs RTOS** | Un fil d'exécution vs plusieurs tâches ; RTOS pour échéances multiples et structure. |
| **Stack** | Dimensionner pour chaque tâche ; éviter débordement. |
| **Ressources partagées** | Protéger par section critique ou mutex pour éviter les race conditions. |

---

## Tester sa compréhension

→ [**Scénarios – Contraintes et synthèse**](scenarios/contraintes-synthese.md) · → [**Éléments de réponse**](reponses/contraintes-synthese.md)

---

## 5. Suite du parcours

Avec les **Fondements** (C embarqué, bus, temps réel), tu as les bases pour aborder le module **02 – Microcontrôleurs** : architecture ARM Cortex-M, registres, startup et interruptions sur une vraie cible (ex. STM32). Ensuite, le module **03 – RTOS** (FreeRTOS) te permettra de mettre en pratique les notions de tâches, files et synchronisation.

---

**Fin du cours Temps réel et contraintes.**  
Retour à la [vue d'ensemble](README.md) du module Fondements ou au [README principal](../../README.md) du parcours.
