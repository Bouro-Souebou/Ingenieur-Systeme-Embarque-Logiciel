# 5.3 – Sécurité, robustesse et maintenabilité

## Objectifs

- Renforcer la **robustesse** (gestion d’erreurs, timeouts, états incohérents).
- Améliorer la **sécurité** (entrées utilisateur, mise à jour firmware, défense en profondeur).
- Garder le code **maintenable** (documentation, conventions, revue de code).

---

## 1. Robustesse

- **Timeouts** : toute attente (réception UART, acquittement I2C, prise de mutex) doit avoir un timeout pour éviter les blocages infinis. En cas de timeout : log, reset partiel ou global, retour d’erreur à l’appelant.
- **Vérification des paramètres** : bornes des tableaux, pointeurs non nuls (en debug : assertions). En production : éviter les crashes (valeur par défaut, code de retour).
- **Watchdog** : timer matériel qui reset le MCU si le logiciel ne le « nourrit » pas périodiquement. Utiliser pour détecter les boucles infinies ou les deadlocks.
- **États** : machine à états explicite pour les protocoles (UART, I2C, bootloader) ; gestion des états d’erreur et des retours à un état connu.

---

## 2. Sécurité

- **Entrées** : valider et limiter les commandes reçues (longueur, caractères, plages de valeurs). Éviter les buffer overflows (sprintf → snprintf, strcpy → strncpy ou strlcpy).
- **Mise à jour firmware** : signature ou checksum du firmware ; rollback en cas d’échec de mise à jour ; zone de boot et zone d’application bien séparées.
- **Secrets** : ne pas stocker de clés en clair dans le code ; utiliser des zones protégées (secure storage) si le MCU le permet, ou des mécanismes de provisionnement sécurisé.

---

## 3. Maintenabilité

- **Conventions** : nommage (variables, fichiers), style (indentation, commentaires), règles de commit (messages clairs, pas de code commenté inutile).
- **Documentation** : README (build, flash, usage), schéma des modules, commentaires sur les algorithmes complexes et les contraintes temps réel.
- **Revue de code** : relecture par un pair pour détecter les bugs et améliorer la clarté ; checklist (erreurs, ressources, timeouts).

---

## Résumé

- **Robustesse** : timeouts, assertions, watchdog, machines à états.
- **Sécurité** : validation des entrées, mise à jour signée, gestion des secrets.
- **Maintenabilité** : conventions, documentation, revue de code.

---

## Tester sa compréhension

- **Scénarios** : [scenarios/robustesse-securite.md](scenarios/robustesse-securite.md) · **Réponses** : [reponses/robustesse-securite.md](reponses/robustesse-securite.md).

---

**Fin du parcours cours.** Revenir au [README principal](../../README.md) ou aux [projets avancés](../README.md).
