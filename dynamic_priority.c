#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Process {
    char processNumber[20];
    int arrivalTime;
    int burstTime;
    int priority;
    int turnaroundTime;
    int waitingTime;
    int burstTimeOriginal;
    int consecutiveSelections; 
} Process;

double averageTurnaroundTime = 0.0;
double averageWaitingTime = 0.0;

void preemptivePriorityScheduling(struct Process processes[], int n) {
    int currentTime = 0;
    int completedProcesses = 0;

    printf("\n| %-20s | %-15s | %-15s | %-8s |\n", "Process", "Start Time", "End Time", "Priority");
    printf("|----------------------|-----------------|-----------------|----------|\n");

  
    while (completedProcesses < n) {
        int highestPriorityIndex = -1;
        int highestPriority = INT_MIN;

  
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].burstTime > 0 &&
                processes[i].priority > highestPriority) {
                highestPriority = processes[i].priority;
                highestPriorityIndex = i;
            } else if (processes[i].arrivalTime <= currentTime && processes[i].burstTime > 0 &&
                       processes[i].priority == highestPriority &&
                       processes[i].arrivalTime < processes[highestPriorityIndex].arrivalTime) {
                highestPriorityIndex = i;
            }
        }

        if (highestPriorityIndex != -1) {
    
            printf("| %-20s | %-15d | %-15d | %-8d |\n", processes[highestPriorityIndex].processNumber,
                   currentTime, currentTime + 1, processes[highestPriorityIndex].priority);

            processes[highestPriorityIndex].burstTime--;

            if (highestPriorityIndex != -1) {
                if (processes[highestPriorityIndex].consecutiveSelections < 2) {
                    processes[highestPriorityIndex].consecutiveSelections++;
                } else {
                    processes[highestPriorityIndex].consecutiveSelections = 0;
                    processes[highestPriorityIndex].priority = (processes[highestPriorityIndex].priority > 0)
                                                                     ? processes[highestPriorityIndex].priority - 1
                                                                     : 0;
                }
            }


            if (processes[highestPriorityIndex].burstTime == 0) {
                completedProcesses++;

                processes[highestPriorityIndex].turnaroundTime = currentTime + 1 -
                                                                 processes[highestPriorityIndex].arrivalTime;
                processes[highestPriorityIndex].waitingTime = processes[highestPriorityIndex].turnaroundTime -
                                                               processes[highestPriorityIndex].burstTimeOriginal;

                averageTurnaroundTime += processes[highestPriorityIndex].turnaroundTime;
                averageWaitingTime += processes[highestPriorityIndex].waitingTime;
            }

            currentTime++;
        } else {
            currentTime++;
        }
    }
}

int main() {
    FILE *file = fopen("processes.txt", "r");
    if (file == NULL) {
        perror("Unable to open file.");
        return 1;
    }

    int num_processes;
    fscanf(file, "%d", &num_processes);

    Process *processes = (Process *)malloc(num_processes * sizeof(Process));
    if (processes == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < num_processes; i++) {
        fscanf(file, "%s %d %d %d", processes[i].processNumber, &processes[i].arrivalTime,
               &processes[i].burstTime, &processes[i].priority);
        processes[i].turnaroundTime = 0;
        processes[i].waitingTime = 0;
        processes[i].burstTimeOriginal = processes[i].burstTime;
        processes[i].consecutiveSelections = 0;
    }
    fclose(file);

    printf("Process execution order with Preemption Priority :\n");
    preemptivePriorityScheduling(processes, num_processes);

  
    printf("\n \nTurnaround and Waiting Times:\n");
    printf("\n| %-20s | %-15s | %-15s | %-8s |\n", "Process", "Turnaround Time", "Waiting Time", "Priority");
    printf("|----------------------|-----------------|-----------------|----------|\n");

    
    for (int i = 0; i < num_processes; i++) {
        printf("| %-20s | %-15d | %-15d | %-8d |\n", processes[i].processNumber,
               processes[i].turnaroundTime, processes[i].waitingTime, processes[i].priority);
    }

    averageTurnaroundTime /= num_processes;
    averageWaitingTime /= num_processes;

    printf("\nAverage Turnaround Time: %f\n", averageTurnaroundTime);
    printf("Average Waiting Time: %f\n", averageWaitingTime);


    free(processes);

    return 0;
}


