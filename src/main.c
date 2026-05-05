#include "qcm.h"
#include "enseignant.h"
#include "etudiant.h"


int main(void) {
    CREER_DOSSIER;     
    int choix;
    do {
        printf("\n+=======================+\n");
        printf("|   Gestionnaire QCM    |\n");
        printf("+=======================+\n");
        printf("| 1. Mode enseignant    |\n");
        printf("| 2. Mode etudiant      |\n");
        printf("| 0. Quitter            |\n");
        printf("+-----------------------+\n");
        choix = scanf_secu("Votre choix : ", 0, 2);
        if (choix == 1) menu_enseignant();
        else if (choix == 2) menu_etudiant();
    } while (choix != 0);
    return 0;
}
