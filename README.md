# Gestionnaire de QCM - Ayrlay

## Description
Bienvenue dans **Ayrlay** , une application en ligne de commande développée en langage C permettant aux enseignants de créer des QCMs et aux étudiants de les passer et d'être notés automatiquement sur 20.

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
* **Saut de question** : Possibilité de passer une question (si le mode séquentiel est désactivé).

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
- Sur Windows : installer [MinGW](https://www.mingw-w64.org/)
  
### Étapes

1. Clonez le dépôt :
   ```bash
   https://github.com/Aryem03/Ayrlay.git
   cd Ayrlay
   ```
   
2. Compilez le projet :   
  
  **Linux / Mac**:
  ```bash
  make
  ```
  
  **Windows**
  ```bash
  mingw32-make 
  ```
  ou 
  ```bash
  make
  ```


3.Exécutez le programme :
  ```bash
  ./qcm
  ```

### Compiler et exécuter en meme temps si possible 

```bash
make run
```


## Mot de passe par défaut
Un mot de passe est deja fourni si vous voulez directement faire les qcms, il suffit d'entrer: "admin"
Sinon le mot de passe peut être modifié depuis le mode enseignant. Il sera stocké dans 'sauvegarde/mdp.tkt'.

## QCM fournis

Trois QCM sont déjà fournis avec le projet pour permettre une démonstration immédiate :

| Nom | Points négatifs | Multi-réponses | Séquentiel |
| :---: | :---: | :---: | :---: |
| Sport | Oui | Non | Non |
| Capitale | Non | Non | Oui |
| Gastronomie | Non | Oui | Oui |

## Choix techniques

* **"scanf_secu"**: remplace `scanf` direct pour toutes les saisies 
  numériques. Utilise `fgets` + `sscanf` + vérification des bornes. 
  Évite les crashs et boucles infinies sur entrée invalide.
* **Sécurisation des saisies texte** : toutes les chaînes (nom QCM, 
  énoncé, réponse, mot de passe) passent par `fgets` avec vérification 
  de longueur, interdiction des caractères spéciaux et vidage de `stdin` 
  si le buffer est plein.
* **1 fichier = 1 QCM** : chaque QCM est stocké dans un fichier `.qcm` 
  indépendant. Permet de lister, charger et ajouter des QCM facilement 
  sans toucher aux autres.
* **"dirent.h"**: bibliothèque standard POSIX pour lister les fichiers du dossier "sauvegarde/", compatible Linux/Mac. Gestion Windows via "#ifdef _WIN32".
* **"fgets" + "sscanf"**: utilisés systématiquement pour la lecture de fichiers, plus robustes que "fscanf" seul.
* **"CREER_DOSSIER"**: macro qui crée automatiquement le dossier "sauvegarde/" au premier lancement.

## Contributeurs

**EQUIPE :** Alaa OUAZBIR & Aryem ZITOUNE


Merci d'utiliser **Ayrlay** pour créer et faire des qcms !
