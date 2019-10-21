#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

FILE * validateInput() {
	printf("Entrez le chemin du fichier qui contient la ou les grille(s) de Sudoku à valider : ");
	char filepath[100] = {0};
	scanf("%s", filepath);
	FILE *fp = fopen(filepath, "r");
	while (fp == NULL) {
		printf("Le fichier fourni n'existe pas, veuillez réessayer\n");
		printf("Entrez le chemin du fichier qui contient la ou les grille(s) de Sudoku à valider : ");
		scanf("%s", filepath);
		fp = fopen(filepath, "r");
	}

	return fp;
}


int compteurMatrices(FILE *fp) {
	int nombreMatrices = 0;
	char ligne[100];
	while (fgets(ligne, sizeof(ligne), fp)) {
		if (ligne[0] == '\n') 
			nombreMatrices += 1;
	}
	rewind(fp);
	return nombreMatrices + 1;
}


char * contenuFichier(FILE *fp) {
	char * contenu = 0;
	long longueur;

	if (fp) {
		fseek (fp, 0, SEEK_END);
		longueur = ftell (fp);
		fseek (fp, 0, SEEK_SET);
		contenu = malloc (longueur);
		if (contenu) {
			fread (contenu, 1, longueur, fp);
		}
		fclose (fp);
	}
	
	return contenu;
}


void extraireMatrice(char * contenu, int nombreDeMatrices) { 
	int length = strlen(contenu);
	char **matrice = malloc (1000 * sizeof(char));
	char ***tableauMatrices = malloc (nombreDeMatrices * sizeof(matrice));
	
	int j, k = 0;
	
	char *p1, *p2, *temp;
	p1 = strtok_r(contenu, "\n", &temp);
	
	for (int i = 0; i < length; i++) {
		p2 = strtok_r(NULL, "\n", &temp);
		if (p2 != NULL) {
			if (i == 0) {
				matrice[j] = p1;
			} else {
				matrice[j] = p2;
			}
			j++;
		} else {
			tableauMatrices[k] = matrice;
			k++;
			j = 0;
		}
	} 
	
	for (int i = 0; i < 9; i++) {
		printf("%s\n", tableauMatrices[2][i]);
	}
	
}


int main(int argc, char *argv[]) {
	FILE *fp = validateInput();
	int cptMatrices = compteurMatrices(fp);
	char *contenu = contenuFichier(fp);
	extraireMatrice(contenu, cptMatrices);
	return 0;
}
