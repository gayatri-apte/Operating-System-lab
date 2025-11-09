#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void sort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

void scan(int requests[], int n, int head, int disk_size)
{
    int total_seek = 0;
    int i;
    sort(requests, n);

    // Find the first request greater than head
    for (i = 0; i < n; i++)
    {
        if (requests[i] > head)
            break;
    }

    printf("SCAN Disk Scheduling Order:\n");

    // Move towards the right (higher tracks)
    for (int j = i; j < n; j++)
    {
        printf("%d ", requests[j]);
        total_seek += abs(head - requests[j]);
        head = requests[j];
    }

    // Go to the end of disk
    total_seek += abs(head - (disk_size - 1));
    head = disk_size - 1;

    // Move towards the left (lower tracks)
    for (int j = i - 1; j >= 0; j--)
    {
        printf("%d ", requests[j]);
        total_seek += abs(head - requests[j]);
        head = requests[j];
    }

    printf("\nTotal seek is: %d\n", total_seek);
}

int main()
{
    int n, head, disk_size;
    printf("Enter the number of requests:\n");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the disk requests:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial head position:\n");
    scanf("%d", &head);

    printf("Enter the disk size:\n");
    scanf("%d", &disk_size);

    scan(requests, n, head, disk_size);
    return 0;
}
