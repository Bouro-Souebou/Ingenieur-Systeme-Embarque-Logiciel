# Cours – Module Fondements

Les cours du module **Fondements** sont organisés en **sous-dossiers** : chaque thème est détaillé en plusieurs leçons progressives, adaptées aux **débutants** et réutilisables pour des **étudiants**.

---

## Structure des cours

| Dossier | Contenu | Nombre de leçons |
|---------|---------|-------------------|
| [**01-c-embarque**](01-c-embarque/README.md) | C pour l'embarqué (types, volatile, bits, pointeurs, mémoire, pièges) | 7 leçons |
| [**02-bus-protocoles**](02-bus-protocoles/README.md) | Bus et protocoles (série, UART, SPI, I2C, comparaison) | 5 leçons |
| [**03-temps-reel**](03-temps-reel/README.md) | Temps réel et contraintes (définition, latence, interruptions, RTOS) | 5 leçons |

---

## Ordre recommandé

1. **C pour l'embarqué** → bases du langage et accès au matériel.
2. **Bus et protocoles** → communication avec les périphériques.
3. **Temps réel et contraintes** → réactivité, interruptions, structure du logiciel.

Chaque sous-dossier contient un **README** (vue d'ensemble, objectifs, ordre des leçons) et des fichiers **.md** numérotés (01-, 02-, …) à lire dans l'ordre.

**Tester sa compréhension** : les cours peuvent inclure des dossiers **scenarios/** (questions, situations classiques) et **reponses/** (analyse, solution, pièges). Ex. : [03-temps-reel – Scénarios](03-temps-reel/scenarios/README.md) et [Réponses](03-temps-reel/reponses/README.md).

---

## Utilisation pour les étudiants

- Les leçons peuvent être distribuées telles quelles (format Markdown).
- Chaque leçon est autonome (objectif, contenu, points clés, lien vers la suivante).
- Les TP du dossier `../tp/` complètent le cours C pour l'embarqué ; les cours Bus et Temps réel préparent les TP des modules suivants (microcontrôleurs, périphériques).
