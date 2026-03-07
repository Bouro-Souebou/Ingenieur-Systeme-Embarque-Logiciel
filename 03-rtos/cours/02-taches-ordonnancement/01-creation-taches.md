# Leçon 1 – Création de tâches (xTaskCreate)

## Objectif de la leçon

Savoir **créer** une tâche FreeRTOS avec **xTaskCreate** : fonction d'entrée, nom, taille de stack, paramètre utilisateur, priorité et handle optionnel.

---

## 1. Signature de xTaskCreate

Sous FreeRTOS, une tâche est créée par :

```c
BaseType_t xTaskCreate(
    TaskFunction_t pvTaskCode,      /* fonction d'entrée */
    const char * const pcName,     /* nom (debug) */
    uint16_t usStackDepth,         /* taille stack en words (4 octets sur Cortex-M) */
    void *pvParameters,             /* paramètre passé à la tâche */
    UBaseType_t uxPriority,        /* priorité (0 = plus basse) */
    TaskHandle_t *pxCreatedTask    /* handle créé (optionnel, peut être NULL) */
);
```

La tâche est créée en état **Ready** : elle pourra s'exécuter dès que **vTaskStartScheduler()** sera appelé (ou immédiatement si l'ordonnanceur tourne déjà).

---

## 2. Fonction d'entrée (pvTaskCode)

La fonction doit avoir la signature :

```c
void ma_tache(void *pvParameters);
```

- **Pas de retour** : en pratique la fonction contient une **boucle infinie** (`for (;;) { ... }`). Si elle retourne, le comportement dépend du port (souvent la tâche est supprimée).
- **pvParameters** : pointeur passé à la création ; permet de donner un paramètre différent à chaque instance (ex. numéro de LED, pointeur vers une structure de config).

Exemple :

```c
void task_led(void *pvParameters) {
    int led_num = (int)(intptr_t)pvParameters;
    for (;;) {
        allumer(led_num);
        vTaskDelay(pdMS_TO_TICKS(500));
        eteindre(led_num);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
xTaskCreate(task_led, "LED", 128, (void *)1, 1, NULL);
```

---

## 3. Stack (usStackDepth)

**usStackDepth** est la taille de la **stack** de la tâche en **words** (sur ARM Cortex-M, 1 word = 4 octets). Donc 128 words = 512 octets. Il faut **dimensionner** selon :

- La **profondeur** des appels de fonctions (chaque appel consomme de la stack).
- Les **variables locales** (tableaux, structures).

Une stack trop petite provoque un **overflow** (écriture en dehors de la zone), souvent détectable avec `configCHECK_FOR_STACK_OVERFLOW` (hook appelé en cas de débordement). En développement, prévoir une **marge** (ex. 256 ou 512 words pour une tâche simple).

---

## 4. Priorité (uxPriority)

**uxPriority** : 0 = priorité la plus **basse**, **configMAX_PRIORITIES - 1** = priorité la plus **haute** (configMAX_PRIORITIES est défini dans FreeRTOSConfig.h, ex. 8 ou 16). L'ordonnanceur donne le CPU à la tâche **Ready** de priorité la plus **élevée**. À priorité égale, les tâches se partagent le CPU (tourniquet à chaque tick).

---

## 5. Handle (pxCreatedTask)

Si tu passes un pointeur vers un **TaskHandle_t**, FreeRTOS y écrit le **handle** de la tâche créée. Ce handle sert ensuite à : suspendre/reprendre la tâche (`vTaskSuspend`, `vTaskResume`), modifier sa priorité, ou la supprimer. Si tu n'en as pas besoin, passer **NULL**.

---

## Points clés à retenir

- **xTaskCreate** : fonction d'entrée, nom, **stack en words**, paramètre, **priorité**, handle optionnel.
- La tâche est en état **Ready** après création ; elle s'exécute quand l'ordonnanceur démarre (ou quand elle est la plus prioritaire parmi les prêtes).
- **Stack** : dimensionner suffisamment pour éviter l'overflow (marge en développement).

---

## Tester sa compréhension

→ [Scénario – Création de tâches](scenarios/01-creation-taches.md) · [Réponse](reponses/01-creation-taches.md)

---

**Suite** : [Leçon 2 – États et ordonnancement préemptif](02-etats-ordonnancement.md)
