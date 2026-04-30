#include"qcm.h"

int sauvegarder_qcm(const QCM *q) {
    char path[300];
    snprintf(path, sizeof(path), "%s/%s.qcm", DOSSIER_DATA, q->nom);
    FILE *f = fopen(path, "w");

    if (!f) { perror("sauvegarder_qcm"); return -1; }
    fprintf(f, "%s\n", q->nom);
    fprintf(f, "%d\n", q->nb_questions);
    fprintf(f, "%d\n", q->points_negatifs);
    fprintf(f, "%d\n", q->multi_reponses);
    fprintf(f, "%d\n", q->sequentiel);

    for (int i = 0; i < q->nb_questions; i++) {
        const Question *qi = &q->questions[i];
        fprintf(f, "%s\n", qi->enonce);
        fprintf(f, "%d\n", qi->nb_reponses);
        for (int j = 0; j < qi->nb_reponses; j++) {
            fprintf(f, "%s\n", qi->reponses[j].texte);
            fprintf(f, "%d\n", qi->reponses[j].est_correcte);
        }
    }
    fclose(f);
    return 0;
}
