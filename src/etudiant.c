#include "etudiant.h"


float calculer_note(QCM *q, int reponses[MAX_QUESTIONS][MAX_REPONSES]) {
    float pts = 20.0f / q->nb_questions;
    float total = 0.0f;
    for (int i = 0; i < q->nb_questions; i++) {
        Question *qi = &q->questions[i];
        int bonne = 1;
        if (reponses[i][0] == -1) continue;
        for (int j = 0; j < qi->nb_reponses; j++) {
            if (reponses[i][j] != qi->reponses[j].est_correcte) {
                bonne = 0;
                break;
            }
        }
        if (bonne) total += pts;
        else if (q->points_negatifs) total -= pts;
    }
    if (total < 0.0f) return 0.0f;
    return total;
}



void passer_qcm(QCM *q) {
    int reponses[MAX_QUESTIONS][MAX_REPONSES];
    memset(reponses, 0, sizeof(reponses));
    
    printf("\n-------------------------");
    printf("\nParametres du QCM : \n\n");
    printf("Points negatifs : %s\n", q->points_negatifs ? "Oui" : "Non");
    printf("Multi-reponses  : %s\n", q->multi_reponses ? "Oui" : "Non");
    printf("Mode sequentiel (Reponse Obligatoire?): %s\n", q->sequentiel ? "Oui" : "Non");
    printf("-------------------------\n\n");
    
    printf("\n=== Debut du QCM : %s ===\n", q->nom);
    printf("Ce QCM contient %d question(s). Bonne chance !\n", q->nb_questions);

    for (int i = 0; i < q->nb_questions; i++) {
        Question *qi = &q->questions[i];

        
        printf("\n--- Question %d sur %d ---\n", i+1, q->nb_questions);
        printf("%s\n", qi->enonce);
        printf("\nReponses possibles :\n");

        
        for (int j = 0; j < qi->nb_reponses; j++){
            printf("  %d. %s\n", j+1, qi->reponses[j].texte);
        }
        if (!q->sequentiel) printf("  0. Passer cette question\n");

        if (q->multi_reponses) {
            printf("\nAttention : plusieurs reponses peuvent etre correctes.\n");
            printf("Entrez vos choix un par un (0 pour terminer) :\n");
            int c, nb_coches = 0;
            while (nb_coches < qi->nb_reponses) {
                c = scanf_secu("> Choix : ", 0, qi->nb_reponses);
                if (c == 0) {
                    if (q->sequentiel && nb_coches == 0) {
                        printf("Reponse obligatoire : vous devez cocher au moins une reponse.\n");
                        continue;
                    }
                    break;
                }
                if (reponses[i][c-1] == 1) {
                    printf("Deja cochee. Choisissez une autre reponse ou tapez 0.\n");
                    continue;
                }
                reponses[i][c-1] = 1;
                nb_coches++;
            }
            
            int bonne = 1;
            for (int k = 0; k < qi->nb_reponses; k++) {
                if (reponses[i][k] != qi->reponses[k].est_correcte) {
                    bonne = 0;
                    break;
                }
            }
            if (bonne) printf("\nBonne reponse !\n");
            else printf("\nMauvaise reponse.\n");
        } 
        else {
            
            int min;
            if (q->sequentiel) min=1;
            else min = 0;
            int c = scanf_secu("\nEntrez le numero de votre reponse : ", min, qi->nb_reponses);
            if (c == 0){
                printf("Question passee.\n");
                reponses[i][0] = -1;
            }
            else{
                reponses[i][c-1] = 1; //reponse choisie par l'eleve
                if (qi->reponses[c-1].est_correcte) printf("\nBonne reponse !\n");
                else printf("\nMauvaise reponse.\n");
            }
        }
    }

    float note = calculer_note(q, reponses);
    printf("\n=====================================\n");
    printf("  QCM termine ! Votre note : %.2f / 20\n", note);
    printf("=====================================\n");
}


void menu_etudiant() {
    char noms[MAX_QUESTIONS][MAX_NOM];
    int count = lister_qcm(noms);
    if (count == 0) return;

    printf("  0. Retour au menu\n");
    int choix = scanf_secu("Choisissez un QCM : ", 0, count);
    if (choix == 0) return;

    QCM q = charger_qcm(noms[choix - 1]);
    if (q.nb_questions == 0) {
        printf("Erreur au chargement du QCM.\n");
        return;
    }
    passer_qcm(&q);
}
