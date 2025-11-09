#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define SHM_SIZE 1024

int main()
{
    key_t key = ftok("shmfile", 65);
    if(key == -1)
    {
        perror("ftok");
        exit(1);
    }
    int shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if(shmid == -1)
    {
        perror("shmid");
        exit(1);
    }
    char* data = (char*)shmat(shmid, NULL, 0);
    if(data == (char*)-1)
    {
        perror("shmat");
        exit(1);
    }
    printf("Message from server:%s", data);
    if(shmdt(data)==-1)
    {
        perror("shmdt");
        exit(1);
    }
    if(shmctl(shmid, IPC_RMID, NULL)==-1)
    {
        perror("shmctl");
        exit(1);
    }
    return 0;

}
