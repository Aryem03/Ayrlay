# Gestionnaire de QCM — Ayrlay
# Description
Bienvenue dans **Ayrlay** , une application en ligne de commande développée en langage C permettant aux enseignants de créer des QCM et aux étudiants de les passer et d'être notés automatiquement sur 20.
## Fonctionnalités
     * Mode Enseignant * :
- ** Création d'un QCM avec nom, questions et réponses **
- ** Paramètres par QCM : points négatifs, multi-réponses, mode séquentiel **
- ** Sauvegarde automatique dans un fichier '.qcm' **
- **  Modification du mot de passe **
     ** Mode Étudiant **:
- ** Liste automatique des QCM disponibles **
- ** Passage du QCM question par question **
- ** Calcul et affichage de la note sur 20 **
- ** Possibilité de passer une question (si mode non séquentiel) **

## Structure du projet

# Ayrlay/
# src/       : dossier qui contient les fonctions .c
- ** main.c ** :         - point d'entrée, menu principal
- ** enseignant.c ** :   - mode enseignant, scanf_secu, gestion mot de passe
- ** etudiant.c ** :     - mode étudiant, passage du QCM, calcul de note
- ** qcm.c ** :          - sauvegarde, chargement et listage des QCM
# headers/   : dossier qui contient les fonctions .h
- **   qcm.h ** :         - structures, constantes, déclarations
- ** enseignant.h **:     - déclarations mode enseignant
- ** etudiant.h ** :      - déclarations mode étudiant
- ** sauvegarde/ ** :  	  - dossier créé automatiquement au lancement
	- IA.qcm           
	- Animaux.qcm
	-...
** Makefile **


