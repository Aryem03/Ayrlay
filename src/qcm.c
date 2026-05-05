#include "qcm.h"

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

QCM charger_qcm(const char *nom) { // on veut retourner une structure QCM
    QCM q;
    memset(&q, 0, sizeof(QCM));
    char path[300], buffer[512];
    // pour avoir le nom du fichier en caractere (path)
    snprintf(path, sizeof(path), "%s/%s.qcm", DOSSIER_DATA, nom); 
    FILE *f = fopen(path, "r");
    if (!f) {
        fprintf(stderr, "Impossible d'ouvrir : %s\n", path);
        return q;
    }
    fgets(q.nom, MAX_NOM, f); // on charge le nom du QCM dans le fichier puis les autres infos
    q.nom[strcspn(q.nom, "\n")] = 0; // tjr apres fgets
    fgets(buffer,sizeof(buffer),f); sscanf(buffer,"%d",&q.nb_questions); //robustesse
    fgets(buffer,sizeof(buffer),f); sscanf(buffer,"%d",&q.points_negatifs);
    fgets(buffer,sizeof(buffer),f); sscanf(buffer,"%d",&q.multi_reponses);
    fgets(buffer,sizeof(buffer),f); sscanf(buffer,"%d",&q.sequentiel);

    for (int i = 0; i < q.nb_questions; i++) { // PREMIERE BOUCLE : questions
        Question *qi = &q.questions[i]; //facilité d'écriture
        fgets(qi->enonce, 512, f);
        qi->enonce[strcspn(qi->enonce, "\n")] = 0;//apres fgets
        fgets(buffer,sizeof(buffer),f);
        sscanf(buffer, "%d", &qi->nb_reponses);
        for (int j = 0; j < qi->nb_reponses; j++) { // DEUXIEME BOUCLE : reponses
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
    // Ouvre le dossier contenant les fichiers QCM 
    DIR *d = opendir(DOSSIER_DATA);
    // Si le dossier n'existe pas ou ne peut pas être ouvert 
    if (!d) {
        printf("Aucun QCM disponible.\n");
        return 0;  // Aucun QCM trouvé
    }
    // Représente chaque élément (fichier/dossier) lu 
    struct dirent *entry;
    // Compteur du nombre de QCM valides trouvés 
    int count = 0;
    printf("\nQCM disponibles :\n");
    // Parcourt tous les fichiers du dossier 
    while ((entry = readdir(d)) != NULL && count < MAX_QUESTIONS) {
        // Cherche la dernière occurrence de '.' → début de l'extension 
        char *ext = strrchr(entry->d_name, '.');
        // Garde uniquement les fichiers avec extension ".qcm" 
        if (ext && strcmp(ext, ".qcm") == 0) {
            // Longueur du nom sans l'extension (.qcm) 
            int len = (int)(ext - entry->d_name);
            /* 
               Copie le nom sans ".qcm" dans noms[count]
               %.*s → permet de copier exactement 'len' caractères
               snprintf → évite les débordements (sécurisé)
            */
            snprintf(noms[count], MAX_NOM, "%.*s", len, entry->d_name);
            // Affiche le nom avec un numéro pour le choix utilisateur 
            printf("  %d. %s\n", count + 1, noms[count]);
            // Passe au QCM suivant 
            count++;
        }
    }
    // Ferme le dossier (obligatoire pour éviter fuite de ressources) 
    closedir(d);
    // Si aucun fichier .qcm n'a été trouvé 
    if (count == 0)
        printf("  (aucun QCM pour l'instant)\n");
    // Retourne le nombre de QCM disponibles 
    return count;
}

