# Réponse – Champs multi-bits et bonnes pratiques

Voir [scénario](../scenarios/05-champs-bonnes-pratiques.md).

---

## Réponse Scénario 1 : Modifier un champ sans toucher aux autres

**Séquence** : (1) **Lire** le registre : `crl = REG(GPIOA_CRL);`. (2) **Effacer** le champ : `crl &= ~(0xFu << 28);` (masque avec 0 pour les bits 28–31). (3) **Mettre** la nouvelle valeur : `crl |= (0x9u & 0xFu) << 28;`. (4) **Écrire** : `REG(GPIOA_CRL) = crl;`.

**Borner** : Si `nouvelle_valeur` vaut par exemple 0x12, sans masque `& 0xFu` les bits au-delà du champ (ex. bit 4) déborderaient sur les bits voisins (broche 6). Le `& 0xFu` garantit qu'on ne modifie que les 4 bits du champ.

---

## Réponse Scénario 2 : BSRR vs ODR

**Risque** : **Read-modify-write** : lecture de ODR, modification locale, écriture. Si une **ISR** s'exécute **entre** la lecture et l'écriture et modifie ODR, sa modification peut être **écrasée** par l'écriture qui suit (race condition). Résultat : un des deux changements est perdu.

**BSRR** : **Set** : `GPIOA->BSRR = (1u << 5);` (bit 5 à 1). **Reset** : `GPIOA->BSRR = (1u << (5 + 16));` (bits 16–31 = reset). Une **seule** écriture, **atomique** côté accès registre ; pas de lecture intermédiaire, donc pas de race avec une ISR.

**Mélanger styles** : Sans raison documentée, cela rend le code **incohérent** et moins lisible. Si on mélange (ex. HAL pour l'init, registres pour un timing critique), **commenter** la raison.

---

**Retour** : [Scénarios](../scenarios/README.md) · [Leçon 5](../05-champs-bonnes-pratiques.md)
