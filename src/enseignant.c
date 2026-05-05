#include"qcm.h"
#include"enseignant.h"


/*
int scanf_secu (const char *prompt, int min, int max) {
    char buffer[64];
    int val;
    while (1) {
        printf("%s", prompt);
        if (!fgets(buffer, sizeof(buffer), stdin)) continue;
        if (sscanf(buffer, "%d", &val) == 1
                && val >= min && val <= max)
            return val;
        printf("Invalide. Entrez entre %d et %d : ", min, max);
    }
}
*/

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
        
        if (sscanf(buffer, "%d", &val) == 1
                && val >= min && val <= max)
            return val;
        printf("Invalide. Entrez entre %d et %d : ", min, max);
    }
}

int verifier_mdp(const char *saisie) {
    char mdp[64];
    strcpy(mdp, MDP_DEFAULT); //Par défaut tu mets le mdp = admin
    FILE *f = fopen(MDP_FILE, "r"); // on lit le fichier qui doit contenir mdp
    if (f) {
        fgets(mdp, sizeof(mdp), f); // si le fichier existe,mdp = contenu fichier
        mdp[strcspn(mdp, "\n")] = 0;
        fclose(f);
        // Si le fichier est vide → revenir au mot de passe par défaut
        if (mdp[0] == '\0')
            strcpy(mdp, MDP_DEFAULT);
    }
    return strcmp(saisie, mdp) == 0; // on compare la saisie et le vrai mdp
} // si 0=0 : vrai sinon faux (0=0 veut dire que saisie=mdp)


void changer_mdp(void) {
    char nouveau[64];
    printf("Nouveau mot de passe : ");
    fgets(nouveau, sizeof(nouveau), stdin); //stocke dans la chaine
    nouveau[strcspn(nouveau, "\n")] = 0; //on enleve tjr le \n du fgets

    FILE *f = fopen(MDP_FILE, "w");
    if (!f) { 
		perror("changer_mdp"); //si le fichier n'existe pas : erreur
		return; 
	}
	
    fprintf(f, "%s\n", nouveau);
    fclose(f);
    printf("Mot de passe modifie.\n");
}

void saisir_qcm(void) {
    QCM q;
    memset(&q, 0, sizeof(QCM));

    // Boucle jusqu'à avoir un nom valide
    do {
        printf("Nom du QCM (lettres, chiffres et _ uniquement) : ");
        fgets(q.nom, MAX_NOM, stdin);
        q.nom[strcspn(q.nom, "\n")] = 0;

        if (q.nom[0] == '\0') {
            printf("Erreur : le nom ne peut pas etre vide.\n");
            continue;
        }

        // Vérifier que le nom ne contient que des caractères autorisés
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

        // Énoncé non vide
        do {
            printf("\nQuestion %d : ", i+1);
            fgets(qi->enonce, 512, stdin);
            qi->enonce[strcspn(qi->enonce, "\n")] = 0;
            if (qi->enonce[0] == '\0')
                printf("Erreur : l'enonce ne peut pas etre vide.\n");
        } while (qi->enonce[0] == '\0');

        qi->nb_reponses = scanf_secu("  Nb reponses (2-8) : ", 2, MAX_REPONSES);

        int nb_correctes = 0;
        for (int j = 0; j < qi->nb_reponses; j++) {

            // Texte de réponse non vide
            do {
                printf("  Reponse %d : ", j+1);
                fgets(qi->reponses[j].texte, 256, stdin);
                qi->reponses[j].texte[strcspn(qi->reponses[j].texte, "\n")] = 0;
                if (qi->reponses[j].texte[0] == '\0')
                    printf("Erreur : la reponse ne peut pas etre vide.\n");
            } while (qi->reponses[j].texte[0] == '\0');

            int val = scanf_secu("  Correcte ? (0/1) : ", 0, 1);
            qi->reponses[j].est_correcte = val;
            if (val == 1) nb_correctes++;
        }

        // Vérifier qu'au moins une réponse est correcte
        if (nb_correctes == 0) {
            printf("Erreur : au moins une reponse doit etre correcte. Recommencez cette question.\n");
            memset(qi, 0, sizeof(Question));
            i--;
            continue;
        }

        // Si multi-reponses desactive : exactement une seule bonne reponse autorisee
        if (!q.multi_reponses && nb_correctes > 1) {
            printf("Erreur : une seule bonne reponse autorisee. Recommencez cette question.\n");
            memset(qi, 0, sizeof(Question));
            i--;
            continue;
        }

        // Si multi-reponses desactive : au moins une reponse incorrecte requise
        if (!q.multi_reponses && nb_correctes == qi->nb_reponses) {
            printf("Erreur : au moins une reponse doit etre incorrecte. Recommencez cette question.\n");
            memset(qi, 0, sizeof(Question));
            i--;
            continue;
        }
    }
    sauvegarder_qcm(&q);
}

void menu_enseignant(void) {
    
//Mot de passe
    char saisie[64];
    printf("Mot de passe : ");
    fgets(saisie, sizeof(saisie), stdin);
    saisie[strcspn(saisie, "\n")] = 0;
    if (!verifier_mdp(saisie)) {
        printf("Mot de passe incorrect.\n"); return;
    }

//Menu du mode enseignant
    int choix;
    do {
        printf("\n-- Menu Enseignant --\n");
        printf("1. Creer un QCM\n2. Changer mdp\n0. Retour\n");
        choix = scanf_secu ("Choix : ", 0, 2);
        if (choix == 1) saisir_qcm();
        else if (choix == 2) changer_mdp();
    } while (choix != 0);
}              
