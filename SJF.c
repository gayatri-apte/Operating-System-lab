#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct process {
    int pid, arrival, burst, remaining, waiting, turnaround;
};

void sortbyarrival(struct process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].arrival > p[j + 1].arrival) {
                struct process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void SJF(struct process p[], int n) {
    int completed = 0, time = 0;
    float totalw = 0, totalt = 0;

    for (int i = 0; i < n; i++)
        p[i].remaining = p[i].burst;

    printf("\nSJF (Preemptive - SRTF) Scheduling\n");
    printf("Gantt Chart:\n");

    while (completed != n) {
        int idx = -1, min = INT_MAX;

        // Find process with shortest remaining time available at this moment
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0 && p[i].remaining < min) {
                min = p[i].remaining;
                idx = i;
            }
        }

        if (idx == -1) {
            time++; // No process arrived yet
            continue;
        }

        printf("|P%d", p[idx].pid);
        p[idx].remaining--;
        time++;

        if (p[idx].remaining == 0) {
            completed++;
            p[idx].turnaround = time - p[idx].arrival;
            p[idx].waiting = p[idx].turnaround - p[idx].burst;
            totalw += p[idx].waiting;
            totalt += p[idx].turnaround;
        }
    }

    printf("|\n\nProcess\tAT\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrival, p[i].burst,
               p[i].waiting, p[i].turnaround);
    }

    printf("\nAverage WT: %.2f", totalw / n);
    printf("\nAverage TAT: %.2f\n", totalt / n);
}

int main() {
    int n;
    struct process p[20];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter AT and BT for P%d: ", p[i].pid);
        scanf("%d %d", &p[i].arrival, &p[i].burst);
    }

    sortbyarrival(p, n);
    SJF(p, n);
    return 0;
}
