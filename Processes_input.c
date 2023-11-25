
#include <stdio.h>

int main() {
 
    int nombre_processus;
    printf("Entrez le nombre de processus : ");
    scanf("%d", &nombre_processus);

    FILE *fichier = fopen("prc.txt", "w");

    fprintf(fichier, "%d\n", nombre_processus);

    for (int i = 0; i < nombre_processus; i++) {
        char nom_processus[50];
        char date_arrivee[20];
        char duree_execution[20];
        int priorite;

        printf("Entrez le nom du processus %d : ", i + 1);
        scanf("%s", nom_processus);

        printf("Entrez la date d'arrivée du processus %d : ", i + 1);
        scanf("%s", date_arrivee);

        printf("Entrez la durée d'exécution du processus %d : ", i + 1);
        scanf("%s", duree_execution);

        printf("Entrez la priorité du processus %d : ", i + 1);
        scanf("%d", &priorite);

        fprintf(fichier, "%s %s %s %d\n", nom_processus, date_arrivee, duree_execution, priorite);
    }

    fclose(fichier);

    printf("Les informations ont été enregistrées dans le fichier processus.txt :) \n");

    return 0;
}


