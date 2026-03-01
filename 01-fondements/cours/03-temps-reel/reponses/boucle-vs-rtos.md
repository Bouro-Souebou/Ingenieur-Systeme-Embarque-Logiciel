# Éléments de réponse – Boucle principale vs RTOS

Réponses pour les [scénarios Boucle vs RTOS](../scenarios/boucle-vs-rtos.md).

---

## Scénario 1 : Deux périodes dans une super-loop

### Analyse (ce qu'il faut comprendre)

- **Le problème** : Dans une super-loop, **un seul fil d'exécution**. Après `delay_ms(10)` et lecture du capteur, on enchaîne avec `delay_ms(100)` et envoi UART. Pendant ces **100 ms**, le capteur **n'est pas lu** : la boucle est bloquée dans le second délai.
- **La conséquence** : Le capteur n'est en pratique lu que **toutes les 110 ms** (10 + 100), pas toutes les 10 ms. L'échéance « 10 ms » n'est **pas respectée**. L'UART, lui, est bien déclenché toutes les 110 ms (à la fin de chaque tour de boucle), ce qui n'est pas non plus les 100 ms voulues.
- **Le risque** : Régulation dégradée ou instable, perte d'échantillons, comportement imprévisible pour tout algorithme qui suppose des périodes fixes.

### La solution

- **Option 1 – Machine à états (toujours en super-loop)** : Ne pas enchaîner deux `delay` longs. Utiliser un **timer** (SysTick ou timer matériel) qui incrémente un compteur toutes les 1 ms. Dans la boucle, tester : « si (compteur - dernier_lecture_capteur >= 10) → lire capteur, mettre à jour dernier_lecture_capteur » ; « si (compteur - dernier_uart >= 100) → envoyer UART, mettre à jour dernier_uart ». Ainsi les deux périodes sont **entrelacées** sur un seul fil d'exécution.
- **Option 2 – RTOS** : Une **tâche** période 10 ms (lecture capteur) et une **tâche** période 100 ms (envoi UART). L'ordonnanceur gère les deux échéances ; plus simple conceptuellement mais plus de ressources (stacks, noyau).

En résumé : avec une super-loop, **plusieurs échéances** nécessitent de **découper le temps** (timer + tests sur les périodes) et non d'enchaîner des délais bloquants.

### Un autre piège : delay dans une tâche RTOS

En RTOS, mettre un `delay(100)` dans une tâche **bloque cette tâche** pendant 100 ms mais **libère le CPU** pour les autres tâches. Donc « deux délais dans une boucle » en RTOS peut être correct si ce sont **deux tâches différentes** avec chacune leur propre `vTaskDelay`. La confusion vient souvent de la super-loop, où un seul `delay` bloque tout.

---

## Scénario 2 : Faut-il un RTOS pour un blink LED ?

### Analyse

- **Le problème** : Pour un programme **très simple** (blink + bouton), une **super-loop** suffit largement : une boucle avec `delay_ms(500)`, toggle LED, et lecture du bouton (ou interruption sur le bouton + flag). Aucune **échéance multiple** ni **tâches concurrentes** complexes.
- **La conséquence** : Introduire un RTOS ajoute de la **complexité** (création de tâches, configuration du noyau, stack pour chaque tâche), de la **consommation RAM** et un **coût de maintenance** (ordonnancement, risques d'inversion de priorité, etc.) sans gain réel pour ce cas.
- **Le risque** : « On est prêts pour la suite » peut justifier un RTOS si la **suite** est déjà définie (ex. ajout de communication, d’acquisition, d’affichage). Sinon, c’est de la **sur-ingénierie** : le code sera plus difficile à déboguer pour un débutant et plus lourd pour le MCU.

### La solution

- **Recommandation** : Pour un **blink + bouton** seul, rester en **super-loop** : plus simple, moins de ressources, plus lisible. Passer à un RTOS quand on a **vraiment** besoin de plusieurs activités indépendantes (ex. tâche communication + tâche acquisition + tâche commande) ou de garanties temporelles multiples.
- Si le cahier des charges prévoit **d’évoluer** rapidement (ajout de protocoles, écran, etc.), on peut **dès le début** choisir un RTOS pour éviter un refactoring complet plus tard — à condition d’en avoir les compétences et de dimensionner correctement les tâches et les stacks.

### Un autre piège : tout faire en super-loop quand la complexité monte

À l’inverse, garder une **seule** super-loop avec des dizaines de `if (temps_écoulé(...))` et des machines à états imbriquées rend le code **illisible** et **fragile**. Au-delà de 2–3 échéances indépendantes ou de traitements bloquants (attente UART, attente réseau), un RTOS devient souvent le bon choix pour la **clarté** et la **maintenabilité**.

---

**Retour** : [Scénarios – Boucle vs RTOS](../scenarios/boucle-vs-rtos.md) · [Leçon 4](../04-boucle-vs-rtos.md)
