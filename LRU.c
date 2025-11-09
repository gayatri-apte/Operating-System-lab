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

void LRU(int pages[], int n, int framesize)
{
    int frames[framesize], used[framesize];
    int faults = 0, time = 0;

    for (int i = 0; i < framesize; i++)
    {
        frames[i] = -1;
        used[i] = 0;
    }

    printf("\nLRU Page Replacement Algorithm\n");

    for (int i = 0; i < n; i++)
    {
        printf("Page %d -> ", pages[i]);
        bool hit = false;

        // Check if the page is already present
        for (int j = 0; j < framesize; j++)
        {
            if (frames[j] == pages[i])  // ✅ FIXED: comparison, not assignment
            {
                used[j] = ++time;
                hit = true;
                break;
            }
        }

        // If page fault occurs
        if (!hit)
        {
            int lru = 0;
            for (int j = 1; j < framesize; j++)
            {
                if (used[j] < used[lru])
                    lru = j;
            }

            frames[lru] = pages[i];     // ✅ FIXED: assignment, not comparison
            used[lru] = ++time;
            faults++;
        }

        printframes(frames, framesize);
    }

    printf("\nTotal Page Faults: %d\n", faults);
}

int main()
{
    int n, framesize;
    int pages[MAX];

    printf("Enter the number of pages: ");
    scanf("%d", &n);

    printf("Enter the reference string: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter the frame size: ");
    scanf("%d", &framesize);

    LRU(pages, n, framesize);  
    return 0;
}
