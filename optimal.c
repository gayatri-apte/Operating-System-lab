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

void Optimal(int pages[], int n, int framesize)
{
    int frames[framesize];
    int faults = 0;

    for (int i = 0; i < framesize; i++)
        frames[i] = -1;

    printf("\n--- Optimal Page Replacement ---\n");

    for (int i = 0; i < n; i++)
    {
        printf("Page %d -> ", pages[i]);
        if (!isHit(frames, framesize, pages[i]))
        {
            int replaceIndex = -1, farthest = i + 1;

            for (int j = 0; j < framesize; j++)
            {
                if (frames[j] == -1)
                {
                    replaceIndex = j;
                    break;
                }

                int k;
                for (k = i + 1; k < n; k++)
                {
                    if (frames[j] == pages[k])
                        break;
                }

                if (k == n)
                {
                    replaceIndex = j;
                    break;
                }
                else if (k > farthest)
                {
                    farthest = k;
                    replaceIndex = j;
                }
            }

            frames[replaceIndex] = pages[i];
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

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter the reference string: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter frame size: ");
    scanf("%d", &framesize);

    Optimal(pages, n, framesize);
    return 0;
}

