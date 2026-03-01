# Travaux pratiques – Fondements

## Exercices

1. **exercice_volatile_bits.c** : manipulation de registres (volatile, set/clear bit, champ 4 bits).  
   - Sur PC : compiler avec `gcc -o exo exercice_volatile_bits.c && ./exo`.  
   - Sur cible : remplacer la simulation par l’adresse réelle du registre GPIO (voir Reference Manual).

2. **machine_etats_simple.c** : (à créer ou fourni) machine à états pour un « bouton + LED » (idéalement avec délai anti-rebond logiciel).

3. **parsing_uart_simple.c** : (à créer) parser une ligne de type `CMD arg1 arg2\r\n` et appeler une action selon CMD (simulation ou vraie UART plus tard).

## Ordre conseillé

Faire 1 puis 2 puis 3. Chaque exercice peut être d’abord écrit/testé sur PC, puis porté sur la cible.
