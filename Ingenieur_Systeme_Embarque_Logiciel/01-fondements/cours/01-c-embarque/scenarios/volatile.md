# Scénarios – Le qualificateur volatile

Situations pour vérifier votre compréhension de la [Leçon 3 – Le qualificateur volatile](../03-volatile.md).

---

## Scénario 1 : Flag modifié par l'ISR

Le programme principal attend qu'un **flag** soit mis à 1 par l'**ISR** d'un bouton, puis traite l'appui :

```c
uint8_t bouton_appuye = 0;   /* pas de volatile */

void main_loop(void) {
    while (1) {
        if (bouton_appuye) {
            traiter_appui();
            bouton_appuye = 0;
        }
    }
}
```

En **debug** (sans optimisations), tout fonctionne. En **release** (optimisations activées), le programme ne réagit plus au bouton.

**Questions** : Quelle est la cause probable ? Quelle correction minimale apporter ?

---

## Scénario 2 : Attente sur un registre de statut

On attend que le bit 0 d'un registre matériel à l'adresse `0x40021018` passe à 1 (signal de fin d'opération du périphérique) :

```c
uint32_t *p = (uint32_t *)0x40021018;
while ((*p & 1) == 0)
    ;
```

Le compilateur peut « optimiser » cette boucle. Que risque-t-il de faire et avec quelle conséquence ? Quelle correction ?

---

*Après avoir réfléchi, consultez les* [**Éléments de réponse – volatile**](../reponses/volatile.md).

---

**Retour** : [Leçon 3 – volatile](../03-volatile.md) · [Vue d'ensemble du cours C](../README.md)
