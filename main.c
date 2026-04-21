#include<stdio.h>
#include<stdlib.h>

void modeEnseignant(){
	printf("\n --- Bienvenue dans le mode Enseignant ---\n");
	printf("Dans ce mode on va creer les questions \n");
}


void modeEtudiant(){
	printf("\n--- Bienvenue dans le mode Etudiant ---\n");
	printf("C'est parti pour le quiz \n");
}

int main(){

int choix = 0;
	while( choix != 3){
	printf("\n--- Bienvenue dans QUESTION POUR UN TAKEN ---\n");
	printf("1. Mode Enseignant\n");
	printf("2. Mode Etudiant\n");
	printf("3. Quitter\n");
	printf("Quel est votre choix:  \n");
	scanf("%d",&choix);

	if(choix == 1){
		modeEnseignant();
}
	else if(choix == 2){
		modeEtudiant();
}
	else if(choix == 3){
		printf("Au revoir ! \n");
}
	else{
		printf("choix invalide recommancez\n");
}


	}

return 0;
}
