#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void bubblesort(int arr[], int n)
{
    for(int i =0; i<n-1; i++)
    {
        for(int j =0; j<n-i-1; j++)
        {
            if(arr[j] > arr[j+1])
            {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main()
{
    int n;
    printf("Enter the number of elements:\n");
    scanf("%d", &n);
    int arr[n];
    printf("Enter the array elements:\n");
    for(int i =0; i<n; i++)
    {
        scanf("%d", &arr[i]);
    }
    bubblesort(arr, n);
    printf("The parent sorted array :\n");
    for(int i =0; i<n; i++)
    {
        scanf("%d", &arr[i]);
    }
    printf("\n");
    pid_t pid = fork();
    if(pid < 0)
    {
        perror("Fork failed!");
        exit(0);
    }
    if(pid == 0)
    {
        printf("Child executing by execve!");
        char * args[n+2];
        args[0] = "./child";

        for(int i =0; i<n; i++)
        {
            char*numstr = malloc(10);
            sprintf(numstr, "%d", arr[i]);
            args[i+1] = numstr;
        }
        args[n+1] =  NULL;

        execve(args[0], args, NULL);

        perror("execve failed");
        exit(1);
    }
    else
    {
        wait(NULL);
        printf("Process complete!");
    }
    return 0;

}
