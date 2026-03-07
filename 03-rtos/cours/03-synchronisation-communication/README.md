# Synchronisation et communication – Vue d'ensemble

Ce sous-dossier contient le cours **Synchronisation et communication** : files d'attente (queues), sémaphores binaires et à compteur, mutex, et bonnes pratiques (ISR, timeouts, sections critiques).

---

## Objectifs pédagogiques

À l'issue de ce cours, l'étudiant sera capable de :

- **Créer** et utiliser des **queues** (xQueueCreate, xQueueSend, xQueueReceive, versions FromISR).
- Utiliser un **sémaphore binaire** pour réveiller une tâche depuis une ISR.
- Utiliser un **sémaphore à compteur** pour gérer un nombre de ressources.
- Protéger une **ressource partagée** avec un **mutex** (Take/Give).
- Appliquer les **bonnes pratiques** : ISR FromISR uniquement, timeouts, dimensionnement des queues.

---

## Ordre de lecture recommandé

| N° | Leçon | Contenu |
|----|--------|---------|
| 1 | [Queues : création, envoi et réception](01-queues-creation-envoi-reception.md) | xQueueCreate, Send, Receive, timeout |
| 2 | [Queues depuis une ISR (FromISR)](02-queues-depuis-isr.md) | SendFromISR, portYIELD_FROM_ISR |
| 3 | [Sémaphores binaires et à compteur](03-semaphores-binaires-compteur.md) | Give/Take, réveil depuis ISR, compteur |
| 4 | [Mutex : exclusion mutuelle](04-mutex-exclusion-mutuelle.md) | Take/Give, ressource partagée, libération |
| 5 | [Bonnes pratiques et synthèse](05-bonnes-pratiques-synthese.md) | ISR, timeouts, sections courtes, dimensionnement |

---

## Public et prérequis

- **Public** : débutants (étudiants, autodidactes).
- **Prérequis** : cours **01 – Concepts RTOS** et **02 – Tâches et ordonnancement** (états, blocage).

---

**Tester sa compréhension** : [Scénarios](scenarios/README.md) et [Réponses](reponses/README.md).

---

**Commencer par** : [01 – Queues : création, envoi et réception](01-queues-creation-envoi-reception.md)
