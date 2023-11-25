#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[20];
    int arrival_time;
    int burst_time;
    int priority;
} Process;


void fcfs(Process *processes, int num_processes) {
    for (int i = 0; i < num_processes; i++) {
        for (int j = i + 1; j < num_processes; j++) {
            if (processes[i].arrival_time > processes[j].arrival_time) {
                Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    int total_waiting_time = 0;
    int total_turnaround_time = 0; 

    printf("Ordre d'exécution des processus (FCFS) avec timeline :\n");

    int s_wainting_time = 0; // Variable pour stocker la somme des temps d'attente

    for (int i = 0; i < num_processes; i++) {
        int waiting_time = total_waiting_time - processes[i].arrival_time;
        if (waiting_time < 0) {
            waiting_time = 0; // Le temps d'attente ne peut pas être négatif
        }
        s_wainting_time += waiting_time; // Ajoutez le temps d'attente actuel à X
        int turnaround_time = waiting_time + processes[i].burst_time;
        printf("Temps %d - %d : %s (Temps d'attente : %d, Temps de rotation : %d)\n", total_waiting_time, total_waiting_time + processes[i].burst_time, processes[i].name, waiting_time, turnaround_time);

        for (int j = 0; j < total_waiting_time; j++) {
            printf("-");
        }
        for (int j = 0; j < processes[i].burst_time; j++) {
            printf("*");
        }
        printf("\n");

        total_waiting_time += processes[i].burst_time;
        total_turnaround_time += turnaround_time;
    }

    double average_waiting_time = (double) s_wainting_time  / num_processes;
    double average_turnaround_time = (double)total_turnaround_time / num_processes;

    printf("Temps de rotation moyen : %.2f\n", average_turnaround_time);

    printf("Somme des temps d'attente  : %.2f\n", average_waiting_time);

}

int main(){
    FILE *file = fopen("prc.txt", "r");
    if (file == NULL) {
        perror("Impossible d'ouvrir le fichier.");
        return 1;
    }

    int num_processes;
    fscanf(file, "%d", &num_processes);

    Process *processes = (Process *)malloc(num_processes * sizeof(Process));

    for (int i = 0; i < num_processes; i++) {
        fscanf(file, "%s %d %d %d", processes[i].name, &processes[i].arrival_time, &processes[i].burst_time, &processes[i].priority);
    }

    fclose(file);
    printf("Ordonnancement FCFS :\n");
    fcfs(processes, num_processes);
    free(processes);
}

