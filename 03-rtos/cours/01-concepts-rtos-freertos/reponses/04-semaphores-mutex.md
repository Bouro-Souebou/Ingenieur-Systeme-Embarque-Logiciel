# Réponse – Sémaphores et mutex

Voir [scénario](../scenarios/04-semaphores-mutex.md).

---

## Réponse Scénario 1 : Bus SPI et bouton

**Bus SPI** : **Mutex** – une seule tâche à la fois doit accéder au bus (exclusion mutuelle). Take avant transfert, Give après.

**Bouton (réveiller une tâche, sans donnée)** : **Sémaphore binaire** – l'ISR fait Give, la tâche fait Take (bloquant). Pas de queue car on ne transmet pas d'octet, juste un signal « bouton appuyé ».

Résumé : **mutex** = protéger une ressource partagée ; **sémaphore binaire** = réveil par événement sans donnée.

---

## Réponse Scénario 2 : Ressource critique vs simple signal

**(A) Buffer partagé** : **Mutex** – les deux tâches doivent s'exclure pour écrire dans le buffer (section critique). Le mutex assure qu'une seule écrit à la fois.

**(B) Échantillon ADC prêt** : **Sémaphore binaire** si on signale juste « prêt » et que la valeur est lue ailleurs (variable, DMA) ; **queue** si on veut passer la valeur de l'échantillon directement (éviter une variable partagée). Selon le besoin : signal seul → sémaphore ; signal + donnée → queue.

---

**Retour** : [Scénarios](../scenarios/README.md) · [Leçon 4](../04-semaphores-mutex-vue-ensemble.md)
