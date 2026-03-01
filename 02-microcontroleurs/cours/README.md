# Cours – Module Microcontrôleurs

Les cours du module **02 – Microcontrôleurs** sont organisés en **sous-dossiers** : chaque thème est détaillé en plusieurs leçons progressives, adaptées aux **débutants** et réutilisables pour des **étudiants**.

---

## Structure des cours

| Dossier | Contenu | Nombre de leçons |
|---------|---------|-------------------|
| [**01-architecture-cortex-m**](01-architecture-cortex-m/README.md) | Architecture ARM Cortex-M (vue d'ensemble, familles, registres, mémoire, NVIC) | 5 leçons |
| [**02-modele-programme-registres**](02-modele-programme-registres/README.md) | Modèle programme et registres (accès C, GPIO, config sortie, CMSIS, champs) | 5 leçons |
| [**03-startup-interruptions**](03-startup-interruptions/README.md) | Startup, reset et interruptions (séquence reset, fichier startup, ISR, activation) | 5 leçons |

---

## Ordre recommandé

1. **Architecture Cortex-M** → comprendre le cœur, la mémoire et le NVIC.
2. **Modèle programme et registres** → accéder aux périphériques (GPIO en particulier).
3. **Startup et interruptions** → démarrage du MCU et mise en œuvre des ISR.

Chaque sous-dossier contient un **README** (vue d'ensemble, objectifs, ordre des leçons), des fichiers **.md** numérotés à lire dans l'ordre, et des dossiers **scenarios/** et **reponses/** pour tester sa compréhension (voir le README de chaque cours).

---

## Cible type

STM32 (Nucleo, Discovery) ou tout MCU ARM Cortex-M (LPC, Nordic, etc.). Les exemples font référence à la nomenclature CMSIS/STM32 quand c'est pertinent.
