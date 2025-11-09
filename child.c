#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{
    if(argc < 2)
    {
        printf("No data recieved from parent.\n");
        return 1;
    }
    int n = argc -1;
    int arr[n];
    for(int i =1; i<argc; i++)
    {
        arr[i-1] = atoi(argv[i]);
    }
    printf("Child recieved the array as :\n");
    for(int i =0; i<n; i++)
    {
        printf("%d", arr[i]);
    }
    printf("Child sorted array in reverse order is:\n");
    for(int i = n-1; i>=0; i--)
    {
        printf("%d", arr[i]);
    }
    printf("\n");
    return 0;

}