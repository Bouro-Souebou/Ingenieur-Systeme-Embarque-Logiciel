# Scénarios – Types et stdint.h

Situations pour vérifier votre compréhension de la [Leçon 2 – Types et stdint.h](../02-types-et-stdint.md).

---

## Scénario 1 : Dépassement (overflow) avec un petit type

Un capteur renvoie une valeur sur **10 bits** (0 à 1023). Le code utilise un **`uint8_t`** pour stocker cette valeur :

```c
uint8_t valeur_capteur;
valeur_capteur = lire_capteur_10_bits();  /* retourne 0..1023 */
```

**Question** : Que se passe-t-il quand le capteur renvoie 300 ? Et 500 ? Quel type faut-il utiliser et pourquoi ?

---

## Scénario 2 : Portabilité et taille de `long`

Un programme embarqué stocke une **adresse de registre** (32 bits) dans une variable de type **`long`**. Le code est développé sur une carte à processeur 32 bits, où `long` fait 32 bits. Plus tard, on recompile le même code sur un PC 64 bits pour des tests de simulation : sur ce PC, `long` fait 64 bits.

**Questions** : Quels risques (affichage, masques, décalages) ? Quelle bonne pratique pour les adresses et valeurs à taille fixe ?

---

*Après avoir réfléchi, consultez les* [**Éléments de réponse – Types et stdint**](../reponses/types-stdint.md).

---

**Retour** : [Leçon 2 – Types et stdint.h](../02-types-et-stdint.md) · [Vue d'ensemble du cours C](../README.md)
