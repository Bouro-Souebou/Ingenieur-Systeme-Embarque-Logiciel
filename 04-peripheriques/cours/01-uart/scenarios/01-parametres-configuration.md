# Scénario – Paramètres et configuration UART

Pour la leçon [01 – Paramètres et configuration](../01-parametres-configuration.md).

---

## Scénario 1 : Baudrate et format

On connecte le MCU à un **module GPS** qui envoie des NMEA à **9600 baud**, 8 bits, pas de parité, 1 bit d'arrêt. Le terminal affiche des caractères illisibles.

**Questions** : Quels paramètres doivent être **identiques** des deux côtés (émetteur / récepteur) ? Où configurer le baudrate et le format sur le MCU ? Que faire si le MCU et le module n'utilisent pas la même horloge de base (diviseur) ?

---

## Scénario 2 : Broches et horloge

Le développeur a branché les fils TX du MCU et du récepteur, et RX du MCU et du récepteur (croisés). Il a choisi PA9/PA10 dans le CubeMX pour USART1. Aucune donnée ne sort.

**Questions** : Quelles étapes sont nécessaires pour que PA9/PA10 fonctionnent en UART (GPIO, horloge) ? Pourquoi l'**horloge du périphérique UART** (RCC) doit-elle être activée **avant** d'écrire dans les registres ?

---

**Réponse** : [../reponses/01-parametres-configuration.md](../reponses/01-parametres-configuration.md) · **Retour** : [Vue d'ensemble](../README.md)
