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

### Linux / Mac
```bash
make
./programme_quiz

