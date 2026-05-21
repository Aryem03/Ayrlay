# Gestionnaire de QCM — Ayrlay

# Description
Bienvenue dans **Ayrlay** , une application en ligne de commande développée en langage C permettant aux enseignants de créer des QCM et aux étudiants de les passer et d'être notés automatiquement sur 20.

## Fonctionnalités

### Mode Enseignant (protégé par un mot de passe)  

* **Création d'un QCM**: Configurez un QCM avec son nom, ses questions et ses réponses.
* **Paramètres par QCM** : points négatifs, multi-réponses, mode séquentiel. 
* **Sauvegarde**: Export automatique dans un fichier '.qcm'.
* **Sécurité** :  Modification du mot de passe.

### Mode Étudiant

* **Liste des QCM** : Affichage automatique des questionnaires disponibles dans le dossier de sauvegarde.
* **Passage de test** : Répondez aux questions une par une.
* **Notation automatique** : Calcul et affichage direct de la note sur 20 à la fin du test.
* **Saut de question** : Possibilité de passer une question (si le mode non séquentiel est activé).

## Structure du projet


* **src/main.c** : Point d'entrée du programme et gestion du menu principal.
* **src/enseignant.c** : Implémente le mode enseignant, la fonction `scanf_secu` et la gestion du mot de passe.
* **src/etudiant.c** : Gère le mode étudiant, le passage du QCM et le calcul de la note.
* **src/qcm.c** : S'occupe de la sauvegarde, du chargement et du listage des fichiers QCM.
* **headers/qcm.h** : Déclare les structures, les constantes globales et les prototypes de base.
* **headers/enseignant.h** : Déclare les fonctions propres au mode enseignant.
* **headers/etudiant.h** : Déclare les fonctions propres au mode étudiant.
* **sauvegarde/** : Dossier créé automatiquement au lancement pour stocker les fichiers de configuration.
* **Makefile** : Script de compilation automatisé.

## Compilation et Exécution

### Prérequis
- Un compilateur C (comme `gcc`).
- L'Utilitaire `make`
### Étapes
1. Clonez le dépôt :
   ```bash
   https://github.com/Aryem03/Ayrlay.git
   cd Ayrlay
   ```
2. Compilez le projet (avec linux/Mac):   

* **Linux / Mac**:
```bash
make
```bash
3.Exécutez le programme :
```bash
./programme_quiz
```
**Pour Windows (avec MinGW)**
```bash
mingw32-make 
programme_quiz.exe
```
## Mot de passe par défaut
Un mot de passe est deja fourni si vous voulez directement faire les qcm, il suffit d'entrer:   "admin"

Sinon le mot de passe peut être modifié depuis le mode enseignant. Il est stocké dans 'sauvegarde/mdp.tkt'.

## QCM fournis

Trois QCM sont déjà fournis avec le projet pour permettre une démonstration immédiate :

| Nom | Sujet | Points négatifs | Multi-réponses | Séquentiel |
| :--- | :--- | :---: | :---: | :---: |
| IA | Intelligence Artificielle | Non | Oui | Non |
| Animaux | Animaux du monde | Oui | Non | Oui |

## Choix techniques

• "scanf_secu" - remplace "scanf" pour éviter les crashs en cas de saisie invalide (utilise "fgets" + "sscanf")
• "dirent.h" - bibliothèque standard POSIX pour lister les fichiers du dossier "sauvegarde/", compatible Linux/Mac. Gestion Windows via "#ifdef _WIN32"
• "fgets" + "sscanf" - utilisés systématiquement pour la lecture de fichiers, plus robustes que "fscanf" seul
• "CREER_DOSSIER" - macro qui crée automatiquement le dossier "sauvegarde/" au premier lancement

## Contributeurs

**EQUIPE :** Alaa OUAZBIR & Aryem ZITOUNE


Merci d'utiliser **Ayrlay** pour crée et faire les qcm !
(Un projet pour CYTECH)
