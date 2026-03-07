# Leçon 4 – Sémaphores et mutex : vue d'ensemble

## Objectif de la leçon

Distinguer **sémaphore** (signal ou compteur) et **mutex** (exclusion mutuelle) : à quoi ils servent et dans quels cas les utiliser. Les détails d'utilisation (API FreeRTOS) seront vus dans le cours **Synchronisation et communication**.

---

## 1. Sémaphore : signaler un événement

Un **sémaphore** permet de **signaler** qu'un événement s'est produit (ou qu'une ressource est disponible), **sans** transporter de donnée (contrairement à une queue). Une tâche (ou une ISR) fait **Give** (donner) ; une autre tâche fait **Take** (prendre). Si personne n'a encore fait Give, le Take **bloque** la tâche jusqu'à ce qu'un Give soit effectué (ou jusqu'à un timeout).

**Sémaphore binaire** : valeur 0 ou 1. Un Give met à 1 (ou incrémente si déjà 1, selon l'API) ; un Take remet à 0 (ou décrémente). Utilisation typique : **réveiller une tâche** depuis une ISR (bouton appuyé, donnée reçue). La tâche fait Take (bloquant) ; l'ISR fait Give → la tâche se réveille et fait le travail.

**Sémaphore à compteur** : valeur entière (ex. 0 à N). Représente un **nombre de ressources** ou d'**occurrences** (ex. N slots libres dans un buffer). Take = consommer une ressource (décrémenter), Give = en rendre une (incrémenter). Si le compteur est à 0, Take bloque.

---

## 2. Mutex : exclusion mutuelle

Un **mutex** (mutual exclusion) sert à **protéger une ressource partagée** : une seule tâche à la fois peut **détenir** le mutex. Une tâche fait **Take** avant d'accéder à la ressource (variable globale, UART, SPI) et **Give** après. Une autre tâche qui fait Take pendant que le mutex est détenu **bloque** jusqu'à ce que la première fasse Give.

Cela évite les **race conditions** : deux tâches qui modifient la même variable ou le même périphérique en même temps. Le mutex garantit un accès **exclusif** pendant la section critique (entre Take et Give).

**Différence avec un sémaphore binaire** : le mutex a souvent une notion d'**héritage de priorité** (pour limiter l'inversion de priorité) et est destiné à être pris et rendu par la **même** tâche. Un sémaphore binaire est souvent « donné » par une entité (ISR, tâche A) et « pris » par une autre (tâche B).

---

## 3. Résumé des usages

| Primitif | Usage typique |
|----------|----------------|
| **Queue** | Passer des **données** (octets, structures) entre tâches ou ISR ↔ tâche |
| **Sémaphore binaire** | **Signal** : réveiller une tâche depuis une ISR ou une autre tâche (sans donnée) |
| **Sémaphore à compteur** | **Nombre de ressources** (slots, tokens) ; Take = consommer, Give = rendre |
| **Mutex** | **Exclusion mutuelle** : protéger une ressource partagée (variable, périphérique) |

---

## Points clés à retenir

- **Sémaphore** = signal (Give/Take) ou compteur de ressources ; pas de payload.
- **Mutex** = une seule tâche à la fois peut détenir ; protéger une ressource partagée.
- **Queue** = passage de **messages** (données) ; sémaphore = **événement** sans donnée.

---

## Tester sa compréhension

→ [Scénario – Sémaphores et mutex](scenarios/04-semaphores-mutex.md) · [Réponse](reponses/04-semaphores-mutex.md)

---

**Suite** : [Leçon 5 – FreeRTOS en bref](05-freertos-en-bref.md)
