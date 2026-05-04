#ifndef ETUDIANT_H
#define ETUDIANT_H

#include "qcm.h"

void menu_etudiant(void);
void passer_qcm(QCM *q);
float calculer_note(QCM *q, int reponses[MAX_QUESTIONS][MAX_REPONSES]);

#endif
