# Leçon 1 – Pourquoi un RTOS ?

## Objectif de la leçon

Comprendre les **limites** d'une boucle principale (super-loop) quand plusieurs activités doivent respecter des **échéances** différentes, et en quoi un **RTOS** apporte des réponses (tâches, ordonnancement, primitives de synchronisation).

---

## 1. Rappel : la super-loop

Dans une **super-loop**, il n'y a qu'**un seul** fil d'exécution. Le programme enchaîne des traitements et des **delays** (attentes actives ou basées sur un timer) :

```c
void main(void) {
    init_hardware();
    for (;;) {
        lire_capteur();
        delay_ms(10);
        envoyer_message();
        delay_ms(100);
        if (bouton_appuye) traiter_bouton();
    }
}
```

Chaque traitement **bloque** tout le reste pendant sa durée. Si `lire_capteur()` ou `envoyer_message()` prend du temps, les autres activités sont retardées. Garantir **plusieurs échéances indépendantes** (ex. : capteur toutes les 10 ms, message toutes les 100 ms, bouton réagi en moins de 50 ms) devient difficile et le code devient vite un enchevêtrement de flags et de machines à états.

---

## 2. Besoins typiques en embarqué

- **Plusieurs activités** en parallèle logique : acquisition, commande, communication, affichage.
- **Échéances** différentes : une activité toutes les 1 ms, une autre toutes les 100 ms, une autre à la demande (événement).
- **Réactivité** : réagir à un événement (bouton, caractère reçu) sans attendre la fin d'un long traitement.
- **Séparation des préoccupations** : un bloc de code par fonction métier, plutôt qu'une seule boucle qui tout fait.

Une super-loop peut répondre à ces besoins en découpant tout en **petits pas** et en utilisant des **états** et des **timers**, mais le code devient complexe et fragile. Un **RTOS** structure tout cela avec des **tâches** et des **primitives** dédiées.

---

## 3. Ce qu'apporte un RTOS

Un **RTOS** (Real-Time Operating System) fournit :

- **Plusieurs tâches** (threads) : chacune est une fonction qui s'exécute « en parallèle » avec les autres. En réalité une seule tâche s'exécute à la fois sur un cœur, mais l'**ordonnanceur** alterne entre elles selon les **priorités** et les **événements** (délai écoulé, message reçu, etc.).
- Un **ordonnancement préemptif** : si une tâche de priorité plus élevée devient prête, elle **prend** le CPU à la tâche en cours (préemption). On peut ainsi garantir qu'une tâche critique s'exécute dans un délai borné.
- Des **primitives de synchronisation** : files d'attente (messages), sémaphores (signal ou compteur), mutex (exclusion mutuelle). Les tâches peuvent **bloquer** en attendant un message ou un signal, sans consommer de CPU.
- Une **notion de temps** : tick périodique, `vTaskDelay`, timers logiciels. Les tâches peuvent attendre un délai ou une période.

On obtient une **séparation claire** des activités (une tâche par rôle) et une **meilleure maîtrise** des délais (temps réel mou ou dur selon la conception).

---

## 4. Quand utiliser un RTOS ?

- **Plusieurs activités** avec des **périodes ou échéances** différentes.
- Besoin de **réactivité** (une tâche prioritaire réveillée par un événement).
- Projet qui va **grandir** : ajouter une tâche est plus simple qu'imbriquer des machines à états dans une boucle.

Pour un **très petit** système (une LED, un seul capteur, pas de contrainte temps réel), une super-loop peut suffire. Dès que plusieurs « rythmes » ou événements coexistent, un RTOS comme **FreeRTOS** est un choix courant et bien documenté.

---

## Points clés à retenir

- **Super-loop** : un seul fil d'exécution ; difficile de garantir plusieurs échéances indépendantes.
- **RTOS** : tâches, ordonnancement préemptif, primitives de synchronisation et notion de temps.
- Utiliser un RTOS quand il y a **plusieurs activités** ou besoin de **réactivité** et de **structure** claire.

---

## Tester sa compréhension

→ [Scénario – Pourquoi un RTOS ?](scenarios/01-pourquoi-rtos.md) · [Réponse](reponses/01-pourquoi-rtos.md)

---

**Suite** : [Leçon 2 – Tâches : unité d'exécution](02-taches-unite-execution.md)
