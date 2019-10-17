#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

// nombre maximal de caractere quon peut lire
#define MAX_INPUT_COUNT 1000

/**
 * Obtenir un pointeur de stream vers le fichier que nous voulons ouvrir
 *
 * @param chemin Le chemin vers le fichier. Peut etre absolu ou relatif
 *
 * @return un pointeur de type FILE vers le fichier a ouvrir. NULL si echec
 *         d'ouverture.      
 */
FILE *get_fichier (const char chemin[])
{
    FILE *fichier = fopen(chemin, "r");
    if (!fichier)
        return NULL;
    else
        return fichier;
}

/**
 * Retourne le contenu du fichier en une chaine de caracteres
 */
char *get_input (char str[], FILE *fichier)
{
    char ligne[10];
    while (fgets(ligne, sizeof ligne, fichier))
        strcat(str, ligne);

    return str;
}

int main (int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "%s: Usage: <nom-fichier>\n", argv[0]);
        exit(1);
    }

    FILE *fichier = get_fichier(argv[1]);
    if (!fichier) {
        fprintf(stderr, "%s: Erreur: Fichier \"%s\" n'existe pas\n", argv[0], argv[1]);
        exit(1);
    }

    char entree_fichier[MAX_INPUT_COUNT] = {0};
    get_input(entree_fichier, fichier);

    printf("%s", entree_fichier);
    return 0;
}
