#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define PIPE1 "pipe"
#define PIPE2 "pipe"
#define FILE_NAME "result.txt"
#define SIZE 1024

void count_data(char *text, int *ch, int*wd, int*ln)
{
    *ch = *wd =*ln =0;
    int in_word = 0;
    for(int i =0; text[i]!='\0'; i++)
    {
        (*ch)++;
        if(text[i]=='\n'){(*ln)++;}

        if(text[i]==' '|| text[i]=='\t' || text[i]=='\n')
        {
            in_word = 0;
        }
        else if(!in_word)
        {
            in_word = 0;
            (*wd)++;
        }
    }
}

void process1()
{
    char input[SIZE], result[SIZE];
    int fd1 = open(PIPE1, O_WRONLY); 
    if(fd1 < 0){perror("pipe1 write error.");}

    printf("Enter the sentence\n");
    fgets(input, SIZE, stdin);
    write(fd1, input, strlen(input)+1);
    close(fd1);

    int fd2 = open(PIPE2, O_RDONLY);
    if(fd2 <0){perror("pipe2 read error");}
    read(fd2, result, SIZE);
    close(fd2);
    printf("result from process2:\n %s \n", result);   
}

void process2()
{
    char input[SIZE], result[SIZE];
    int fd1 = open(PIPE1,O_RDONLY);
    if(fd1<0){perror("pipe1 read error");}
    read(fd1, input, SIZE);
    close(fd1);

    int ch, wd, ln;
    count_data(input, &ch, &wd, &ln);
    FILE*fp = fopen(FILE_NAME, "w");
    fprintf(fp, "character:%d\n words:%d\n lines :%d\n", ch, wd, ln);
    fclose(fp);

    fp = fopen(FILE_NAME, "r");
    fread(result, sizeof(char), SIZE, fp);
    fclose(fp);

    int fd2 = open(PIPE2, O_WRONLY);
    if(fd2 <0){perror("pipe2 write error"); exit(0);}
    write(fd2, result, strlen(result)+1);
    close(fd2);
}

int main()
{
    unlink(PIPE1), unlink(PIPE2);
    mkfifo(PIPE1, 0666);
    mkfifi(PIPE2, 0666);
    pid_t pid = fork();
    if(pid <0)
    {
        perror("Fork failed");
        exit(1);
    }
    else if(pid == 0)
    {
        process2();
    }
    else
    {
        process1();
    }
    unlink(PIPE1);
    unlink(PIPE2);
    return 0;
}
