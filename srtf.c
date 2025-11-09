#include <stdio.h>

#define MAX 10

struct Process {
    int id;
    int at;
    int bt;
    int remaining_bt;
    int ct;
    int wt;
    int tat;
};

int find_shortest_remaining_time(struct Process p[], int n, int current_time) {
    int min_remaining_time = 9999;
    int min_index = -1;
    for (int i = 0; i < n; i++) {
        if (p[i].at <= current_time && p[i].remaining_bt > 0 && p[i].remaining_bt < min_remaining_time) {
            min_remaining_time = p[i].remaining_bt;
            min_index = i;
        }
    }
    return min_index;
}

void srtf(struct Process p[], int n) {
    int current_time = 0;
    int completed = 0;
    int total_wt = 0;
    int total_tat = 0;

    int gantt_chart_process[100];
    int gantt_chart_time[100];
    int gantt_chart_idx = 0;

    for (int i = 0; i < n; i++) {
        p[i].remaining_bt = p[i].bt;
    }

    while (completed < n) {
        int idx = find_shortest_remaining_time(p, n, current_time);

        if (idx == -1) {
            current_time++;
            continue;
        }

       
        if (gantt_chart_idx == 0 || gantt_chart_process[gantt_chart_idx - 1] != p[idx].id) {
            gantt_chart_process[gantt_chart_idx] = p[idx].id;
            gantt_chart_time[gantt_chart_idx] = current_time;
            gantt_chart_idx++;
        }

        p[idx].remaining_bt--;
        current_time++;

        if (p[idx].remaining_bt == 0) {
            p[idx].ct = current_time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            total_wt += p[idx].wt;
            total_tat += p[idx].tat;
            completed++;
        }
    }

    gantt_chart_time[gantt_chart_idx] = current_time;

    printf("\nGantt Chart:\n");
    for (int i = 0; i < gantt_chart_idx; i++) {
        printf("---P%d---", gantt_chart_process[i]);
    }
    printf("\n");
    for (int i = 0; i <= gantt_chart_idx; i++) {
        printf("%d\t", gantt_chart_time[i]);
    }
    printf("\n");

    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].wt, p[i].tat);
    }
    printf("\nAverage Waiting Time: %.2f", (float)total_wt / n);
    printf("\nAverage Turnaround Time: %.2f", (float)total_tat / n);
    printf("\n");
}

int main() {
    struct Process p[MAX];
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
    srtf(p, n);
    return 0;
}