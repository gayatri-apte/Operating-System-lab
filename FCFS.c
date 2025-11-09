#include <stdio.h>
#include <stdbool.h>

#define MAX 50

bool isHit(int frames[], int n, int page)
{
    for (int i = 0; i < n; i++)
    {
        if (frames[i] == page)
            return true;
    }
    return false;
}

void printframes(int frames[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (frames[i] == -1)
            printf("-");
        else
            printf("%d", frames[i]);
    }
    printf("\n");
}

void FCFS(int pages[], int n, int framesize)
{
    int frames[framesize];
    int faults = 0, index = 0;

    for (int i = 0; i < framesize; i++)
        frames[i] = -1;

    printf("FCFS Page Replacement\n");

    for (int i = 0; i < n; i++)
    {
        printf("Page %d → ", pages[i]);
        if (!isHit(frames, framesize, pages[i]))
        {
            frames[index] = pages[i];
            index = (index + 1) % framesize;
            faults++;
        }
        printframes(frames, framesize);
    }

    printf("Total Page Faults: %d\n", faults);
}

int main()
{
    int n, framesize;
    int pages[MAX];

    printf("Enter the number of pages:\n");
    scanf("%d", &n);

    printf("Enter the reference string:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter the frame size:\n");
    scanf("%d", &framesize);

    FCFS(pages, n, framesize);
    return 0;
}
