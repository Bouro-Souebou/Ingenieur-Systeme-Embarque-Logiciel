# Leçon 1 – Séquence au reset

## Objectif de la leçon

Comprendre **ce qui se passe** lorsque le microcontrôleur est mis sous tension ou reçoit un signal de reset : chargement du Stack Pointer et du Program Counter depuis la table des vecteurs, puis exécution du Reset_Handler jusqu'à l'appel à `main()`.

---

## 1. Déclenchement du reset

Le **reset** peut être provoqué par :

- **Mise sous tension** (power-on reset).
- **Broche RESET** tirée au niveau actif (généralement bas).
- **Watchdog** (si le logiciel ne « nourrit » pas le watchdog à temps).
- **Logiciel** (demande de reset via un registre de contrôle).

Au reset, le processeur repart dans un **état connu** : pas d’exécution de code applicatif tant que le **démarrage** (startup) n’a pas préparé l’environnement (stack, données initialisées, etc.).

---

## 2. Premier accès : la table des vecteurs

Dès la fin du reset, le cœur ARM Cortex-M effectue ses **premiers accès mémoire** à une adresse fixe (souvent **0x0000_0000** ; sur STM32 la flash est parfois mappée à 0x0800_0000 et le bootloader fait que 0x0000_0000 pointe vers 0x0800_0000). À cette adresse se trouve la **table des vecteurs** :

- **Offset 0** : valeur initiale du **Stack Pointer** (SP). Le processeur **charge** cette valeur dans R13 (SP). La stack est donc initialisée avec l’adresse (généralement en haut de la RAM) définie dans le fichier de lien (linker script).
- **Offset 4** : adresse du **Reset_Handler**. Le processeur **charge** cette adresse dans le **Program Counter** (PC) et commence à exécuter le code à cette adresse.

Les entrées suivantes (offset 8, 12, …) sont les handlers des autres exceptions (NMI, HardFault, …) et des IRQ. Ils ne sont pas exécutés au reset ; ils sont seulement **chargés** quand une interruption correspondante se déclenche.

---

## 3. Rôle du Reset_Handler

Le **Reset_Handler** est une fonction (souvent en assembly ou en C) qui :

1. **Copie** la section **.data** (variables globales initialisées) de la **flash** vers la **RAM**. En effet, au reset la RAM est « vide » ; les valeurs initiales des variables sont stockées en flash et doivent être copiées en RAM au démarrage.
2. **Met à zéro** la section **.bss** (variables globales non initialisées, ou initialisées à 0). La norme C impose que ces variables soient à 0 au démarrage.
3. **Appelle** éventuellement des constructeurs C++ si le projet est en C++.
4. **Appelle** la fonction **main()** du programme utilisateur.

Une fois dans `main()`, le programme « normal » s’exécute. Le Reset_Handler ne revient jamais : `main()` ne doit pas retourner (boucle infinie ou appel à un RTOS qui ne retourne pas).

---

## 4. Résumé de la séquence

```
Reset matériel
    → CPU lit @ 0x0000_0000 : charge SP
    → CPU lit @ 0x0000_0004 : charge PC (Reset_Handler)
    → Exécution de Reset_Handler
        → Copie .data (flash → RAM)
        → Zero-fill .bss
        → Appel main()
    → Exécution de main() (boucle infinie ou vTaskStartScheduler, etc.)
```

---

## Points clés à retenir

- Au **reset**, le CPU charge **SP** et **PC** depuis la **table des vecteurs** (début de la flash).
- Le **Reset_Handler** initialise les données (.data, .bss) puis appelle **main()**.
- La table des vecteurs doit donc exister en flash à l’adresse attendue au boot (définie par le linker script et le fichier startup).

---

## Tester sa compréhension

→ [Scénario – Séquence au reset](scenarios/01-sequence-reset.md) · [Réponse](reponses/01-sequence-reset.md)

---

**Suite** : [Leçon 2 – Le fichier startup](02-fichier-startup.md)
