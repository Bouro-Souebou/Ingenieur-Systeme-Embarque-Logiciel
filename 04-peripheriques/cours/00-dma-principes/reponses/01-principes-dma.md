# Réponse – Principes du DMA

Voir [scénario](../scenarios/01-principes-dma.md).

---

## Réponse Scénario 1 : Quand choisir le DMA ?

**Limites** : En polling, le CPU attend chaque octet UART et chaque conversion ADC → **charge élevée** et **jitter** (le moment de lecture dépend du logiciel). En interruption seule, à fort débit les ISR s'enchaînent et le CPU passe beaucoup de temps en contexte d'interruption ; risque de **manquer** des données si une ISR est retardée.

**DMA** : Le CPU **configure** une fois le transfert ; le DMA copie **en arrière-plan**. Pour l'UART : chaque octet reçu déclenche un transfert vers la RAM sans ISR par octet. Pour l'ADC : chaque conversion terminée déclenche un transfert ; **régularité** assurée par le matériel, charge CPU réduite.

---

## Réponse Scénario 2 : Paramètres d'un transfert DMA

**Source** : le **registre de données** (DR) du UART (adresse **fixe**). **Destination** : le **buffer en RAM** (adresse qui **s'incrémente** après chaque octet).

**Déclencheur** : **matériel** — une requête du périphérique UART à chaque octet reçu (RXNE ou équivalent).

**Incrément** : **Source** = pas d'incrément (toujours le même registre DR). **Destination** = incrémenter (octet par octet ou word selon la config) pour remplir le buffer.

**Interruption fin de transfert** : le logiciel sait que les **256 octets** sont reçus ; il peut **traiter** le buffer (parser, copier) ou **relancer** un nouveau transfert (double buffering). L'ISR doit rester **courte** (flag, queue).

---

**Retour** : [Scénarios](../scenarios/README.md) · [Leçon 1](../01-principes-dma.md)
