# Éléments de réponse – Définition du temps réel

Réponses pour les [scénarios Définition temps réel](../scenarios/definition-temps-reel.md).

---

## Scénario 1 : « Temps réel » dans le cahier des charges

### Analyse (ce qu'il faut comprendre)

- **Le problème** : Le terme « temps réel » est souvent utilisé dans le langage courant pour dire « en direct » ou « rapide », alors qu'en **systèmes embarqués** il signifie : la **correctitude du résultat dépend du moment** où il est produit ; une réponse **trop tardive = erreur**.
- **La conséquence** : Une mise à jour « toutes les secondes » peut être **acceptable** pour un affichage opérateur (temps réel **mou** : un retard occasionnel dégrade la qualité mais n'est pas catastrophique). En revanche, on ne peut pas en déduire que « tout système qui affiche des données = temps réel » sans préciser l'**échéance** et la **criticité** du dépassement.
- **Le risque** : Confondre **temps réel** avec « très rapide » ou « en direct » conduit à sous-estimer les contraintes quand le système deviendra vraiment critique (sécurité, contrôle).

### La solution

- **Clarifier** avec le chef de projet : quelle est l'**échéance** (délai max acceptable) et que se passe-t-il si on la **dépasse** (critique = dur, dégradation = mou) ?
- **Qualifier** l'exigence : ici, affichage ~1 s → plutôt **temps réel mou** (un retard de 2 s est gênant mais pas catastrophique).
- **Documenter** : dans le cahier des charges, parler d'« **mise à jour périodique** (période cible 1 s) » et de « **temps réel mou** » si les dépassements occasionnels sont acceptés.

### Un autre piège : « Temps réel = très rapide »

- **Mauvaise idée** : Croire qu'un système temps réel doit toujours réagir en microsecondes. Un système peut être **temps réel** avec une échéance de **100 ms** ou **1 s** si c'est ce que l'application exige (ex. surveillance, datalogging).
- **Bonne idée** : Le temps réel, c'est **respecter une échéance garantie**, pas « aller le plus vite possible ». La vitesse requise dépend du **domaine** (contrôle moteur = ms, affichage = dizaines de ms à s).

---

## Scénario 2 : Freinage vs lecture vidéo

### Analyse

- **A – ABS (freinage)** : **Temps réel DUR**. Un dépassement du délai peut avoir des **conséquences critiques** (accident, intégrité physique). Il faut **prouver ou borner** le pire temps de réponse (WCET).
- **B – Lecture vidéo** : **Temps réel MOU**. Un retard occasionnel dégrade la **qualité** (saccade) mais n'est pas catastrophique. On cherche à minimiser les retards et à les garder rares.

### La solution

Distinguer toujours **dur** (dépassement = faute grave, sécurité/intégrité) et **mou** (dépassement = dégradation de service, acceptable de façon occasionnelle).

### Un autre piège

Ne pas confondre **fréquence** (25 Hz) avec **dur/mou** : une application peut exiger 1 kHz en temps réel **mou** (ex. acquisition de courbe) ou 10 Hz en temps réel **dur** (ex. commande de sécurité).

---

**Retour** : [Scénarios – Définition temps réel](../scenarios/definition-temps-reel.md) · [Leçon 1](../01-definition-temps-reel.md)
