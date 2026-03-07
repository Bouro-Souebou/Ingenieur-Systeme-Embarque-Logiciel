# Scénario – FreeRTOS en bref

Pour la leçon [05 – FreeRTOS en bref](../05-freertos-en-bref.md).

---

## Scénario 1 : vTaskStartScheduler ne revient pas

Dans main(), après création des tâches et des queues, on appelle **vTaskStartScheduler()**. Le programme semble « bloqué » dans cette fonction.

**Questions** : Est-ce un bug ? Que fait vTaskStartScheduler() ? Quand revient-elle (ou pas) ? Que faire si elle revient (erreur) ?

---

## Scénario 2 : Pas d'appel à vTaskStartScheduler

Le développeur crée des tâches avec xTaskCreate mais oublie d'appeler **vTaskStartScheduler()**. main() se termine et rien ne s'exécute.

**Questions** : Pourquoi les tâches ne tournent-elles pas ? Quel est le rôle de vTaskStartScheduler() par rapport à la boucle principale (main) ?

---

**Réponse** : [../reponses/05-freertos-en-bref.md](../reponses/05-freertos-en-bref.md) · **Retour** : [Vue d'ensemble](../README.md)
