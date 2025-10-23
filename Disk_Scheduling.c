#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

//sort the request array
void sort(int arr[], int n){
    for(int i =0; i< n-1; i++){
        for(int j =0; j< n-1-i; j++)
        {
            if(arr[j]> arr[j+1]){
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}

//SSTF (shortest seek time first)

void SSTF(int requests[], int n, int head){
    int total_seek = 0;
    int current = head;
    bool visited[n];

    for(int i =0; i<n; i++){
        visited[i] = false;
    }
    printf("SSTF order");
    for(int count =0; count<n; count++){
        int min = 1e9, index = -1;
        for(int i=0; i<n; i++){
            if(!visited[i]){
                int dist = abs(current - requests[i]);
                if(dist < min){
                    min = dist;
                    index = i;
                }
            }
        }
        visited[index] = true;
        printf("%d", requests[index]);
        total_seek += abs(current - requests[index]);
        current = requests[index];
    }
    printf("\n Total seek time: %d\n", total_seek);

}

//SCAN 
void SCAN(int requests[], int n, int head, int disk_size){
    int total_seek = 0;
    int i;
    sort(requests, n);

    for( i =0; i< n; i++){
        if(requests[i] > head){
            break;
        }

    }
    printf("SCAN ORDER");

    //Move towards right(higher order)
    for(int j =i; i<n; i++){
        printf("%d", requests[j]);
        total_seek+= abs(head - requests[j]);
        head = requests[j];
    }
    //Hit the edn of disk
    total_seek+= abs(head - (disk_size -1));
    head = disk_size - 1;

    //Move left 
    for(int j = i-1; j>=0; j--){
        printf("%d", requests[j]);
        total_seek += abs(head - requests[j]);
        head = requests[j];

    }
    printf("Total seek time :%d\n", total_seek);
}

//C-LOOK Scan 
void CLOOK(int requests[], int n, int head){
    int total_seek =0;
    int i;
    sort(requests, n);

    for(i =0; i<n; i++){
        if(requests[i] > head){
            break;
        }
    }
    printf("\n CLOOK order");

    //Move right
    for(int j = i; j< n; j++){
        printf("%d", requests[j]);
        total_seek+= abs(head - requests[j]);
        head = requests[j];
    }

    //Jump to beginning 
    if(i > 0){
        total_seek += abs(head - requests[0]);
        head = requests[0];
    }

    //continue the process
     for(int j = 0; j< i; j++){
        printf("%d", requests[j]);
        total_seek+= abs(head - requests[j]);
        head = requests[j];
    }
    printf("\n total seek time :%d\n", total_seek);
}

int main()
{
    int n, head, disk_size;
    printf("Enter the number of disk requests");
    scanf("%d", &n);

    int requests[n];

    printf("Enter the disk requests:");
    for(int i =0; i<n; i++){
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial head position:");
    scanf("%d", &head);

    printf("Enter the disk size:");
    scanf("%d", &disk_size);

    SSTF(requests, n, head);
    SCAN(requests, n, head, disk_size);
    CLOOK(requests, n, head);

    return 0;



}