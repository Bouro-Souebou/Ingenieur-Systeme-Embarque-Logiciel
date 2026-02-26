# Leçon 1 – Qu'est-ce que le temps réel ?

## Objectif de la leçon

Comprendre ce que signifie **temps réel** en informatique embarquée : ce n'est pas « aller vite », mais **répondre dans un délai garanti**. Savoir distinguer **temps réel dur** et **temps réel mou**.

---

## 1. Définition du temps réel

Un système est dit **temps réel** lorsque la **correctitude** du résultat dépend aussi du **moment** où il est produit. Une réponse **trop tardive** est considérée comme une **erreur**, même si le calcul en lui-même est correct.

**Exemples** :

- **Freinage** : la commande de frein doit être envoyée dans les quelques millisecondes qui suivent la détection d'obstacle. Trop tard = accident.
- **Contrôle moteur** : la boucle de régulation doit s'exécuter à une période fixe (ex. 1 ms). Un retard dégrade la stabilité voire endommage le système.
- **Acquisition** : les échantillons doivent être lus à intervalles réguliers ; un retard ou une perte d'échantillon fausse les mesures.

À l'inverse, sur un **PC classique** (traitement de texte, navigation web), une réponse un peu plus lente est souvent acceptable : on parle de **temps partagé** ou **interactif**, pas de temps réel strict.

---

## 2. Temps réel « dur » vs « mou »

### Temps réel dur (hard real-time)

Le **dépassement** du délai imparti peut avoir des **conséquences critiques** : perte de vie, blessure, dégât matériel, perte de données irremplaçables. Les systèmes de **sécurité** (freinage, pilote automatique, médical) ou de **contrôle critique** (avionique, industrie) entrent dans cette catégorie.

- **Exigence** : il faut **prouver** (ou au moins borner) que le pire temps de réponse (WCET, Worst-Case Execution Time) ne dépasse jamais le délai autorisé.
- **Méthodes** : analyse statique, mesures, conception déterministe (pas de heap dynamique, pas de boucles non bornées dans les parties critiques).

### Temps réel mou (soft real-time)

Les **dépassements** dégradent la **qualité de service** mais ne sont pas catastrophiques. Exemples : lecture vidéo (saccades si retard), affichage (latence), réseau (paquets en retard).

- On cherche à **minimiser** les retards et à les garder **rares**, mais une dépassement occasionnel est acceptable.
- Beaucoup d'applications embarquées (objets connectés, interfaces utilisateur, dataloggers) sont en temps réel **mou**.

---

## 3. Ce que le temps réel n'est pas

- **Temps réel ≠ « très rapide »** : un système peut être très rapide (ex. serveur) mais ne pas garantir de délai ; à l'inverse, un système temps réel peut réagir en 100 ms si c'est le délai requis.
- **Temps réel ≠ « en direct »** : « en direct » signifie souvent « pas de décalage volontaire » (streaming), pas « réponse dans un délai garanti ».

---

## 4. Pourquoi c'est important en embarqué

Les systèmes embarqués pilotent souvent des **actionneurs** (moteurs, vannes, relais) et lisent des **capteurs** dans un environnement physique. Le **monde réel** ne attend pas : un capteur envoie une donnée à un instant donné, un moteur doit être commandé à une certaine fréquence. Le logiciel doit donc être conçu pour **respecter des échéances** (délais, périodes), ce qui implique une attention particulière à l'**ordonnancement**, aux **interruptions** et à l'**utilisation de la mémoire** (pas d'allocation imprévisible, stack dimensionnée).

---

## Points clés à retenir

- **Temps réel** = la correctitude dépend du **moment** où la réponse est produite ; une réponse trop tardive = faute.
- **Temps réel dur** : dépassement = conséquence critique (sécurité, intégrité).
- **Temps réel mou** : dépassement = dégradation de la qualité, acceptable occasionnellement.

---

## Tester sa compréhension

→ [**Scénarios – Définition temps réel**](scenarios/definition-temps-reel.md) · → [**Éléments de réponse**](reponses/definition-temps-reel.md)

---

**Suite** : [Leçon 2 – Latence, jitter et déterminisme](02-latence-jitter-determinisme.md)
