
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  
    srand(time(NULL));

    FILE *fichier = fopen("processes.txt", "w");

    if (fichier == NULL) {
        fprintf(stderr, "Impossible d'ouvrir le fichier pour l'écriture.\n");
        return 1;
    }

    int nombre_de_processus = rand() % 10 + 1;

    fprintf(fichier, "%d\n", nombre_de_processus);

   
    for (int i = 1; i <= nombre_de_processus; i++) {

        int date_arrivee = rand() % 30 + 1;
        int duree_execution = rand() % 30 + 1;
        int priorite = rand() % 10 + 1;

        fprintf(fichier, "P%d %d %d %d\n", i, date_arrivee, duree_execution, priorite);
    }

    fclose(fichier);

    printf("Le fichier a été généré avec succès.\n");

    return 0;
}


