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

void clook(int requests[], int n, int head)
{
    int total_seek = 0;
    sort(requests, n);

    int i;
    for (i = 0; i < n; i++)
    {
        if (requests[i] > head)
            break;
    }

    printf("CLOOK Disk Scheduling Order:\n");

    // Move from head to the end
    for (int j = i; j < n; j++)
    {
        printf("%d ", requests[j]);
        total_seek += abs(head - requests[j]);
        head = requests[j];
    }

    // Wrap around to beginning
    if (i > 0)
    {
        total_seek += abs(head - requests[0]);
        head = requests[0];
        for (int j = 0; j < i; j++)
        {
            printf("%d ", requests[j]);
            total_seek += abs(head - requests[j]);
            head = requests[j];
        }
    }

    printf("\nTotal Seek Time: %d\n", total_seek);
}

int main()
{
    int n, head;

    printf("Enter the number of disk requests:\n");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the requests:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial head position:\n");
    scanf("%d", &head);

    clook(requests, n, head);
    return 0;
}
