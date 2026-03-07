# Réponse – Familles Cortex-M

Voir [scénario](../scenarios/02-familles-cortex-m.md).

---

## Réponse Scénario 1 : Choisir un cœur pour un projet

**Privilégier M4** (avec **FPU** si disponible sur le MCU) : le **régulateur PID** et la boucle à 10 kHz font beaucoup de calculs en **float**. Sur **M3**, le flottant est **émulé en logiciel** → lent. Sur **M4**, la **FPU** (Floating-Point Unit) en simple précision exécute les opérations float en matériel → beaucoup plus rapide, ce qui permet de tenir la cadence 10 kHz à coût raisonnable.

**M3 vs M4** : M3 n’a **pas de FPU** ; M4 en a une **optionnelle** (simple précision 32 bits). Pour du float intensif, M4 (avec FPU) est le bon compromis coût/performance.

---

## Réponse Scénario 2 : M0+ vs M4

**IoT sur pile** : **M0 ou M0+** — très **faible consommation**, pipeline court, pas de FPU. Idéal pour des applications qui se réveillent peu souvent (une trame par minute) et doivent **dormir** le reste du temps. Coût et encombrement minimaux.

**Moteur FOC** : **M4 avec FPU** (ou M7 si besoin de double précision ou de marge) — FOC demande des calculs **trigo et flottant** en temps réel à haute fréquence. La **FPU** M4 (simple précision) suffit en général ; M7 apporte plus de puissance et éventuellement une FPU double précision.

---

**Retour** : [Scénarios](../scenarios/README.md) · [Leçon 2](../02-familles-cortex-m.md)
