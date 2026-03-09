# 02 – Microcontrôleurs

Architecture ARM Cortex-M, modèle registres, démarrage (startup), vecteurs d'interruption et gestion des exceptions.  
Les cours sont **détaillés en leçons progressives** dans des sous-dossiers, destinés aux **débutants** et utilisables pour des **étudiants**.

## Contenu des cours

Les cours se trouvent dans le dossier **[cours/](cours/)**. Chaque thème est découpé en plusieurs leçons (sous-dossiers) :

| Thème | Dossier | Description |
|-------|---------|-------------|
| **Architecture ARM Cortex-M** | [cours/01-architecture-cortex-m/](cours/01-architecture-cortex-m/README.md) | 5 leçons : vue d'ensemble, familles, registres, mémoire, NVIC |
| **Modèle programme et registres** | [cours/02-modele-programme-registres/](cours/02-modele-programme-registres/README.md) | 5 leçons : accès C, GPIO, config sortie, CMSIS, champs |
| **Startup, reset et interruptions** | [cours/03-startup-interruptions/](cours/03-startup-interruptions/README.md) | 5 leçons : séquence reset, startup, ISR, activation, synthèse |

→ **Index complet** : [cours/README.md](cours/README.md)

## Applications pratiques

- **tp/** : série de TP progressifs pour **STM32 NUCLEO F446RE** : prise en main des outils (IDE, build, flash, debug), blink LED (registres), bouton + LED (polling), interruption EXTI (ISR). Voir [tp/README.md](tp/README.md).
- **projet/** : application bare-metal (ex. chronomètre avec bouton et affichage).

Pour comprendre **comment passer du code à la carte** (compilation, édition de liens, flash, débogage), voir le document **[Chaîne de compilation et déploiement](../ressources/chaine-compilation-deploiement.md)** dans `ressources/`.

## Cible type

STM32 (Nucleo, Discovery) ou tout MCU ARM Cortex-M (LPC, Nordic, etc.). Les exemples utilisent la nomenclature CMSIS/STM32 quand c'est pertinent.

---

**Commencer par** : [01 – Architecture ARM Cortex-M](cours/01-architecture-cortex-m/README.md)
