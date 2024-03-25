#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 6
#define MAX_WORDS 2309

char mots[MAX_WORDS][MAX_WORD_LENGTH];

int main() {
    FILE *fichier;
    char ligne[100]; // Taille maximale d'une ligne
    int nbMots = 0;
    int debutListe = 0; // Indicateur pour le début de la liste de mots

    // Ouvrir le fichier en mode lecture
    fichier = fopen("bdd_wordle.txt", "r");
    if (fichier == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }

    // Lire le fichier ligne par ligne
    while (fgets(ligne, sizeof(ligne), fichier)) {
        // Vérifier si nous sommes arrivés au début de la liste de mots
        if (strstr(ligne, "Wordle Words List") != NULL) {
            debutListe = 1;
            continue;
        }

        // Vérifier si nous avons atteint la fin de la liste de mots
        if (debutListe && strstr(ligne, "Related Word Lists") != NULL) {
            break;
        }

        // Si nous sommes dans la liste de mots, extraire et stocker chaque mot
        if (debutListe) {
            char *token = strtok(ligne, " ");
            while (token != NULL) {
                // Ignorer les mots plus longs que 5 lettres
                if (strlen(token) == 5) {
                    strcpy(mots[nbMots], token);
                    nbMots++;
                }
                token = strtok(NULL, " ");
            }
        }
    }

    // Fermer le fichier
    fclose(fichier);

    // Afficher les mots stockés
    printf("Nombre de mots lus : %d\n", nbMots);
    printf("Mots stockés :\n");
    for (int i = 0; i < nbMots; i++) {
        printf("%s\n", mots[i]);
    }

    return 0;
}
