#include "etudiant.h"

// calculer_note()

float calculer_note(QCM *q, int reponses[MAX_QUESTIONS][MAX_REPONSES]) {
    // Points attribués par question — répartition uniforme sur 20
    float pts = 20.0f / q->nb_questions;
    // Note accumulée au fil des questions
    float total = 0.0f;
    for (int i = 0; i < q->nb_questions; i++) {
        Question *qi = &q->questions[i];
        // On part du principe que la réponse est bonne
        int bonne = 1;
        // On compare case par case ce que l'étudiant a coché avec les bonnes réponses
        for (int j = 0; j < qi->nb_reponses; j++) {
            // Dès qu'une case diffère → la question est fausse, inutile de continuer
            if (reponses[i][j] != qi->reponses[j].est_correcte) {
                bonne = 0;
                break;
            }
        }
        if (bonne)
            // Bonne réponse -> on gagne les points
            total += pts;
        else if (q->points_negatifs)
            // Mauvaise réponse ET points négatifs activés -> on perd les points
            total -= pts;
        // Mauvaise réponse sans points négatifs -> on ne fait rien
    }
    // La note ne peut jamais être négative
    if (total < 0.0f) return 0.0f;
    return total;
}


// passer_qcm()

void passer_qcm(QCM *q) {
    // Stocke les choix de l'étudiant : reponses[i][j] = 1 si la réponse j de la question i a été cochée
    int reponses[MAX_QUESTIONS][MAX_REPONSES];
    // Initialise tout à 0 — question non répondue = toutes les cases à 0
    memset(reponses, 0, sizeof(reponses));

    printf("\n=== Debut du QCM : %s ===\n", q->nom);
    printf("Ce QCM contient %d question(s). Bonne chance !\n", q->nb_questions);

    for (int i = 0; i < q->nb_questions; i++) {
        Question *qi = &q->questions[i];

        // Affiche la question avec sa position dans le QCM
        printf("\n--- Question %d sur %d ---\n", i+1, q->nb_questions);
        printf("%s\n", qi->enonce);
        printf("\nReponses possibles :\n");

        // Affiche les réponses numérotées à partir de 1
        for (int j = 0; j < qi->nb_reponses; j++)
            printf("  %d. %s\n", j+1, qi->reponses[j].texte);

        // Propose le skip uniquement si reponse non obligatoire
        if (!q->sequentiel)
            printf("  0. Passer cette question\n");

        if (q->multi_reponses) {
            // Mode multi : l'étudiant coche plusieurs réponses, 0 pour terminer
            printf("\nAttention : plusieurs reponses peuvent etre correctes.\n");
            printf("Entrez vos choix un par un (0 pour terminer) :\n");
            int c, nb_coches = 0;
            while (nb_coches < qi->nb_reponses) {
                c = scanf_secu("> Choix : ", 0, qi->nb_reponses);
                if (c == 0) {
                    // Reponse obligatoire : interdire le skip si aucune reponse cochée
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
        } else {
            // min=1 si reponse obligatoire, min=0 si skip autorisé
            int min = q->sequentiel ? 1 : 0;
            int c = scanf_secu("\nEntrez le numero de votre reponse : ", min, qi->nb_reponses);
            // c==0 signifie skip → reponses[i] reste à 0 partout
            if (c == 0) printf("Question passee.\n");
            else reponses[i][c-1] = 1;
        }
    }

    // Calcule et affiche la note sur 20
    float note = calculer_note(q, reponses);
    printf("\n=====================================\n");
    printf("  QCM termine ! Votre note : %.2f / 20\n", note);
    printf("=====================================\n");
}


// menu_etudiant()

void menu_etudiant(void) {
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
