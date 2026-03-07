# Réponse – Bonnes pratiques ADC

Voir [scénario](../scenarios/05-bonnes-pratiques.md).

---

## Réponse Scénario 1 : Impédance

**Cause** : Source haute impédance, temps de charge du condensateur d'échantillonnage insuffisant. **Solution** : temps d'échantillonnage plus long (SMP) ou buffer (ampli suiveur).

---

## Réponse Scénario 2 : Bruit

**Réduire** : découplage Vref, moyenne de N échantillons. **Inconvénient** du moyennage : latence.

---

**Retour** : [Scénarios](../scenarios/README.md) · [Leçon 5](../05-bonnes-pratiques.md)
