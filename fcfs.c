#include <stdio.h>

#define MAX_PROCESSES 10
struct Process {
    int id;
    int at;  
    int bt;  
    int ct;  
    int wt;  
    int tat; 
};
void sort_by_arrival_time(struct Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j+1].at) {
                struct Process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}
void fcfs_schedule(struct Process p[], int n) {
    int current_time = 0;
    int total_wt = 0;
    int total_tat = 0;
    sort_by_arrival_time(p, n);

    for (int i = 0; i < n; i++) {
        // If a process arrives after the current time, the CPU is idle
        if (p[i].at > current_time) {
            current_time = p[i].at;
        }
        p[i].ct = current_time + p[i].bt;
        // Update current time for the next process
        current_time = p[i].ct;

        
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
       
       
        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }
   
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].wt, p[i].tat);
    }
    printf("\nAverage Waiting Time: %.2f", (float)total_wt / n);
    printf("\nAverage Turnaround Time: %.2f", (float)total_tat / n);
    printf("\n");
}

int main() {
    struct Process p[MAX_PROCESSES];
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("\nEnter arrival time for Process P%d: ", i + 1);
        scanf("%d", &p[i].at);
        printf("Enter burst time for Process P%d: ", i + 1);
        scanf("%d", &p[i].bt);
    }
   
    fcfs_schedule(p, n);
   
    return 0;
}