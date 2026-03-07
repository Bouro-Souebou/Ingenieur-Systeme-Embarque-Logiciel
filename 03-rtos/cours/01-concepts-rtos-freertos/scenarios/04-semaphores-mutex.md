# Scénario – Sémaphores et mutex : vue d'ensemble

Pour la leçon [04 – Sémaphores et mutex](../04-semaphores-mutex-vue-ensemble.md).

---

## Scénario 1 : Bus SPI et bouton

Deux tâches doivent accéder à un **bus SPI** partagé (une seule à la fois). Une ISR doit **réveiller** une tâche quand un bouton est appuyé (sans passer de donnée).

**Questions** : Quelle primitive pour le bus SPI (queue, sémaphore, mutex) ? Quelle primitive pour le bouton (queue, sémaphore binaire, mutex) ? Justifier brièvement.

---

## Scénario 2 : Ressource critique vs simple signal

On a : (A) deux tâches qui écrivent dans un **buffer partagé** ; (B) une ISR qui doit **signaler** qu'un échantillon ADC est prêt.

**Questions** : Pour (A), mutex ou sémaphore binaire ? Pour (B), queue (avec la valeur) ou sémaphore ? Pourquoi ?

---

**Réponse** : [../reponses/04-semaphores-mutex.md](../reponses/04-semaphores-mutex.md) · **Retour** : [Vue d'ensemble](../README.md)
