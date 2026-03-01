# Leçon 1 – Pourquoi le C en embarqué ?

## Objectif de la leçon

Comprendre **pourquoi** le langage C est encore le standard en électronique embarquée logicielle, et quelles **contraintes** du monde embarqué influencent la façon d'écrire le code.

---

## 1. Qu'est-ce qu'un système embarqué ?

Un **système embarqué** est un ordinateur spécialisé, intégré dans un produit (voiture, drone, capteur, appareil médical, etc.). Il a des caractéristiques très différentes d'un PC :

| Caractéristique | PC / serveur | Système embarqué typique |
|-----------------|--------------|---------------------------|
| **Mémoire RAM** | Plusieurs Go | Quelques Ko à quelques Mo |
| **Mémoire flash** | Disque / SSD | 64 Ko à quelques Mo |
| **Processeur** | Multi-cœur, fréquence élevée | Un cœur, 48–300 MHz souvent |
| **Alimentation** | Secte, batterie grande capacité | Batterie, énergie limitée |
| **Contraintes** | Performance, confort utilisateur | **Temps réel**, coût, fiabilité |

En résumé : **peu de ressources**, **comportement déterministe** et **réactif** requis.

---

## 2. Pourquoi le C et pas un autre langage ?

### C est proche du matériel

- Le C permet d'accéder à des **adresses mémoire** précises (registres des périphériques).
- Il n'y a pas de « couche » cachée entre ton code et le processeur : ce que tu écris se traduit de façon prévisible en instructions machine.
- Les **pointeurs** et les **types de taille fixe** permettent de décrire exactement la disposition des données en mémoire (registres 8, 16 ou 32 bits).

### Efficacité et prédictibilité

- Pas de **garbage collector** (pas de pause imprévisible pour libérer la mémoire).
- Pas de **runtime** lourd (comme en Java ou Python) : le programme démarre directement, sans interpréteur.
- Les compilateurs C pour microcontrôleurs (GCC, Keil, IAR) produisent du code **optimisé** et **compact**.

### Héritage et écosystème

- La quasi-totalité des **datasheets** et des **exemples** fournis par les fabricants (ST, NXP, etc.) sont en C.
- Les **RTOS** (FreeRTOS, Zephyr, etc.) ont des APIs en C.
- Les **normes** et bonnes pratiques (MISRA C, CERT C) ciblent le C pour l'embarqué critique.

### Et les autres langages ?

- **C++** : utilisé dans certains projets (objets, templates), mais avec des précautions (pas d'exceptions en temps réel critique, pas de heap dynamique non maîtrisé). Le C reste la base.
- **Rust** : en croissance pour l'embarqué (sécurité mémoire, pas de undefined behavior par défaut), mais l'écosystème et les formations restent encore majoritairement en C.
- **Python / JavaScript** : utilisés pour le **développement côté PC** (outils, tests, cloud), rarement sur le microcontrôleur lui-même à cause de la consommation mémoire et du manque de déterminisme.

---

## 3. Contraintes qui façonnent le code embarqué

### Mémoire limitée

- Pas de gros tableaux dynamiques ni de structures de données « magiques » : on dimensionne tout à l'avance (buffers de taille fixe, pas de `malloc` incontrôlé).
- Chaque **octet** compte : on évite les librairies lourdes et on privilégie les types adaptés (ex. `uint8_t` au lieu de `int` pour un compteur 0–255).

### Comportement déterministe

- Le logiciel doit réagir dans un **délai connu** (temps réel). On évite tout ce qui peut introduire de l'aléatoire ou des délais variables :
  - pas d'allocation dynamique imprévisible ;
  - pas de boucles dont le nombre d'itérations dépend de données non bornées ;
  - gestion explicite des **interruptions** et des **variables partagées** (avec `volatile` et plus tard des mécanismes de synchronisation).

### Accès direct au matériel

- Les **périphériques** (GPIO, UART, timers, etc.) sont des blocs matériels accessibles à des **adresses fixes** en mémoire. Le programme les pilote en lisant/écrivant dans ces adresses (registres). Le C est idéal pour cela : pointeurs, accès aux bits, pas d'abstraction imposée.

---

## 4. Ce que tu vas apprendre dans ce cours

Les leçons suivantes détaillent les **outils du C** indispensables pour écrire du code embarqué correct et maintenable :

1. **Types à taille fixe** : ne plus dépendre de « int = 32 bits chez moi » et adapter le code à la cible.
2. **volatile** : dire au compilateur de ne pas optimiser les accès à des données modifiées par le matériel ou les interruptions.
3. **Accès aux bits** : configurer un registre bit par bit (mode d'une broche, enable d'un périphérique).
4. **Pointeurs et adresses** : accéder aux registres des périphériques à des adresses fixes.
5. **Mémoire** : comprendre stack, heap, et les pièges à éviter (débordement, comportement indéfini).

---

## Points clés à retenir

- En embarqué, le C est privilégié pour sa **proximité avec le matériel**, son **efficacité** et son **écosystème**.
- Les contraintes (mémoire, temps réel, accès direct au matériel) imposent des **règles de codage** précises que nous allons voir.
- Maîtriser le C « embarqué » (types, volatile, bits, pointeurs, mémoire) est la base pour aborder sereinement les microcontrôleurs et les RTOS.

---

**Suite** : [Leçon 2 – Types et stdint.h](02-types-et-stdint.md)
