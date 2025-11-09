#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void sstf(int requests[], int n, int head)
{
    int total_seek = 0;
    int cur = head;
    bool visited[n];
    for (int i = 0; i < n; i++)
        visited[i] = false;

    printf("SSTF Disk Scheduling Order:\n");

    for (int count = 0; count < n; count++)
    {
        int min = 1e9, index = -1;

        for (int i = 0; i < n; i++)
        {
            if (!visited[i])
            {
                int dist = abs(cur - requests[i]);
                if (dist < min)
                {
                    min = dist;
                    index = i;
                }
            }
        }

        visited[index] = true;
        printf("%d ", requests[index]);
        total_seek += abs(cur - requests[index]);
        cur = requests[index];
    }

    printf("\nTotal seek is: %d\n", total_seek);
}

int main()
{
    int n, head;
    printf("Enter the number of requests:\n");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the disk requests:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &requests[i]);

    printf("Enter the head position:\n");
    scanf("%d", &head);

    sstf(requests, n, head);
    return 0;
}
