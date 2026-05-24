#include"qcm.h"
#include"enseignant.h"


int scanf_secu(const char *prompt, int min, int max) {
    char buffer[64];
    int val;
    while (1) {
        printf("%s", prompt);
        if (!fgets(buffer, sizeof(buffer), stdin)) continue;
        
        // Vider le buffer si la ligne était trop longue
        if (buffer[strlen(buffer)-1] != '\n') {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
        
        if (sscanf(buffer, "%d", &val) == 1 && val >= min && val <= max)
            return val;
        printf("Invalide. Entrez entre %d et %d : ", min, max);
    }
}

int verifier_mdp(const char *saisie) {
    char mdp[64];
    strcpy(mdp, MDP_DEFAULT); 
    FILE *f = fopen(MDP_FILE, "r"); 
    if (f) {
        fgets(mdp, sizeof(mdp), f); // mdp = contenu fichier
        mdp[strcspn(mdp, "\n")] = 0;
        fclose(f);
        if (mdp[0] == '\0') strcpy(mdp, MDP_DEFAULT);
    }
    return strcmp(saisie, mdp) == 0; 
}

void changer_mdp() {
    char nouveau[64];
	do{
	    printf("Nouveau mot de passe : ");
	    fgets(nouveau, sizeof(nouveau), stdin); //stocke dans la chaine
	    nouveau[strcspn(nouveau, "\n")] = 0; 

		// Si le buffer est plein, vider le reste de stdin
        if (strlen(nouveau) >= 63) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            nouveau[0] = '\0';
            printf("Erreur : 20 caracteres maximum.\n");
            continue;
        }

        if (nouveau[0] == '\0') {
            printf("Erreur : le mot de passe ne peut pas etre vide.\n");
        } 
        else if (strlen(nouveau) > 20) {
            printf("Erreur : 20 caracteres maximum.\n");
            nouveau[0] = '\0';
        }
        
    } while (nouveau[0] == '\0');

    FILE *f = fopen(MDP_FILE, "w");
    if (!f) { 
		perror("changer_mdp"); 
		return; 
	}
	
    fprintf(f, "%s\n", nouveau);
    fclose(f);
    printf("Mot de passe modifie.\n");
}

void saisir_qcm() {
    QCM q = {0};

    // Boucle jusqu'à avoir un nom valide
    do {
        printf("Nom du QCM (lettres, chiffres et _ uniquement) : ");
        fgets(q.nom, MAX_NOM, stdin);
        q.nom[strcspn(q.nom, "\n")] = 0;

        if (strlen(q.nom) >= MAX_NOM - 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            q.nom[0] = '\0';
            printf("Erreur : nom trop long (%d caracteres max).\n", MAX_NOM - 1);
            continue;
        }

        if (q.nom[0] == '\0') {
            printf("Erreur : le nom ne peut pas etre vide.\n");
            continue;
        }

        int nom_valide = 1;
        for (int k = 0; q.nom[k] != '\0'; k++) {
            unsigned char c = (unsigned char)q.nom[k];
            if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
                  (c >= '0' && c <= '9') || c == '_' || c >= 128)) {
                nom_valide = 0;
                break;
            }
        }
        if (!nom_valide) {
            printf("Erreur : caracteres interdits. Lettres, chiffres et _ uniquement.\n");
            q.nom[0] = '\0';
        }
    } while (q.nom[0] == '\0');

    q.points_negatifs = scanf_secu("Points negatifs ?     (0/1) : ", 0, 1);
    q.multi_reponses  = scanf_secu("Multi-reponses ?      (0/1) : ", 0, 1);
    q.sequentiel      = scanf_secu("Reponse obligatoire ? (0/1) : ", 0, 1);
    q.nb_questions    = scanf_secu("Nombre de questions : ", 1, MAX_QUESTIONS);

    for (int i = 0; i < q.nb_questions; i++) {
        Question *qi = &q.questions[i];

         // Boucle permettant d'avoir des énoncés de questions valides 
        do {
            printf("\nQuestion %d : ", i+1);
            
            fgets(qi->enonce, 512, stdin);
            qi->enonce[strcspn(qi->enonce, "\n")] = 0;
            
            if (strlen(qi->enonce) >= 511) {
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                qi->enonce[0] = '\0';
                printf("Erreur : enonce trop long (100 caracteres max).\n");
                continue;
            }

			if (strlen(qi->enonce) > 100) {
                printf("Erreur : enonce trop long (100 caracteres max).\n");
                qi->enonce[0] = '\0';
            }

            if (qi->enonce[0] == '\0')
                printf("Erreur : l'enonce ne peut pas etre vide.\n");
        } while (qi->enonce[0] == '\0');

        qi->nb_reponses = scanf_secu("  Nb reponses (2-8) : ", 2, MAX_REPONSES);

        int nb_correctes = 0;
        for (int j = 0; j < qi->nb_reponses; j++) {

            //  Boucle permettant d'avoir des réponses remplies valides + indiquer si correcte ou non
            do {
                printf("  Reponse %d : ", j+1);
                fgets(qi->reponses[j].texte, 256, stdin);
                qi->reponses[j].texte[strcspn(qi->reponses[j].texte, "\n")] = 0;
                
                if (strlen(qi->reponses[j].texte) >= 255) {
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF);
                    qi->reponses[j].texte[0] = '\0';
                    printf("Erreur : reponse trop longue (60 caracteres max).\n");
                    continue;
                }
                
                if (strlen(qi->reponses[j].texte) > 60) {
                    printf("Erreur : reponse trop longue (60 caracteres max).\n");
                    qi->reponses[j].texte[0] = '\0';
                }

                if (qi->reponses[j].texte[0] == '\0'){
                    printf("Erreur : la reponse ne peut pas etre vide.\n");
                }
            } while (qi->reponses[j].texte[0] == '\0');

            int val = scanf_secu("  Correcte ? (0/1) : ", 0, 1);
            qi->reponses[j].est_correcte = val;
            if (val == 1) nb_correctes++;
        }

        if (nb_correctes == 0) {
            printf("Erreur : au moins une reponse doit etre correcte. Recommencez cette question.\n");
            memset(qi, 0, sizeof(Question));
            i--;
            continue;
        }

        if (!q.multi_reponses && nb_correctes > 1) {
            printf("Erreur : une seule bonne reponse autorisee. Recommencez cette question.\n");
            memset(qi, 0, sizeof(Question));
            i--;
            continue;
        }
		
        if (!q.multi_reponses && nb_correctes == qi->nb_reponses) {
            printf("Erreur : au moins une reponse doit etre incorrecte. Recommencez cette question.\n");
            memset(qi, 0, sizeof(Question));
            i--;
            continue;
        }
    }
    if (sauvegarder_qcm(&q) == -1) {
        printf("Le QCM n'a pas ete sauvegarde.\n");
    } 
    else {
        printf("QCM sauvegarde avec succes !\n");
    }
}

void menu_enseignant() {
    char saisie[64];
    printf("Mot de passe : ");
    fgets(saisie, sizeof(saisie), stdin);
    saisie[strcspn(saisie, "\n")] = 0;

	if (strlen(saisie) >= 63) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
	
    if (!verifier_mdp(saisie)) {
        printf("Mot de passe incorrect.\n"); return;
    } 
    int choix;
    do {
        printf("\n-- Menu Enseignant --\n");
        printf("1. Creer un QCM\n2. Changer mdp\n0. Retour\n");
        choix = scanf_secu ("Choix : ", 0, 2);
        if (choix == 1) saisir_qcm();
        else if (choix == 2) changer_mdp();
    } while (choix != 0);
}              
