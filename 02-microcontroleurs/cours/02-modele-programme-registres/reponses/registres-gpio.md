# Réponses – Registres et GPIO

Voir [scénarios](../scenarios/registres-gpio.md).

---

## Scénario 1 : La LED ne s'allume pas

**Problème** : L’**horloge** du port GPIO (ex. GPIOA) est souvent **désactivée** au reset. Sans activer l’horloge (registre **RCC**), les accès aux registres du port n’ont **aucun effet**.

**Solution** : Activer l’horloge du port **avant** de configurer et d’utiliser les broches (ex. `RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;` ou `__HAL_RCC_GPIOA_CLK_ENABLE()`). Ordre : 1) RCC, 2) config CRL/CRH, 3) ODR/IDR.

**Piège** : Broche configurée en **entrée** au lieu de sortie → écriture ODR sans effet.

---

## Scénario 2 : Lire une entrée avec ODR

**Problème** : **ODR** sert à **écrire** les sorties. Pour **lire** une broche en entrée, il faut **IDR** (Input Data Register). Lire ODR ne donne pas l’état physique de la broche.

**Solution** : `uint32_t val = REG(GPIOB_IDR); if (val & (1u << 3)) { ... }`. Règle : **IDR** = lecture entrées, **ODR** = écriture sorties.

**Piège** : Pour modifier **un seul bit** de sortie sans race avec une ISR, utiliser **BSRR** (écriture atomique) au lieu de read-modify-write sur ODR.

---

**Retour** : [Scénarios](../scenarios/README.md) · [Modèle programme et registres](../README.md)
