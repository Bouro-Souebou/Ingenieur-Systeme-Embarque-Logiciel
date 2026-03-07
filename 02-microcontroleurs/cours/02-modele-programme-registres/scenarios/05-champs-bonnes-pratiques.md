# Scénario – Champs multi-bits et bonnes pratiques

Pour la leçon [05 – Champs multi-bits et bonnes pratiques](../05-champs-bonnes-pratiques.md).

---

## Scénario 1 : Modifier un champ

On veut mettre les 4 bits de la broche 7 (CRL, bits 28-31) à 0x9 sans toucher aux autres broches.

**Questions** : Quelle séquence (lire, effacer masque, mettre valeur, réécrire) ? Pourquoi borner la valeur (et 0xFu) avant de décaler ?

---

## Scénario 2 : BSRR vs ODR

Une ISR et la boucle principale modifient la LED (PA5). On utilise ODR avec read-modify-write.

**Questions** : Quel risque (race condition) ? Solution avec BSRR (set/reset atomique) ? Pourquoi ne pas mélanger style registres et HAL sans raison ?

---

**Réponse** : [../reponses/05-champs-bonnes-pratiques.md](../reponses/05-champs-bonnes-pratiques.md) · **Retour** : [Vue d'ensemble](../README.md)
