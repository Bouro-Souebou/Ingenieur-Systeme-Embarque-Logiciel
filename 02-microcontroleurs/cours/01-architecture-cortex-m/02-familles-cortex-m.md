# Leçon 2 – Familles Cortex-M

## Objectif de la leçon

Distinguer les **familles** de cœurs Cortex-M (M0, M0+, M3, M4, M7) et savoir choisir (ou reconnaître) un MCU selon l'application : coût, consommation, performance, calcul flottant.

---

## 1. Pourquoi plusieurs familles ?

ARM propose plusieurs **variantes** du cœur Cortex-M pour couvrir des besoins différents :

- **Ultra bas coût / faible consommation** : capteurs, IoT, objets à pile.
- **Usage général** : contrôle industriel, automobile, interfaces.
- **Calcul et signal** : régulation, filtrage, moteur.
- **Haute performance** : interfaces riches, traitement d'image, multi-tâches lourd.

Chaque famille a un **pipeline** plus ou moins long, une **FPU** (unité flottante) optionnelle, et une **MPU** optionnelle ou standard.

---

## 2. Tableau des familles

| Cœur | Usage typique | Pipeline | FPU | MPU |
|------|----------------|----------|-----|-----|
| **M0 / M0+** | Ultra bas coût, très faible consommation | 3 stages | Non | Option |
| **M3** | Général (STM32 F1, L1, etc.) | 3 stages | Non | Option |
| **M4** | Signal, contrôle (STM32 F4, L4, etc.) | 3 stages | Option (simple précision) | Option |
| **M7** | Haute performance (STM32 F7, H7) | 6 stages | Option (double précision) | Oui |

---

## 3. Cortex-M0 et M0+

- **M0** : le plus simple et le plus économique. Pipeline 3 stages, pas de FPU, peu de fonctionnalités avancées.
- **M0+** : évolution du M0 avec quelques améliorations (moins de cycles pour certains accès, option single-cycle I/O). Très répandu dans les MCU à très bas coût et les composants IoT (Nordic nRF, STM32 L0, etc.).

**Typique** : applications à faible charge de calcul, réactivité aux interruptions, consommation minimale.

---

## 4. Cortex-M3

- Cœur « milieu de gamme » : 3 stages de pipeline, performances correctes, bon rapport coût/performance.
- Très utilisé dans les **STM32 F1**, **L1**, et de nombreux MCU industriels. Pas d'unité flottante matérielle (les calculs en flottant sont émulés en logiciel, donc plus lents).

**Typique** : contrôle industriel, communication, interfaces, premiers projets avec RTOS.

---

## 5. Cortex-M4

- Similaire au M3 avec une **FPU** (Floating-Point Unit) **optionnelle** en simple précision (32 bits). Quand la FPU est présente, les calculs `float` sont beaucoup plus rapides.
- Présent dans les **STM32 F4**, **L4**, **G4**, etc. Idéal pour la régulation, le filtrage, le traitement de signal léger.

**Typique** : contrôle moteur, capteurs avec calculs, audio simple, applications avec RTOS et calculs flottants.

---

## 6. Cortex-M7

- **Pipeline 6 stages** : plus de parallélisme, meilleures performances (DMIPS/MHz plus élevé).
- **FPU** optionnelle en **double précision** (64 bits). **MPU** souvent standard.
- Présent dans les **STM32 F7**, **H7**. Utilisé quand il faut de la puissance (écrans, algorithmes lourds, plusieurs protocoles en parallèle).

**Typique** : interfaces graphiques, traitement d'image, applications complexes.

---

## 7. En pratique

- Pour **apprendre** et pour la plupart des TPs : un **STM32 à base M3 ou M4** (Nucleo, Discovery) convient très bien.
- Pour un **projet à très faible consommation** : viser un MCU **M0+**.
- Pour un **projet avec beaucoup de calculs** (régulation, filtres) : viser un **M4** avec FPU (ou M7 si besoin de double précision).

---

## Points clés à retenir

- **M0/M0+** : économie, faible consommation.
- **M3** : général, bon rapport coût/performance.
- **M4** : signal, option FPU simple précision.
- **M7** : haute performance, pipeline 6 stages, FPU double précision possible.

---

**Suite** : [Leçon 3 – Modèle de programmation : registres](03-modele-programmation.md)
