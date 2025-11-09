#include <stdio.h>
#include <stdlib.h>

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

void RR(struct process p[], int n, int q) {
    int completed = 0, time = 0;
    float totalw = 0, totalt = 0;

    for (int i = 0; i < n; i++)
        p[i].remaining = p[i].burst;

    printf("\nRound Robin Scheduling\n");
    printf("Gantt Chart:\n");

    while (completed != n) {
        int executed = 0;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0) {
                executed = 1;
                printf("|P%d", p[i].pid);

                if (p[i].remaining > q) {
                    time += q;
                    p[i].remaining -= q;
                } else {
                    time += p[i].remaining;
                    p[i].turnaround = time - p[i].arrival;
                    p[i].waiting = p[i].turnaround - p[i].burst;
                    totalw += p[i].waiting;
                    totalt += p[i].turnaround;
                    p[i].remaining = 0;
                    completed++;
                }
            }
        }

        if (!executed) // No process available yet
            time++;
    }

    printf("|\n\nProcess\tAT\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].arrival, p[i].burst,
               p[i].waiting, p[i].turnaround);
    }

    printf("\nAverage WT: %.2f", totalw / n);
    printf("\nAverage TAT: %.2f\n", totalt / n);
}

int main() {
    int n, q;
    struct process p[20];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter AT and BT for P%d: ", p[i].pid);
        scanf("%d %d", &p[i].arrival, &p[i].burst);
    }

    printf("Enter the time quantum: ");
    scanf("%d", &q);

    sortbyarrival(p, n);
    RR(p, n, q);
    return 0;
}
