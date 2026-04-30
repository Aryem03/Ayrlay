#include"qcm.h"
#include"enseignant.h"

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

int verifier_mdp(const char *saisie) {
    char mdp[64];
    strcpy(mdp, MDP_DEFAULT); //Par défaut tu mets le mdp = admin
    FILE *f = fopen(MDP_FILE, "r"); // on lit le fichier qui doit contenir mdp
    if (f) {
        fgets(mdp, sizeof(mdp), f); // si le fichier existe,mdp = contenu fichier
        mdp[strcspn(mdp, "\n")] = 0;
        fclose(f);
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
    printf("Nom du QCM (sans espaces) : ");
    fgets(q.nom, MAX_NOM, stdin);
    q.nom[strcspn(q.nom, "\n")] = 0;
    q.points_negatifs = scanf_secu("Points negatifs ? (0/1) : ", 0, 1);
    q.multi_reponses  = scanf_secu("Multi-reponses ?  (0/1) : ", 0, 1);
    q.sequentiel      = scanf_secu("Sequentiel ?      (0/1) : ", 0, 1);
    q.nb_questions    = scanf_secu("Nombre de questions : ", 1, MAX_QUESTIONS);
    for (int i = 0; i < q.nb_questions; i++) {
        Question *qi = &q.questions[i];
        printf("\nQuestion %d : ", i+1);
        fgets(qi->enonce, 512, stdin);
        qi->enonce[strcspn(qi->enonce, "\n")] = 0;
        qi->nb_reponses = scanf_secu("  Nb reponses (2-8) : ", 2, MAX_REPONSES);
        for (int j = 0; j < qi->nb_reponses; j++) {
            printf("  Reponse %d : ", j+1);
            fgets(qi->reponses[j].texte, 256, stdin);
            qi->reponses[j].texte[strcspn(qi->reponses[j].texte, "\n")] = 0;
            qi->reponses[j].est_correcte =
                scanf_secu("  Correcte ? (0/1) : ", 0, 1);
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
