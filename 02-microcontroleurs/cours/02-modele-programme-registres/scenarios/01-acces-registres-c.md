# Scénario – Accès aux registres en C

Pour la leçon [01 – Accès aux registres en C](../01-acces-registres-c.md).

---

## Scénario 1 : Pointeur volatile

On écrit `*(uint32_t *)0x4001080C = 0x20;` pour allumer une LED. Le compilateur optimise et supprime l'écriture.

**Questions** : Pourquoi le compilateur peut-il supprimer l'accès ? Quelle qualification utiliser (**volatile**) ? Où trouver l'adresse (Reference Manual) ?

---

## Scénario 2 : Base et offset

Le registre **ODR** de GPIOA est à **0x4001080C**. GPIOB a la même structure avec une base différente.

**Questions** : Comment organiser le code (macros base + offset) ? Si on change de MCU, que ne modifier qu'une macro (GPIOA_BASE) ? Quelle macro **REG(addr)** pour lire/écrire ?

---

**Réponse** : [../reponses/01-acces-registres-c.md](../reponses/01-acces-registres-c.md) · **Retour** : [Vue d'ensemble](../README.md)
