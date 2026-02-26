# 01 – Fondements

Bases indispensables pour l'embarqué : C adapté au matériel, bus numériques, notion de temps réel.  
Les cours sont **détaillés en leçons progressives** dans des sous-dossiers, destinés aux **débutants** et utilisables pour des **étudiants**.

## Contenu des cours

Les cours se trouvent dans le dossier **[cours/](cours/)**. Chaque thème est découpé en plusieurs leçons (sous-dossiers) :

| Thème | Dossier | Description |
|-------|---------|-------------|
| **C pour l'embarqué** | [cours/01-c-embarque/](cours/01-c-embarque/README.md) | 7 leçons : types, volatile, bits, pointeurs, mémoire, pièges |
| **Bus et protocoles** | [cours/02-bus-protocoles/](cours/02-bus-protocoles/README.md) | 5 leçons : série, UART, SPI, I2C, comparaison |
| **Temps réel et contraintes** | [cours/03-temps-reel/](cours/03-temps-reel/README.md) | 5 leçons : définition, latence, interruptions, RTOS, synthèse |

→ **Index complet** : [cours/README.md](cours/README.md)

## Applications pratiques

- **tp/** : exercices et petits programmes (volatile/bits, blink bare-metal, machine à états, parsing).
- **projet/** : mini-projet de synthèse (ex. contrôle LED + UART simple).

## Ordre conseillé

1. **C pour l'embarqué** (toutes les leçons) → puis exercices C dans `tp/`.
2. **Bus et protocoles** → schémas, timing, choix du protocole.
3. **Temps réel** → avant ou en parallèle du module Microcontrôleurs (interruptions, ISR).
