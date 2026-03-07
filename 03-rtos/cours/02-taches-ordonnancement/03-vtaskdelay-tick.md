# Leçon 3 – vTaskDelay et tick

## Objectif de la leçon

Utiliser **vTaskDelay** pour attendre un **délai** en ticks et **rendre le CPU** aux autres tâches. Comprendre le **tick** et la macro **pdMS_TO_TICKS** pour exprimer des délais en millisecondes.

---

## 1. Le tick (horloge du noyau)

FreeRTOS utilise une **horloge** interne appelée **tick** : une interruption périodique (souvent **SysTick** sur Cortex-M) incrémente un compteur à intervalles réguliers. La **période** du tick est configurée dans **FreeRTOSConfig.h** par **configTICK_RATE_HZ** (ex. 1000 = 1000 ticks par seconde, soit 1 tick = 1 ms).

Ce tick sert à :
- **Réveiller** les tâches qui ont appelé **vTaskDelay** quand le délai est écoulé.
- Déclencher l'**ordonnanceur** (éventuel changement de tâche à chaque tick).
- Faire avancer les **timers** logiciels FreeRTOS (si activés).

---

## 2. vTaskDelay(ticks)

**vTaskDelay(ticks)** met la tâche en état **Blocked** pendant **ticks** ticks. La tâche ne consomme **pas** de CPU pendant ce temps ; l'ordonnanceur peut exécuter d'autres tâches. Après **ticks** ticks, la tâche repasse en **Ready** et pourra s'exécuter selon sa priorité.

```c
void ma_tache(void *pv) {
    for (;;) {
        faire_travail();
        vTaskDelay(100);   /* attendre 100 ticks (ex. 100 ms si 1 tick = 1 ms) */
    }
}
```

**Important** : le délai est **à partir du moment où vTaskDelay est appelé**. Si **configTICK_RATE_HZ = 1000**, alors 100 ticks = 100 ms. Pour exprimer facilement des millisecondes, on utilise la macro **pdMS_TO_TICKS(ms)**.

---

## 3. pdMS_TO_TICKS(ms)

**pdMS_TO_TICKS(ms)** convertit une durée en **millisecondes** en nombre de **ticks**, selon **configTICK_RATE_HZ**. Exemple : si le tick est à 1 kHz, `pdMS_TO_TICKS(10)` vaut 10. Ainsi on écrit :

```c
vTaskDelay(pdMS_TO_TICKS(10));   /* attendre 10 ms */
```

C'est plus lisible et portable si on change un jour la fréquence du tick. Attention : si **configTICK_RATE_HZ** est faible (ex. 100), la résolution est de 10 ms et `pdMS_TO_TICKS(5)` peut valoir 0 (arrondi).

---

## 4. Boucles périodiques et dérive

Pour une tâche **périodique** (ex. exécuter toutes les 10 ms), un pattern simple est :

```c
for (;;) {
    do_work();
    vTaskDelay(pdMS_TO_TICKS(10));
}
```

Le **temps entre deux débuts** d'exécution de `do_work()` est **10 ms + temps d'exécution de do_work()**. Si `do_work()` varie (1 ms un jour, 5 ms un autre), la **période** varie (dérive). Pour une période **stricte**, il faut utiliser un **timer** FreeRTOS ou un sémaphore donné par un timer à période fixe, et attendre ce sémaphore au début de la boucle (la tâche se réveille à intervalles fixes, puis fait le travail).

---

## Points clés à retenir

- **Tick** = horloge du noyau (configTICK_RATE_HZ) ; 1 tick = 1/configTICK_RATE_HZ secondes.
- **vTaskDelay(ticks)** : bloquer la tâche pendant **ticks** ticks, rendre le CPU aux autres.
- **pdMS_TO_TICKS(ms)** : convertir des ms en ticks pour des délais lisibles.
- Boucle « travail + delay » = période approximative (dérive si le travail varie).

---

## Tester sa compréhension

→ [Scénario – vTaskDelay et tick](scenarios/03-vtaskdelay-tick.md) · [Réponse](reponses/03-vtaskdelay-tick.md)

---

**Suite** : [Leçon 4 – Priorités et inversion de priorité](04-priorites-inversion.md)
