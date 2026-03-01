# Scénarios – Stack et heap (mémoire)

Situations pour vérifier votre compréhension de la [Leçon 6 – Const, static et mémoire (stack/heap)](../06-const-static-memoire.md).

---

## Scénario 1 : Gros buffer local sur la stack

Sur un MCU avec **4 Ko de stack**, une fonction déclare un **tableau local** de 2 Ko pour une trame de communication :

```c
void traiter_trame(void) {
    uint8_t trame[2048];
    /* remplir trame, puis l'envoyer */
}
```

Cette fonction est appelée depuis `main`, qui appelle aussi d'autres fonctions (UART, timers). Parfois le système **plante** (HardFault) lors de l'appel à `traiter_trame`, pas toujours.

**Questions** : Quelle est la cause probable ? Quelle(s) solution(s) proposeriez-vous ?

---

## Scénario 2 : malloc dans un système embarqué critique

Pour un **datalogger** qui doit enregistrer des mesures pendant **plusieurs jours** sans redémarrage, un développeur alloue dynamiquement un buffer avec `malloc(256)` à chaque nouvelle série de mesures, puis appelle `free()` à la fin du traitement.

**Questions** : Quels risques à long terme (fuites, fragmentation) ? Quelle alternative recommandée en embarqué critique ?

---

*Après avoir réfléchi, consultez les* [**Éléments de réponse – Stack et heap**](../reponses/stack-heap.md).

---

**Retour** : [Leçon 6 – Const, static et mémoire](../06-const-static-memoire.md) · [Vue d'ensemble du cours C](../README.md)
