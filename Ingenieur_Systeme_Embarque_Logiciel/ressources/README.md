# Ressources

Références utiles pour approfondir la formation.

## Chaîne de compilation et déploiement

- **[Chaîne de compilation et déploiement](chaine-compilation-deploiement.md)** : du code source au programme sur la carte (compilation, édition de liens, script .ld, génération .elf/.bin, flash, débogage). À lire en complément du module **02 – Microcontrôleurs** lorsque tu prépares ton premier projet sur cible.

## Documentation et normes

- **C** : ISO/IEC 9899 (C99/C11) ; *Embedded C Coding Standard* (Barr Group, MISRA C).
- **ARM** : *Cortex-M Generic User Guide*, *ARMv6-M/ARMv7-M Architecture Reference Manual*.
- **Bus** : normes UART (RS-232/RS-485), I2C (NXP), SPI (de facto), CAN.

## Outils

- **IDE** : STM32CubeIDE, VS Code + extensions (C/C++, ARM, Cortex-Debug).
- **Toolchain** : arm-none-eabi-gcc (GNU Arm Embedded).
- **Débogage** : OpenOCD, ST-Link, J-Link ; GDB, trace (ETM/SWO si disponible).
- **Analyse** : Wireshark (réseau), logic analyzer (bus numériques), oscilloscope.

## Glossaire (à compléter dans `glossaire.md`)

- **ISR** : Interrupt Service Routine.
- **RTOS** : Real-Time Operating System.
- **HAL** : Hardware Abstraction Layer.
- **DMA** : Direct Memory Access.
- **CMSIS** : Cortex Microcontroller Software Interface Standard.

## Liens utiles

- [STM32 Education](https://www.st.com/en/education.html)
- [FreeRTOS documentation](https://www.freertos.org/Documentation/RTOS_book.html)
- [Embedded Artistry](https://embeddedartistry.com/) (articles et bonnes pratiques)
