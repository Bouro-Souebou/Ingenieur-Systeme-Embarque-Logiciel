# Scénarios – Qu'est-ce que le temps réel ?

Situations pour vérifier votre compréhension de la [Leçon 1 – Définition du temps réel](../01-definition-temps-reel.md).

---

## Scénario 1 : « Temps réel » dans le cahier des charges

Votre chef de projet demande une application **« temps réel »** qui affiche les données d'un capteur sur un écran, avec une **mise à jour toutes les secondes**. Il précise : « Il faut que ce soit temps réel pour que l'opérateur voie les changements. »

**Questions** :
1. Ce besoin correspond-il au sens **technique** du temps réel (comme dans le cours) ?
2. Comment qualifieriez-vous ce type d'exigence (dur / mou / autre) ?
3. Quelle confusion courante votre chef pourrait-il faire ?

---

## Scénario 2 : Freinage vs lecture vidéo

On compare deux systèmes :
- **A** : Système de freinage antiblocage (ABS) : la commande doit être envoyée dans les **quelques millisecondes** après la détection de glissement.
- **B** : Lecteur vidéo sur un set-top box : les images doivent être affichées à **25 images par seconde** ; un retard occasionnel provoque une saccade.

**Question** : Lequel est **temps réel dur**, lequel est **temps réel mou** ? Justifiez en une phrase pour chacun.

---

*Après avoir réfléchi, consultez les* [**Éléments de réponse – Définition temps réel**](../reponses/definition-temps-reel.md).

---

**Retour** : [Leçon 1 – Qu'est-ce que le temps réel ?](../01-definition-temps-reel.md) · [Vue d'ensemble](../README.md)
