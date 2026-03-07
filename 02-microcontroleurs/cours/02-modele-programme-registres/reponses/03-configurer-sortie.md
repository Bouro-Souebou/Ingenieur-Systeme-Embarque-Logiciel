# Réponse – Configurer une broche en sortie

Voir [scénario](../scenarios/03-configurer-sortie.md).

---

## Réponse Scénario 1 : CRL et PA5

**Bits** : Broche 5 → bits 20 à 23. Mode 11 = 50 MHz, config 00 = push-pull. Effacer d'abord pour ne pas toucher aux autres broches (lecture, AND ~masque, OR nouvelle valeur, écriture).

---

## Réponse Scénario 2 : Ordre

**Ordre** : (1) RCC activer horloge GPIOA, (2) CRL config, (3) ODR/BSRR. Horloge avant tout accès sinon registres ignorés ou faute.

---

**Retour** : [Scénarios](../scenarios/README.md) · [Leçon 3](../03-configurer-sortie.md)
