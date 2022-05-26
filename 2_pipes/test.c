#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <unistd.h>


int main(){
    FILE *fbridge;
    fbridge = fopen("bridge.bin","w+b");
    if(fbridge==NULL){
        printf("There is a error about openning bridge.b");
        exit(0);
    }
    int weigth = 10;
    char *row = malloc(weigth*sizeof(char));

    for(int i=0;i<weigth;i++){
        *(row+i) = 'Z';
    }
    //fork();
    //fork();
    //printf("1\n");
    //printf("2\n");
    //printf("3\n");
    int pipefd[2];
    int r;
    r = pipe(pipefd);
    //Handling possible error that pipe() would return
    if(r<0){
        perror("Error is got about pipe() function");
        exit(0);
    }

    pid_t pid;
    pid = fork();

    if(pid==0){
        close(pipefd[0]);
        printf("HIJO1\n");
        write(pipefd[1],"h",1);
        printf("HIJO2\n");
        close(pipefd[1]);
    }else{
        close(pipefd[1]);
        printf("PADRE1\n");
        char var;
        read(pipefd[0],"h",1);
        printf("PADRE2\n");
        close(pipefd[0]);
    }
    fclose(fbridge);

    return 0;

}