# Leçon 2 – Tâches : unité d'exécution

## Objectif de la leçon

Comprendre ce qu'est une **tâche** dans un RTOS : une fonction avec sa propre **stack**, une **priorité**, et un **point d'entrée** (boucle infinie ou fonction qui se termine). Introduction à la création de tâches avec FreeRTOS.

---

## 1. Définition d'une tâche

Une **tâche** (task) est l'unité d'exécution gérée par l'ordonnanceur. Chaque tâche :

- A un **point d'entrée** : une fonction C de la forme `void ma_fonction(void *pvParameters)`. Cette fonction est en général une **boucle infinie** qui fait un travail, puis attend (délai, message, sémaphore). Si la fonction retourne, la tâche est détruite (selon le RTOS).
- Dispose de sa **propre stack** : les variables locales et les appels de fonction de cette tâche utilisent une zone mémoire dédiée, dimensionnée à la création (en mots, ex. 128 ou 256 words sur Cortex-M).
- A une **priorité** (nombre). Sous FreeRTOS : **plus le nombre est élevé, plus la tâche est prioritaire** (0 = priorité la plus basse).

À tout instant, **une seule** tâche s'exécute sur un cœur (multitâche **coopératif** ou **préemptif**). L'ordonnanceur choisit quelle tâche **prête** (Ready) a la priorité la plus élevée et lui donne le CPU.

---

## 2. Exemple minimal

```c
#include "FreeRTOS.h"
#include "task.h"

void ma_tache(void *pvParameters) {
    for (;;) {
        /* travail périodique */
        faire_travail();
        vTaskDelay(pdMS_TO_TICKS(100));   /* attendre 100 ms, rendre le CPU */
    }
}

void main(void) {
    init_hardware();
    xTaskCreate(ma_tache, "MaTache", 128, NULL, 1, NULL);
    vTaskStartScheduler();   /* ne revient jamais en temps normal */
    for (;;) ;   /* ne doit pas être atteint */
}
```

- **xTaskCreate** : crée la tâche (nom "MaTache", stack 128 words, pas de paramètre, priorité 1).
- **vTaskStartScheduler()** : démarre l'ordonnanceur ; le CPU passe alors aux tâches prêtes. En général on ne revient jamais de cette fonction (sauf erreur ou arrêt du noyau).
- **vTaskDelay** : met la tâche en état **Blocked** pendant la durée indiquée (en ticks). Pendant ce temps, d'autres tâches peuvent s'exécuter.

---

## 3. Priorité et stack

- **Priorité** : à égalité de priorité, les tâches prêtes partagent le CPU (tourniquet). Une tâche de priorité plus haute **préempte** une tâche de priorité plus basse dès qu'elle est prête.
- **Stack** : trop petite → **overflow** (comportement imprévisible, souvent HardFault). Il faut dimensionner selon les appels imbriqués et les variables locales. En développement, activer `configCHECK_FOR_STACK_OVERFLOW` et surveiller le « high water mark » si disponible.

Nous détaillerons la création (xTaskCreate), les états (Running, Ready, Blocked, Suspended) et vTaskDelay dans le cours **Tâches et ordonnancement**.

---

## Points clés à retenir

- Une **tâche** = une fonction (souvent boucle infinie) + une **stack** + une **priorité**.
- **xTaskCreate** crée la tâche ; **vTaskStartScheduler()** lance l'ordonnanceur.
- **vTaskDelay** : attendre un délai et **rendre le CPU** aux autres tâches.

---

**Suite** : [Leçon 3 – Files d'attente (queues)](03-files-attente.md)
