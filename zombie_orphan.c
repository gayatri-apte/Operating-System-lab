#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

// Function for Bubble Sort
void bubbleSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function for Selection Sort
void selectionSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min])
                min = j;
        }
        int temp = arr[min];
        arr[min] = arr[i];
        arr[i] = temp;
    }
}

int main()
{
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    pid_t pid = fork();

    if (pid < 0)
    {
        printf("Fork failed!\n");
        exit(1);
    }

    else if (pid == 0)
    {
        // CHILD PROCESS
        printf("\n[Child] Process ID: %d | Parent ID: %d\n", getpid(), getppid());
        printf("[Child] Sorting using Selection Sort...\n");

        selectionSort(arr, n);

        printf("[Child] Sorted array: ");
        for (int i = 0; i < n; i++)
            printf("%d ", arr[i]);
        printf("\n");

        printf("[Child] Exiting now...\n");
        // To demonstrate ORPHAN process
        sleep(10);
        printf("[Child] After sleep, new Parent ID: %d (init/adopted)\n", getppid());
        exit(0);
    }
    else
    {
        // PARENT PROCESS
        printf("\n[Parent] Process ID: %d | Child ID: %d\n", getpid(), pid);
        printf("[Parent] Sorting using Bubble Sort...\n");

        bubbleSort(arr, n);

        printf("[Parent] Sorted array: ");
        for (int i = 0; i < n; i++)
            printf("%d ", arr[i]);
        printf("\n");

        printf("[Parent] Sleeping to create Zombie...\n");
        sleep(15);  // Child exits before parent waits → Zombie

        printf("[Parent] Now calling wait() to remove zombie...\n");
        wait(NULL);  // Cleans up zombie
        printf("[Parent] Child process reaped. Exiting.\n");
    }

    return 0;
}
