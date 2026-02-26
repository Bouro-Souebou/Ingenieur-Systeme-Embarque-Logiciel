# Leçon 3 – Sémaphores binaires et à compteur

## Objectif de la leçon

Créer et utiliser un **sémaphore binaire** (signal d'événement, réveil de tâche depuis une ISR) et un **sémaphore à compteur** (nombre de ressources). Savoir quand utiliser Give/Take et les versions FromISR.

---

## 1. Sémaphore binaire : création

```c
SemaphoreHandle_t xSemaphoreCreateBinary(void);
```

Retourne un handle. Le sémaphore binaire est créé **vide** (0) : un premier **Take** bloquera jusqu'à un **Give**. Typique : une **ISR** fait **Give** (signal « événement arrivé »), une **tâche** fait **Take** (bloquant) puis effectue le traitement.

---

## 2. Give et Take (côté tâche)

- **xSemaphoreGive(sem)** : « donner » le sémaphore (incrémente ; pour un binaire, passe à 1 si était à 0). Ne bloque pas.
- **xSemaphoreTake(sem, timeout)** : « prendre » le sémaphore (décrémente, ou bloque si valeur 0). **timeout** : attendre au plus ce délai (portMAX_DELAY = attendre indéfiniment).

Exemple (tâche qui attend un « bouton appuyé » signalé par une ISR) :

```c
void task_bouton(void *pv) {
    for (;;) {
        xSemaphoreTake(sem_bouton, portMAX_DELAY);   /* bloquer jusqu'à Give */
        traiter_appui_bouton();
    }
}
```

L'ISR du bouton fait **xSemaphoreGiveFromISR(sem_bouton, &wake)** puis **portYIELD_FROM_ISR(wake)**.

---

## 3. Depuis une ISR : GiveFromISR

```c
BaseType_t xSemaphoreGiveFromISR(SemaphoreHandle_t xSemaphore, BaseType_t *pxHigherPriorityTaskWoken);
```

Même logique que pour les queues : **GiveFromISR** ne bloque pas ; si une tâche était bloquée sur **Take**, *pxHigherPriorityTaskWoken peut être mis à pdTRUE → appeler **portYIELD_FROM_ISR(wake)** à la sortie de l'ISR.

**Ne jamais** faire **xSemaphoreTake** dans une ISR (Take peut bloquer).

---

## 4. Sémaphore à compteur

```c
SemaphoreHandle_t xSemaphoreCreateCounting(UBaseType_t uxMaxCount, UBaseType_t uxInitialCount);
```

- **uxMaxCount** : valeur **maximale** du compteur.
- **uxInitialCount** : valeur **initiale** (ex. nombre de « ressources » disponibles au démarrage).

**Take** décrémente (bloque si compteur = 0) ; **Give** incrémente (jusqu'à max). Utilisation typique : **pool de ressources** (ex. N slots dans un buffer) ; une tâche Take un slot, fait son travail, Give le slot. Ou **compteur d'événements** (plusieurs Give avant un Take pour « consommer » plusieurs occurrences).

---

## Points clés à retenir

- **Sémaphore binaire** : xSemaphoreCreateBinary ; **Give** = signaler, **Take** = attendre (bloquant).
- **ISR** : **xSemaphoreGiveFromISR** + **portYIELD_FROM_ISR** ; pas de Take en ISR.
- **Sémaphore à compteur** : xSemaphoreCreateCounting(max, initial) ; Take/Give pour gérer un **nombre** de ressources ou d'occurrences.

---

**Suite** : [Leçon 4 – Mutex : exclusion mutuelle](04-mutex-exclusion-mutuelle.md)
