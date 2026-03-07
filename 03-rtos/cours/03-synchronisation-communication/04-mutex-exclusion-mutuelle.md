# Leçon 4 – Mutex : exclusion mutuelle

## Objectif de la leçon

Utiliser un **mutex** FreeRTOS pour **protéger une ressource partagée** (variable globale, UART, SPI) : Take avant accès, Give après. Comprendre la nécessité de **toujours** libérer le mutex (y compris en cas d'erreur) et de garder les **sections critiques courtes**.

---

## 1. Création du mutex

```c
SemaphoreHandle_t xSemaphoreCreateMutex(void);
```

Retourne un handle. Le mutex est créé **libre** (aucune tâche ne le détient). Une seule tâche peut le **détenir** à la fois (Take réussi) ; les autres tâches qui font Take **bloquent** jusqu'à ce que la tâche détentrice fasse **Give**.

---

## 2. Take et Give

- **xSemaphoreTake(mutex, timeout)** : prendre le mutex. Si une autre tâche le détient, **bloquer** jusqu'à ce qu'elle le libère (ou jusqu'à **timeout**). Une fois Take réussi, la tâche **détient** le mutex.
- **xSemaphoreGive(mutex)** : libérer le mutex. Doit être appelé par la **même** tâche qui a fait le Take (sinon comportement non garanti).

Pattern typique :

```c
void utiliser_uart(void) {
    if (xSemaphoreTake(mutex_uart, pdMS_TO_TICKS(100)) == pdTRUE) {
        /* section critique : accès exclusif à l'UART */
        envoyer_trame_uart(...);
        xSemaphoreGive(mutex_uart);   /* toujours libérer */
    } else {
        /* timeout : échec */
    }
}
```

---

## 3. Toujours libérer le mutex

Si la tâche fait **Take** puis **return** (ou sort par une erreur) **sans** faire **Give**, le mutex reste **détenu** pour toujours. Les autres tâches qui font Take resteront **bloquées** (deadlock). Il faut donc :
- Soit une **structure** claire : Take → traitement → Give, sans return au milieu.
- Soit en cas d'erreur : faire **Give** avant de return, ou utiliser un **timeout** au Take pour ne pas bloquer indéfiniment si le mutex n'est jamais libéré (par une autre tâche en bug).

---

## 4. Sections critiques courtes

Tant qu'une tâche **détient** le mutex, les autres tâches qui en ont besoin sont **bloquées**. Pour limiter la **latence** des tâches prioritaires, la **section critique** (entre Take et Give) doit être **courte** : uniquement l'accès à la ressource partagée, pas de calcul lourd ni d'attente (delay) à l'intérieur.

---

## 5. Mutex et ISR

En général, on **ne prend pas** un mutex dans une **ISR** (Take peut bloquer, et les ISR ne doivent pas bloquer). Si une ISR doit accéder à une ressource partagée avec des tâches, on peut utiliser une **queue** (l'ISR envoie une demande, une tâche dédiée fait Take(mutex), traite, Give(mutex)) ou un **section critique** courte (désactivation d'interruptions) selon le cas. Les mutex sont surtout pour la **synchronisation entre tâches**.

---

## Points clés à retenir

- **Mutex** = Take (avant accès) + **Give** (après accès) ; une seule tâche détentrice à la fois.
- **Toujours** faire Give après Take (y compris en cas d'erreur) pour éviter le deadlock.
- Garder la **section critique** **courte** ; ne pas prendre de mutex dans une ISR (pas de Take bloquant).

---

## Tester sa compréhension

→ [Scénario – Mutex](scenarios/04-mutex.md) · [Réponse](reponses/04-mutex.md)

---

**Suite** : [Leçon 5 – Bonnes pratiques et synthèse](05-bonnes-pratiques-synthese.md)
