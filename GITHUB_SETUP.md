# Mettre le projet sur GitHub

Dépôt cible : **[Bouro-Souebou/Ingenieur-Systeme-Embarque-Logiciel](https://github.com/Bouro-Souebou/Ingenieur-Systeme-Embarque-Logiciel)**

---

## Dépôt déjà créé – Commandes à lancer

Ouvrez un **terminal** dans le dossier du projet (celui qui contient `01-fondements`, `04-peripheriques`, `PLAN_PROGRESSION.md`), puis exécutez :

```bash
git init
git add .
git commit -m "Initial commit: formation Ingénieur système embarqué logiciel"
git branch -M main
git remote add origin https://github.com/Bouro-Souebou/Ingenieur-Systeme-Embarque-Logiciel.git
git push -u origin main
```

Si une fenêtre ou un message demande de vous connecter à GitHub, utilisez votre compte (ou un [Personal Access Token](https://github.com/settings/tokens) comme mot de passe).

---

## Détail des étapes (si besoin)

---

## 1. Créer un dépôt sur GitHub

1. Allez sur [github.com](https://github.com) et connectez-vous.
2. Cliquez sur **« New »** (nouveau dépôt).
3. Choisissez un **nom** (ex. `Ingenieur-Systeme-Embarque-Logiciel` ou `formation-embarque`).
4. Laissez **« Public »** (ou « Private » si vous préférez).
5. **Ne cochez pas** « Add a README » (le projet en a déjà un).
6. Cliquez sur **« Create repository »**.

---

## 2. Ouvrir un terminal dans le dossier du projet

- Dans **Cursor** : menu **Terminal → New Terminal** (ou `` Ctrl+` ``).
- Vérifiez que vous êtes dans le bon dossier (celui qui contient `01-fondements`, `04-peripheriques`, `PLAN_PROGRESSION.md`, etc.).  
  Si ce n’est pas le cas :  
  `cd "Ingenieur_Systeme_Embarque_Logiciel"`  
  (ou le chemin complet vers ce dossier.)

---

## 3. Initialiser Git et faire le premier commit

Exécutez ces commandes **une par une** :

```bash
git init
git add .
git status
git commit -m "Initial commit: formation Ingénieur système embarqué logiciel"
```

---

## 4. Branche principale (si besoin)

Si Git vous demande d’utiliser une branche `main` au lieu de `master` :

```bash
git branch -M main
```

---

## 5. Lier le dépôt GitHub et pousser

Pour ce projet, l’URL du dépôt est déjà configurée :

```bash
git remote add origin https://github.com/Bouro-Souebou/Ingenieur-Systeme-Embarque-Logiciel.git
git push -u origin main
```

(Utilisez `master` au lieu de `main` si vous n’avez pas fait l’étape 4.)

---

## 6. Authentification GitHub

- Si une **fenêtre de connexion** s’ouvre : connectez-vous à GitHub (navigateur ou token).
- Si vous utilisez **HTTPS** et que le mot de passe est refusé : GitHub exige un **Personal Access Token** (PAT) à la place du mot de passe.  
  Création : GitHub → **Settings → Developer settings → Personal access tokens → Generate new token** ; cochez au minimum `repo`, puis utilisez ce token comme mot de passe lors du `git push`.

---

Une fois ces étapes faites, tout le contenu du projet (cours, scénarios, réponses, ressources) sera sur votre dépôt GitHub.
