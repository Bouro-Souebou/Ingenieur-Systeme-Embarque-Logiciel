# Réponse – Modèle de programmation : registres

Voir [scénario](../scenarios/03-modele-programmation.md).

---

## Réponse Scénario 1 : SP et table des vecteurs

**Valeur initiale du SP** : Elle est lue à l’**offset 0** de la **table des vecteurs** (première entrée). Cette table est en **flash** (souvent 0x0800_0000 ou 0x0000_0000 selon le boot). Au reset, le processeur charge cette valeur dans **R13 (SP)**.

**Pourquoi initialiser la pile** : Les **appels de fonction** et les **variables locales** utilisent la pile. Sans SP valide, le premier PUSH ou appel de fonction corromprait la mémoire ou provoquerait une faute. La table des vecteurs est fournie par le **fichier startup** du fabricant.

---

## Réponse Scénario 2 : PC et débogage

**Registro de la faute** : Le **PC (R15)** contient l’**adresse** de l’instruction en cours (ou de la suivante selon le modèle). En cas de HardFault, afficher le **PC** (et éventuellement le **LR**) permet de localiser l’instruction en cause dans le listing ou le code source.

**LR** : En situation **normale**, **R14 (LR)** contient l’**adresse de retour** après un **BL** (Branch with Link). Au **retour** de la fonction (BX LR ou POP {PC}), l’exécution reprend à cette adresse.

**En interruption** : En entrée d’ISR, le processeur met dans LR une valeur spéciale **EXC_RETURN** (et non une adresse de code). Au retour (BX LR), le processeur restaure le contexte et reprend le code interrompu. Le programmeur n’a en général pas à modifier LR en C.

---

**Retour** : [Scénarios](../scenarios/README.md) · [Leçon 3](../03-modele-programmation.md)
