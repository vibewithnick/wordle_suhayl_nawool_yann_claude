#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_WORD_LENGTH 6
#define MAX_WORDS 2309
#define MAX_TRIES 6

char mots[MAX_WORDS][MAX_WORD_LENGTH];
char motSecret[MAX_WORD_LENGTH];

// Fonction pour choisir aléatoirement un mot dans la base de données
void choisirMotSecret() {
    srand(time(NULL));
    int indice = rand() % MAX_WORDS;
    strcpy(motSecret, mots[indice]);
}

// Fonction pour vérifier si le mot proposé par le joueur est valide
int estMotValide(char *motPropose) {
    int i, j;
    int longueur = strlen(motPropose);
    if (longueur != 5) {
        return 0;
    }
    for (i = 0; i < longueur; i++) {
        if (!(motPropose[i] >= 'a' && motPropose[i] <= 'z')) {
            return 0;
        }
    }
    return 1;
}

// Fonction pour vérifier les lettres bien positionnées et présentes mais mal positionnées
void verifierMot(char *motPropose) {
    int i, j;
    int bienPositionnees = 0;
    int presentes = 0;
    for (i = 0; i < 5; i++) {
        if (motPropose[i] == motSecret[i]) {
            bienPositionnees++;
        } else {
            for (j = 0; j < 5; j++) {
                if (motPropose[i] == motSecret[j]) {
                    presentes++;
                    break;
                }
            }
        }
    }
    printf("Lettres bien positionnées : %d\n", bienPositionnees);
    printf("Lettres présentes mais mal positionnées : %d\n", presentes);
}

int main() {
    FILE *fichier;
    char ligne[100];
    int nbMots = 0;
    int essais = 0;
    char motPropose[MAX_WORD_LENGTH];

    // Ouvrir le fichier en mode lecture
    fichier = fopen("bdd_wordle.txt", "r");
    if (fichier == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }

    // Lire le fichier ligne par ligne
    while (fgets(ligne, sizeof(ligne), fichier)) {
        if (strstr(ligne, "Wordle Words List") != NULL) {
            break;
        }
    }

    // Extraire et stocker les mots de la liste
    while (fgets(ligne, sizeof(ligne), fichier)) {
        if (strstr(ligne, "Related Word Lists") != NULL) {
            break;
        }
        char *token = strtok(ligne, " ");
        while (token != NULL) {
            if (strlen(token) == 5) {
                strcpy(mots[nbMots], token);
                nbMots++;
            }
            token = strtok(NULL, " ");
        }
    }

    // Fermer le fichier
    fclose(fichier);

    // Choisir aléatoirement un mot secret
    choisirMotSecret();

    printf("Bienvenue dans Wordle !\n");
    printf("Trouvez le mot secret de 5 lettres en moins de %d essais.\n", MAX_TRIES);

    // Boucle principale du jeu
    while (essais < MAX_TRIES) {
        printf("\nEssai %d/%d : ", essais + 1, MAX_TRIES);
        scanf("%s", motPropose);

        if (!estMotValide(motPropose)) {
            printf("Veuillez proposer un mot valide de 5 lettres.\n");
            continue;
        }

        if (strcmp(motPropose, motSecret) == 0) {
            printf("Félicitations ! Vous avez trouvé le mot secret : %s\n", motSecret);
            break;
        } else {
            printf("Le mot proposé n'est pas le bon.\n");
            verifierMot(motPropose);
            essais++;
        }
    }

    if (essais == MAX_TRIES) {
        printf("\nDésolé, vous avez épuisé tous vos essais.\n");
        printf("Le mot secret était : %s\n", motSecret);
    }

    return 0;
}
   
