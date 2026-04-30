#ifndef QCM_H
#define QCM_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h> // pour ouvrir et fermer dossier 

#ifdef _WIN32
    #include <direct.h>
    #define CREER_DOSSIER _mkdir("sauvegarde")
#else
    #include <sys/stat.h>
    #define CREER_DOSSIER mkdir("sauvegarde", 0777)
#endif
//mettre CREER_DOSSIER dans le main

#define MAX_REPONSES  8
#define MAX_QUESTIONS 50
#define MAX_NOM       64
#define DOSSIER_DATA  "sauvegarde"


typedef struct {
    char texte[256];
    int  est_correcte;   /* 1 = vraie, 0 = fausse */
} Reponse;

typedef struct {
    char    enonce[512];
    Reponse reponses[MAX_REPONSES];
    int     nb_reponses;
} Question;

typedef struct {
    char     nom[MAX_NOM];
    Question questions[MAX_QUESTIONS];
    int      nb_questions;
    int      points_negatifs;
    int      multi_reponses;
    int      sequentiel;
} QCM;

int  scanf_secu(const char *prompt, int min, int max);
int  sauvegarder_qcm(const QCM *q);
QCM  charger_qcm(const char *nom);
int  lister_qcm(char noms[MAX_QUESTIONS][MAX_NOM]);
void menu_etudiant(void);


#endif /*QCM_H*/
