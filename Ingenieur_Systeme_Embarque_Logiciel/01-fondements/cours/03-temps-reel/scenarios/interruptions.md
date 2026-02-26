# Scénarios – Interruptions et réactivité

Quelques **situations classiques** pour vérifier que vous avez bien compris la leçon [Interruptions et réactivité](../03-interruptions-reactivite.md). Réfléchissez à chaque scénario avant de consulter les éléments de réponse.

---

## Scénario 1 : ISR plus longue que la période

Imaginez que vous développez un driver pour un **capteur de distance**. Vous placez la **lecture du capteur** (qui prend **10 ms**) directement dans une **ISR** déclenchée **toutes les 5 ms**.

**Question** : Que se passe-t-il ?

---

## Scénario 2 : printf dans une ISR

Pour déboguer, un développeur ajoute un **printf** dans l'ISR de réception UART : à chaque caractère reçu, il affiche la valeur. En test, tout semble correct ; en charge (réception rapide), le système se met à **ramer** ou à **planter**.

**Questions** : Pourquoi `printf` dans une ISR pose-t-il problème ? Que faire à la place ?

---

## Scénario 3 : Oubli d'acquitter l'interruption

L'ISR d'un **timer** incrémente un compteur utilisé par le programme principal. Le développeur a oublié de **clear le bit « pending »** (acquitter l'interruption) dans le contrôleur d'interruptions (NVIC) ou dans le périphérique timer à la fin de l'ISR.

**Question** : Que peut-il se passer au runtime (comportement observé) ?

---

## Scénario 4 : Variable partagée sans volatile

Une **ISR** met à jour un **flag** `uint8_t donnee_prete = 0;` (mis à 1 quand une donnée est reçue). La **boucle principale** fait : `while (!donnee_prete) { }` puis lit les données. En release (optimisations activées), le programme reste **bloqué** dans la boucle même quand l'ISR a mis le flag à 1.

**Question** : Quelle cause probable (côté langage C / compilateur) ? Quelle correction minimale ?

---

*Une fois que vous avez réfléchi (problème, conséquence, solution), consultez les* [**Éléments de réponse – Interruptions**](../reponses/interruptions.md) *(analyse, solution, pièges pour chaque scénario).*

---

**Retour** : [Leçon 3 – Interruptions et réactivité](../03-interruptions-reactivite.md) · [Vue d'ensemble du cours Temps réel](../README.md)
