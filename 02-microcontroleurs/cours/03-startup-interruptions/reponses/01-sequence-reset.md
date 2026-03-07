# Réponse – Séquence au reset

Voir [scénario](../scenarios/01-sequence-reset.md).

---

## Réponse Scénario 1 : Premier accès mémoire

**SP** : à l'**offset 0** de la table des vecteurs. **Reset_Handler** : à l'**offset 4**. Le processeur charge ces deux valeurs au reset pour initialiser la pile et savoir où exécuter le premier code.

**Table en flash** : Au boot, le CPU lit à une adresse **fixe** (0x0000_0000 ou 0x0800_0000 selon le MCU). Le **linker script** place la table des vecteurs au début de la section code (flash) ; si la table n'est pas à cette adresse, le CPU chargerait des valeurs invalides → crash.

---

## Réponse Scénario 2 : Rôle du Reset_Handler

**.data** : Les variables globales **initialisées** ont leurs valeurs en **flash** ; au reset la **RAM** est indéfinie. Le Reset_Handler **copie** de la flash vers la RAM pour que les variables aient la bonne valeur au démarrage de main().

**.bss** : Variables globales **non initialisées** (ou à 0). La norme C impose qu'elles soient à **zéro** ; le Reset_Handler fait un **zero-fill** de la zone .bss en RAM.

**main()** : S'il retournait, l'exécution reviendrait au Reset_Handler puis « après » main il n'y a plus de code valide. En embarqué, main() fait une **boucle infinie** ou appelle **vTaskStartScheduler()** (RTOS) qui ne retourne pas.

---

**Retour** : [Scénarios](../scenarios/README.md) · [Leçon 1](../01-sequence-reset.md)
