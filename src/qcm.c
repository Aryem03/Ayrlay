#include "qcm.h"

int sauvegarder_qcm(const QCM *q) {
    char chemin[300];
    snprintf(chemin, sizeof(chemin), "%s/%s.qcm", DOSSIER_DATA, q->nom);
    
    FILE *test = fopen(chemin, "r");
    if (test != NULL) {
        fclose(test);
        printf("Erreur : un QCM nomme '%s' existe deja.\n", q->nom);
        return -1;
    }
    
    FILE *f = fopen(chemin, "w");

    if (!f) {
        perror("sauvegarder_qcm"); 
        return -1; 
    }
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

QCM charger_qcm(const char *nom) { 
    QCM q = {0};
    char chemin[300], buffer[512];
    // Construit le chemin complet : "sauvegarde/nom_du_qcm.qcm"
    snprintf(chemin, sizeof(chemin), "%s/%s.qcm", DOSSIER_DATA, nom); 
    FILE *f = fopen(chemin, "r");
    if (!f) {
        printf("Impossible d'ouvrir : %s\n", chemin);
        return q;
    }
    fgets(q.nom, MAX_NOM, f); 
    q.nom[strcspn(q.nom, "\n")] = 0; 
    // fgets lit la ligne entière, sscanf extrait l'entier
    // Plus robuste que fscanf seul qui peut décaler le buffer
    fgets(buffer,sizeof(buffer),f); sscanf(buffer,"%d",&q.nb_questions); 
    fgets(buffer,sizeof(buffer),f); sscanf(buffer,"%d",&q.points_negatifs);
    fgets(buffer,sizeof(buffer),f); sscanf(buffer,"%d",&q.multi_reponses);
    fgets(buffer,sizeof(buffer),f); sscanf(buffer,"%d",&q.sequentiel);

    for (int i = 0; i < q.nb_questions; i++) { 
        Question *qi = &q.questions[i];
        fgets(qi->enonce, 512, f);
        qi->enonce[strcspn(qi->enonce, "\n")] = 0;
        fgets(buffer,sizeof(buffer),f);
        sscanf(buffer, "%d", &qi->nb_reponses);
        
        for (int j = 0; j < qi->nb_reponses; j++) {
            fgets(qi->reponses[j].texte, 256, f);
            qi->reponses[j].texte[strcspn(qi->reponses[j].texte,"\n")]=0;
            fgets(buffer,sizeof(buffer),f);
            sscanf(buffer,"%d",&qi->reponses[j].est_correcte);
        }
    }
    fclose(f);
    return q;
}

int lister_qcm(char noms[MAX_QUESTIONS][MAX_NOM]) {
    DIR *d = opendir(DOSSIER_DATA);
    if (!d) {
        printf("Aucun QCM disponible.\n");
        return 0;  
    }
    struct dirent *entry;
    int count = 0;
    printf("\nQCM disponibles :\n");
    // Parcourt tous les fichiers du dossier 
    while ((entry = readdir(d)) != NULL && count < MAX_QUESTIONS) {
        char *nom = entry->d_name;
        int len = strlen(nom);
        if (len < 5) continue;  
        if (len - 4 >= MAX_NOM) continue;

        // on prend juste le nom du qcm pour l'afficher ensuite
        if (strcmp(nom + len - 4, ".qcm") == 0) { 
            strncpy(noms[count], nom, len - 4); 
            noms[count][len - 4] = '\0';  
            printf("  %d. %s\n", count + 1, noms[count]); 
            count++;
        }
    } 
    closedir(d);
    if (count == 0)
        printf("  (aucun QCM pour l'instant)\n"); 
    return count;
}


