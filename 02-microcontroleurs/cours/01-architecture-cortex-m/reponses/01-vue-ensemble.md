# Réponse – Vue d'ensemble du Cortex-M

Voir [scénario](../scenarios/01-vue-ensemble.md).

---

## Réponse Scénario 1 : Cœur pour l'embarqué

**Cortex-M adapté** : Conçu pour le **contrôle** et l'**embarqué** : **RISC** (efficacité énergétique), **NVIC intégré** (gestion des interruptions sans logique externe), **pas de MMU** (coût et complexité réduits). Réactivité aux événements grâce aux interruptions matérielles (vectored, priorité).

**Pas de MMU** : Les adresses sont **physiques** ; pas de pagination ni de mémoire virtuelle. Pas d'exécution de **Linux** classique (qui requiert une MMU). On utilise un **RTOS** ou du **bare-metal**. Simplicité du modèle : une seule vue de la mémoire (flash, RAM, périphériques à adresses fixes).

---

## Réponse Scénario 2 : Thumb et taille du code

**Thumb** : Instructions sur **16 bits** → **densité du code** plus élevée qu’en ARM 32 bits, donc **moins de flash** utilisée. Important quand la mémoire programme est limitée.

**Choix** : C’est le **compilateur** qui choisit les instructions (Thumb, Thumb-2) selon la cible (Cortex-M). Le programmeur écrit en C ; le compilateur génère du Thumb-2 par défaut pour Cortex-M.

**Thumb-2** : Mélange d’instructions **16 et 32 bits** : bon compromis **densité / performance**. Certaines opérations en 32 bits (ex. branches longues, accès étendus), le reste en 16 bits.

---

**Retour** : [Scénarios](../scenarios/README.md) · [Leçon 1](../01-vue-ensemble.md)
