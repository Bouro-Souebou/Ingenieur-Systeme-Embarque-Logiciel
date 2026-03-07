# Leçon 3 – Déclarer et implémenter une ISR

## Objectif de la leçon

Savoir **écrire** une routine de service d'interruption (ISR) en C : nom exact correspondant au vecteur, **signature** (sans paramètre, sans retour), **acquittement** de l'interruption, et respect de la règle « ISR courte ».

---

## 1. Nom de la fonction = symbole du vecteur

Sur Cortex-M, l’**adresse** appelée lors d’une IRQ est celle stockée dans la **table des vecteurs** pour ce numéro de vecteur. Le fichier startup associe à chaque entrée un **symbole** (nom de fonction). Pour que ton code soit appelé, tu dois définir une fonction C dont le **nom** est **exactement** celui utilisé dans le startup.

Exemples (STM32) :

- **EXTI0_IRQHandler** pour la ligne EXTI 0 (bouton sur PA0, etc.).
- **USART1_IRQHandler** pour l’UART 1.
- **SysTick_Handler** pour le tick système.

La casse et l’orthographe doivent être **identiques** (souvent documentées dans le Reference Manual ou le fichier startup fourni par le fabricant).

---

## 2. Signature de la fonction

Une ISR est une fonction :

- **Sans paramètre** : `void ma_isr(void)`.
- **Sans valeur de retour** : type de retour `void`.

Le compilateur génère le **prologue** (sauvegarde des registres utilisés) et l’**épilogue** (restauration, puis instruction de retour spéciale pour quitter le mode Handler). Tu n’as pas à écrire d’assembly ; le fait d’utiliser le **bon nom** et cette signature suffit pour que le linker place l’adresse de ta fonction dans la table des vecteurs (si tu as remplacé le symbole Weak).

---

## 3. Acquitter l’interruption

Quand une IRQ se déclenche, le **périphérique** (et/ou le NVIC) met un **bit « pending »** à 1. Le processeur exécute ton handler. Si tu ne **remets pas** ce bit à 0 (on dit « acquitter » ou « clear pending »), dès la sortie du handler l’interruption sera **à nouveau** en attente et le processeur rappellera ton handler en boucle.

Il faut donc, **dans** l’ISR, **écrire** dans le registre approprié pour clear le pending. Exemple pour EXTI (STM32) : le registre **EXTI->PR** (Pending Register) a un bit par ligne ; écrire 1 dans le bit de la ligne concernée efface le pending :

```c
void EXTI0_IRQHandler(void) {
    if (EXTI->PR & (1u << 0)) {        /* vérifier que c’est bien la ligne 0 */
        /* faire le travail minimal */
        flag_bouton = 1;
        EXTI->PR = (1u << 0);         /* clear pending : écrire 1 pour effacer */
    }
}
```

Pour d’autres périphériques (UART, timer), le mécanisme peut être différent (lire un registre de statut, écrire dans un registre de clear). Consulter le **Reference Manual** du bloc concerné.

---

## 4. ISR courte : quoi faire et quoi éviter

**À faire** dans l’ISR :

- Mettre à jour un **flag** (variable `volatile`) ou écrire une donnée dans un **buffer** (ex. octet reçu UART).
- **Acquitter** l’interruption (clear pending).
- Éventuellement **donner** un sémaphore ou **envoyer** un message dans une queue (en RTOS) pour réveiller une tâche.

**À éviter** :

- **Calculs lourds**, boucles longues, `printf`, accès à des ressources partagées sans protection (risque de deadlock ou de latence).
- **Attentes bloquantes** (delay, attente sur une queue avec timeout long). Les versions « FromISR » des objets FreeRTOS sont faites pour être appelées depuis une ISR (non bloquantes).

Si un traitement lourd est nécessaire, l’ISR se contente de **signaler** (flag ou queue) ; une **tâche** ou la **boucle principale** fait le travail.

---

## Points clés à retenir

- **Nom** de l’ISR = symbole du vecteur (ex. EXTI0_IRQHandler) ; **signature** : `void isr(void)`.
- **Acquitter** l’interruption (clear pending) pour éviter les rappels en boucle.
- Garder l’ISR **courte** : flag, buffer, clear pending ; le reste en tâche ou en boucle principale.

---

## Tester sa compréhension

→ [Scénario – Déclarer et implémenter une ISR](scenarios/03-declarer-implementer-isr.md) · [Réponse](reponses/03-declarer-implementer-isr.md)

---

**Suite** : [Leçon 4 – Activer une interruption](04-activer-interruption.md)
