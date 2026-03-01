# Scénarios – Robustesse et sécurité

Situations pour vérifier votre compréhension du cours [5.3 – Sécurité, robustesse et maintenabilité](03-securite-robustesse.md).

---

## Scénario 1 : Blocage sur une attente

Le logiciel attend un **acquittement** I2C après l’envoi d’une commande. En cas de coupure du bus ou de panne du périphérique, l’attente peut être **infinie** et le reste du système ne s’exécute plus.

**Questions** : Quel mécanisme général éviter ce blocage ? Où l’appliquer (UART, mutex, autre) ?

---

## Scénario 2 : Commande reçue par UART

L’application reçoit une **commande** formatée (ex. « SET,param,123 ») via l’UART et la traite en copiant les champs dans un buffer avec `strcpy()` puis en parsant.

**Questions** : Quels **risques** (sécurité, robustesse) ? Quelles précautions (fonctions, validation, longueur) ?

---

*Après avoir réfléchi, consultez les* [**Éléments de réponse – Robustesse et sécurité**](../reponses/robustesse-securite.md).

---

**Retour** : [5.3 – Sécurité et robustesse](03-securite-robustesse.md) · [Vue d’ensemble 05](../../README.md)
