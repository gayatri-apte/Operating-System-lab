#include <stdio.h>

int main()
{
    int P, R, i , j, k;
    printf("Enter the number of processes and resources:\n");
    scanf("%d %d", &P, &R);
    
    int available[R], max[P][R], allocation[P][R], need[P][R];
    int finish[P], safeseq[P], cnt =0;
    printf("Enter the available matrix:\n");
    for(int i =0; i<R; i++) scanf("%d", &available[i]);

    printf("Enter the max matrix:\n");
    for(int i =0; i<P; i++)
    {
        for(int j =0; j<R; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the allocation matrix:\n");
    for(int i =0; i<P; i++)
    {
        for(int j =0; j<R; j++)
        {
            scanf("%d", &allocation[i][j]);
        }
    }

    for(int i =0; i<P; i++)
    {
        finish[i] = 0;
        for(int j =0; j<R; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
    
    while(cnt <P)
    {
        int found = 0;
        for(int i =0; i<P; i++)
        {
            if(!finish[i])
            {
                int canAllocate = 1;
                for(int j =0; j<R; j++)
                {
                    if(need[i][j] > available[j])
                    {
                        canAllocate = 0;
                        break;
                    }
                }
                if(canAllocate)
                {
                    for(int k =0; k<R; k++)
                    {
                        available[k] += allocation[i][k];
                    }
                    safeseq[cnt++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if(!found)
        {
            printf("The system is not in safe state!");
            return 0;
        }
    }
    printf("The safe seq is :\n");
    for(int i =0; i<P; i++)
    {
        printf("P %d ",safeseq[i]);
    }
    printf("\n");
    return 0;
}