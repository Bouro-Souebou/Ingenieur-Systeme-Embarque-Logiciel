# Leçon 1 – Principes du DMA

## Objectif de la leçon

Comprendre le **DMA** (Direct Memory Access) : à quoi il sert, comment on configure un transfert (source, destination, déclencheur), et **quand** l'utiliser plutôt que le polling ou les interruptions.

---

## 1. Définition et rôle

Le **DMA** est un **bloc matériel** du microcontrôleur qui effectue des **transferts de données** entre la **RAM** et un **périphérique** (registre UART, ADC, etc.) **sans que le CPU exécute d'instructions** pour chaque octet ou mot transféré.

- **Sans DMA** : le CPU lit ou écrit chaque donnée (polling ou dans une ISR). À haut débit ou avec plusieurs canaux, la charge CPU devient importante et le risque de **manquer** des données (jitter, latence) augmente.
- **Avec DMA** : le CPU **configure** une fois le transfert (adresses, nombre d'éléments, déclencheur) ; le DMA effectue ensuite les copies **en arrière-plan**. Le CPU peut faire autre chose ; une **interruption** en fin (ou à mi-parcours) signale que les données sont prêtes.

En résumé : **DMA = transfert mémoire ↔ périphérique sans CPU**, pour **réduire la charge CPU** et **garantir** des transferts réguliers à fort débit.

---

## 2. Paramètres d'un transfert DMA

Pour lancer un transfert, on configure typiquement :

| Paramètre | Rôle |
|-----------|------|
| **Source** | Adresse de départ (RAM ou registre périphérique). |
| **Destination** | Adresse d'arrivée (registre périphérique ou RAM). |
| **Nombre d'éléments** | Combien d'unités transférer (octets, mots 16/32 bits selon le périphérique). |
| **Incrément** | Après chaque transfert, la source et/ou la destination peut **s'incrémenter** automatiquement (ex. remplir un buffer en RAM) ou rester **fixe** (ex. toujours le même registre DR). |
| **Déclencheur** | **Quand** le DMA effectue un transfert : à chaque requête du **périphérique** (ex. octet reçu sur l'UART, conversion ADC terminée) ou sur **événement** (timer, etc.). |

Le **sens** du transfert dépend du périphérique : **RAM → périphérique** (ex. envoi UART) ou **périphérique → RAM** (ex. réception UART, résultats ADC).

---

## 3. Interruptions : fin de transfert et demi-transfert

- **Fin de transfert** : quand le nombre d'éléments prévu a été transféré, le DMA peut générer une **interruption**. Le logiciel sait alors que le buffer est **complet** et peut traiter les données (ou préparer le prochain transfert).
- **Demi-transfert** (half-transfer) : sur certains MCU, une interruption est générée à **mi-parcours** (ex. après la moitié du buffer). C’est la base du **double buffering** : pendant que le DMA remplit la seconde moitié, le logiciel **traite** la première — sans perte de donnée ni attente.

Ces interruptions doivent être **courtes** (voir [Interruptions et réactivité](../../../01-fondements/cours/03-temps-reel/03-interruptions-reactivite.md)) : poser un flag, envoyer dans une queue, etc., et traiter les données dans une tâche ou la boucle principale.

---

## 4. Quand utiliser le DMA ?

| Situation | Recommandation |
|-----------|----------------|
| **Gros volumes** ou **débit soutenu** (flux UART rapide, ADC multi-canaux à haute fréquence) | **DMA** pour éviter de surcharger le CPU et de manquer des données. |
| **Échanges légers** (quelques octets, commandes ponctuelles) | **Polling** ou **interruption** suffisent ; le DMA ajoute de la complexité sans gain majeur. |
| **Temps réel strict** (échantillonnage ADC périodique) | **DMA + timer** pour des acquisitions **périodiques** sans jitter lié au logiciel. |

En pratique : commencer par polling ou IT ; passer au DMA quand le débit ou le nombre de canaux le justifie.

---

## 5. Rappel : volatile et DMA

Les **zones mémoire** modifiées par le DMA (buffers en RAM) sont lues ou écrites par le **matériel** sans que le compilateur le voie. Il faut donc les déclarer **volatile** (ou accéder via des pointeurs `volatile`) pour que le compilateur ne supprime pas les lectures. Voir [Le qualificateur volatile](../../../01-fondements/cours/01-c-embarque/03-volatile.md).

---

## Points clés à retenir

- **DMA** = transfert **mémoire ↔ périphérique** sans CPU ; on configure source, destination, nombre, déclencheur.
- **Déclencheur** = événement périphérique (octet reçu, conversion terminée, etc.) ; **interruption** en fin (ou demi-) de transfert pour traiter les données.
- Utiliser le DMA pour **gros débits** ou **échantillonnage régulier** ; pour de petits échanges, polling ou IT suffisent.

---

**Suite** : appliquer ces principes dans [DMA avec UART](../01-uart/04-dma-uart.md) ou [DMA avec ADC](../04-adc-dma/04-dma-adc.md).
