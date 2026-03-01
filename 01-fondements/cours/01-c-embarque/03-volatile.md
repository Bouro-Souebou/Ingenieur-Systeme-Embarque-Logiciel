# Leçon 3 – Le qualificateur volatile

## Objectif de la leçon

Comprendre **pourquoi** le compilateur peut « casser » des accès à des données modifiées par le matériel ou les interruptions, et comment le mot-clé **volatile** corrige ce comportement.

---

## Concepts utilisés dans cette leçon

Cette leçon mentionne deux mécanismes courants en embarqué. Une courte définition suffit ici ; les détails (règles d’or, bonnes pratiques) sont vus dans d’autres cours.

| Terme | En une phrase | Pour aller plus loin |
|-------|----------------|----------------------|
| **ISR** (Interrupt Service Routine) | Fonction **appelée automatiquement par le processeur** lorsqu’un événement externe se produit (timer, touche, donnée reçue, etc.) ; elle peut **modifier des variables** que le programme principal lit ensuite. | Rôle des interruptions, **à faire / à ne jamais faire** dans une ISR, règle des ISR courtes : [Interruptions et réactivité](../03-temps-reel/03-interruptions-reactivite.md). |
| **DMA** (Direct Memory Access) | Mécanisme matériel qui **transfère des données** entre un périphérique (UART, ADC, etc.) et la **RAM sans passer par le CPU** ; des zones mémoire peuvent donc **changer sans qu’une instruction du programme les modifie**. | [Glossaire](../../../ressources/glossaire.md) ; **principes détaillés** : [Principes du DMA](../../../04-peripheriques/cours/00-dma-principes/01-principes-dma.md) (module Périphériques). |

*En résumé* : dès qu’une donnée peut être modifiée par une **ISR** ou par le **DMA**, le compilateur ne doit pas supposer qu’elle reste constante — d’où l’usage de **volatile** dans ces situations.

---

## 1. Ce que fait le compilateur : les optimisations

Le compilateur a pour objectif de produire un code **rapide** et **compact**. Pour cela, il **transforme** ton code de façon légale selon la norme C, par exemple :

- **Ne pas relire** une variable en mémoire si elle n'a pas été modifiée dans le code visible (il peut garder la valeur dans un registre du processeur).
- **Supprimer** des lectures ou des écritures qu'il juge inutiles (ex. boucle d'attente qu'il considère comme ne changeant rien).
- **Réordonner** certaines opérations pour aller plus vite.

Sur un **PC**, une variable en mémoire n'est en général modifiée que par **ton programme**. Sur un **système embarqué**, une variable peut aussi être modifiée par :

- une **interruption** (ISR) ;
- un **périphérique** (DMA, registre de statut) ;
- un **autre cœur** (multicore).

Le compilateur **ne voit pas** ces modifications. Il peut donc optimiser en supposant que la variable ne change pas, et ton programme se comporte mal (boucle infinie, valeur obsolète).

---

## 2. Exemple concret : attente sur un registre

Imaginons un registre de **statut** à l'adresse `0x40021018`. Le bit 0 passe à 1 quand un périphérique a terminé une opération. Le programme doit **attendre** que ce bit soit à 1 :

```c
uint32_t *p_statut = (uint32_t *)0x40021018;

while ((*p_statut & 1) == 0) {
    /* attendre que le bit 0 soit à 1 */
}
```

**Sans** `volatile` : le compilateur peut raisonner ainsi : « La variable pointée par `p_statut` n'est jamais modifiée dans ce fichier, donc `*p_statut` est constant. La condition `(*p_statut & 1) == 0` est soit toujours vraie, soit toujours fausse. » Il peut alors **remplacer la boucle** par une boucle infinie ou la supprimer. En pratique, le bit change **à cause du matériel**, mais le compilateur ne le sait pas.

**Avec** `volatile` : on indique au compilateur que la valeur peut changer **à tout moment** (sans action visible dans le code). Il doit donc **à chaque fois** relire la valeur en mémoire et ne pas optimiser les accès :

```c
volatile uint32_t *p_statut = (volatile uint32_t *)0x40021018;

while ((*p_statut & 1) == 0) {
    /* chaque tour de boucle : lecture réelle en mémoire */
}
```

---

## 3. Où utiliser volatile ?

Utiliser **volatile** dans les cas suivants :

| Cas | Explication |
|-----|-------------|
| **Registres de périphériques** | Lus/écrits par le matériel à des adresses fixes. |
| **Variables modifiées dans une ISR** | L'ISR peut modifier un flag ou un buffer ; le code « principal » lit cette variable. |
| **Variables modifiées par le DMA** | Le DMA écrit en RAM sans passer par le CPU. |
| **Variables partagées avec un autre cœur** | En multicore, l'autre cœur peut modifier la donnée. |

Exemple avec un **flag** modifié par une interruption :

```c
volatile uint8_t bouton_appuye = 0;  /* mis à 1 dans l'ISR du bouton */

void main_loop(void) {
    while (1) {
        if (bouton_appuye) {
            /* traiter l'appui */
            bouton_appuye = 0;
        }
    }
}
```

Sans `volatile`, le compilateur pourrait supposer que `bouton_appuye` ne change jamais dans la boucle et ne lire cette variable qu'une seule fois.

---

## 4. Ce que volatile ne fait PAS

- **volatile** ne garantit **pas** l'atomicité : une lecture ou une écriture peut être interrompue. Pour des accès plus complexes (ex. incrément), il faudra plus tard des mécanismes (section critique, atomiques, mutex).
- **volatile** ne remplace **pas** la synchronisation entre tâches : il assure seulement que les accès ne sont pas optimisés ; il ne règle pas les race conditions.
- **volatile** ne rend **pas** la variable « thread-safe » : il dit « cette variable change en dehors du flot normal », pas « tu peux y accéder sans précaution ».

---

## 5. Règle pratique

**Règle** : toute donnée lue ou écrite par le **matériel** (registres) ou par une **ISR** doit être accédée via un type **volatile** (variable `volatile` ou pointeur `volatile`).

Pour les registres, on combine **pointeur** et **volatile** :

```c
#define REG_STATUT  0x40021018u
#define REG_ACCES   (*(volatile uint32_t *)REG_STATUT)

/* lecture */
uint32_t val = REG_ACCES;

/* écriture */
REG_ACCES |= (1u << 0);
```

---

## Points clés à retenir

- Le compilateur **optimise** en supposant que les variables ne changent que quand le code les modifie.
- En embarqué, des **données** peuvent changer à cause du **matériel** ou des **interruptions** : il faut utiliser **volatile** pour forcer une lecture/écriture réelle à chaque accès.
- **volatile** ne résout pas les problèmes de concurrence ; il évite les optimisations incorrectes sur des données « externes ».

---

## Tester sa compréhension

→ [**Scénarios – volatile**](scenarios/volatile.md) · → [**Éléments de réponse**](reponses/volatile.md)

---

**Suite** : [Leçon 4 – Accès aux bits et aux champs](04-acces-bits.md)
