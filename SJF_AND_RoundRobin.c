#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Process {
    int pid;             // Process ID
    int arrival;         // Arrival time
    int burst;           // Burst time
    int remaining;       // Remaining burst time (for preemptive)
    int waiting;         // Waiting time
    int turnaround;      // Turnaround time
    int completed;       // Completion status
};

// Function to sort by arrival time
void sortByArrival(struct Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].arrival > p[j + 1].arrival) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

// Function for SJF (Preemptive)
void SJF_Preemptive(struct Process p[], int n) {
    int completed = 0, time = 0, minBurst, shortest;
    float totalWaiting = 0, totalTurnaround = 0;

    for (int i = 0; i < n; i++)
        p[i].remaining = p[i].burst;

    printf("\n--- Shortest Job First (Preemptive) Scheduling ---\n");
    printf("Gantt Chart:\n");

    while (completed != n) {
        shortest = -1;
        minBurst = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0 && p[i].remaining < minBurst) {
                minBurst = p[i].remaining;
                shortest = i;
            }
        }

        if (shortest == -1) {
            time++;
            continue;
        }

        printf("| P%d ", p[shortest].pid);
        p[shortest].remaining--;
        time++;

        if (p[shortest].remaining == 0) {
            completed++;
            int finishTime = time;
            p[shortest].turnaround = finishTime - p[shortest].arrival;
            p[shortest].waiting = p[shortest].turnaround - p[shortest].burst;

            totalWaiting += p[shortest].waiting;
            totalTurnaround += p[shortest].turnaround;
        }
    }

    printf("|\n\nProcess\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrival, p[i].burst, p[i].waiting, p[i].turnaround);
    }

    printf("\nAverage Waiting Time: %.2f", totalWaiting / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTurnaround / n);
}

// Function for Round Robin
void RoundRobin(struct Process p[], int n, int quantum) {
    int time = 0, completed = 0;
    float totalWaiting = 0, totalTurnaround = 0;

    for (int i = 0; i < n; i++)
        p[i].remaining = p[i].burst;

    printf("\n--- Round Robin Scheduling (Quantum = %d) ---\n", quantum);
    printf("Gantt Chart:\n");

    while (completed != n) {
        int executed = 0;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0) {
                executed = 1;
                if (p[i].remaining > quantum) {
                    printf("| P%d ", p[i].pid);
                    time += quantum;
                    p[i].remaining -= quantum;
                } else {
                    printf("| P%d ", p[i].pid);
                    time += p[i].remaining;
                    p[i].turnaround = time - p[i].arrival;
                    p[i].waiting = p[i].turnaround - p[i].burst;
                    totalWaiting += p[i].waiting;
                    totalTurnaround += p[i].turnaround;
                    p[i].remaining = 0;
                    completed++;
                }
            }
        }
        if (!executed) time++;
    }

    printf("|\n\nProcess\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrival, p[i].burst, p[i].waiting, p[i].turnaround);
    }

    printf("\nAverage Waiting Time: %.2f", totalWaiting / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTurnaround / n);
}

int main() {
    int n, choice, quantum;
    struct Process p[20];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter arrival time and burst time for P%d: ", p[i].pid);
        scanf("%d %d", &p[i].arrival, &p[i].burst);
        p[i].completed = 0;
    }

    sortByArrival(p, n);

    printf("\nSelect Scheduling Algorithm:\n");
    printf("1. Shortest Job First (Preemptive)\n");
    printf("2. Round Robin\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if (choice == 1)
        SJF_Preemptive(p, n);
    else if (choice == 2) {
        printf("Enter Time Quantum: ");
        scanf("%d", &quantum);
        RoundRobin(p, n, quantum);
    } else
        printf("Invalid choice!\n");

    return 0;
}
