# Leçon 5 – Dimensionnement de la stack

## Objectif de la leçon

Comprendre pourquoi la **stack** d'une tâche peut **déborder** (stack overflow), comment **détecter** le débordement avec FreeRTOS, et comment **dimensionner** la stack (marge, éviter gros buffers locaux et récursion).

---

## 1. Risque de stack overflow

Chaque tâche a sa **propre** stack (zone mémoire réservée à la création). Lors des appels de fonctions, les **variables locales** et les **adresses de retour** sont empilées. Si les appels sont trop **profonds** ou si des **variables locales** sont très volumineuses (gros tableaux), la stack peut **déborder** : écriture en dehors de la zone allouée, ce qui peut écraser d'autres données ou le contexte d'une autre tâche. Le résultat est souvent un **crash** (HardFault) ou un comportement imprévisible.

---

## 2. Détection : configCHECK_FOR_STACK_OVERFLOW

FreeRTOS peut **détecter** un débordement de stack (après coup) si **configCHECK_FOR_STACK_OVERFLOW** est défini à 1 ou 2 dans FreeRTOSConfig.h :

- **1** : le noyau vérifie après un changement de contexte si le pointeur de stack a dépassé la zone (mot magique en bas de la stack).
- **2** : vérification plus complète (pattern en haut de la stack).

Quand un overflow est détecté, le **hook** **vApplicationStackOverflowHook** est appelé. Tu peux y mettre un **breakpoint** ou allumer une LED pour déboguer. En production, on évite l'overflow en **dimensionnant** correctement les stacks.

---

## 3. Comment dimensionner

- **Estimer** la consommation : chaque **appel de fonction** utilise quelques octets (adresse de retour, variables locales). Une chaîne d'appels profonde (A appelle B appelle C appelle D…) consomme plus. Les **variables locales** volumineuses (tableaux de 256 octets, structures) consomment beaucoup.
- **Règle pratique** : pour une tâche simple (quelques appels, peu de locales), **128 à 256 words** (512–1024 octets) peuvent suffire. Pour une tâche qui fait du **printf**, des **conversions** (sprintf), ou appelle des **librairies** (TCP/IP, fichiers), prévoir **512 words** ou plus. Consulter la doc des librairies (ex. stack recommandée pour la tâche LwIP).
- **Marge** : en développement, ajouter une **marge** (ex. 25–50 %) pour les imprévus. Utiliser **uxTaskGetStackHighWaterMark** (si disponible) pour voir le **minimum** de stack restant atteint pendant l'exécution (high water mark = combien de bytes n'ont jamais été utilisés) ; cela permet d'ajuster la taille et de réduire si besoin.

---

## 4. Bonnes pratiques

- **Éviter** les gros **tableaux locaux** : préférer des buffers **statiques** (globaux ou static) ou alloués une fois.
- **Éviter** la **récursion** profonde ou non bornée dans une tâche.
- **Tâche idle** : elle a aussi une stack (configurée dans FreeRTOSConfig.h) ; si tu utilises un hook idle (ex. pour mettre le MCU en low power), vérifier qu'il ne consomme pas trop de stack.

---

## Points clés à retenir

- **Stack overflow** = débordement de la zone stack → crash ou comportement indéfini.
- **configCHECK_FOR_STACK_OVERFLOW** + **vApplicationStackOverflowHook** pour **détecter** en développement.
- **Dimensionner** selon la profondeur d'appels et les variables locales ; prévoir une **marge** ; utiliser le **high water mark** pour ajuster.

---

## Tester sa compréhension

→ [Scénario – Dimensionnement stack](scenarios/05-dimensionnement-stack.md) · [Réponse](reponses/05-dimensionnement-stack.md)

---

**Fin du cours Tâches et ordonnancement.**  
Retour à la [vue d'ensemble](README.md) ou passage au cours [Synchronisation et communication](../../03-synchronisation-communication/README.md).
