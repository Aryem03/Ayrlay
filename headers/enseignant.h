#ifndef ENSEIGNANT_H
#define ENSEIGNANT_H

#include"qcm.h"

#define MDP_DEFAULT "admin"

#define MDP_FILE  "sauvegarde/mdp.tkt"


int  verifier_mdp(const char *saisie);
void changer_mdp();
void saisir_qcm();
void menu_enseignant();


#endif
