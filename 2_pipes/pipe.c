#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <unistd.h>


int main(){

    int weigth = 1000*100;
    char *row = malloc(weigth*sizeof(char));
    for(int i=0;i<weigth;i++){
        *(row+i) = '*';
    }

    char *row2;
    int bridge;
    if (weigth<=1000*50){
        bridge = weigth;
        row2 = malloc(bridge* sizeof(char));
    }else{
        bridge = 1000*50;
        row2 = malloc((bridge)* sizeof(char));
    }
    

    int pipefd[2];
    int r;
    r = pipe(pipefd);
    //Handling possible error that pipe() would return
    if(r<0){
        perror("Error is got about pipe() function");
        exit(0);
    }

    //AQUÍ EMPIEZA EL TIEMPO
    pid_t pid;
    pid = fork();

    int pointer = 0;
    while(1){
        if(pid==0){
            close(pipefd[0]);
            r = write(pipefd[1],(row+pointer),bridge);
            close(pipefd[1]);
        }else{
            close(pipefd[1]);
            r = read(pipefd[0],row2,bridge);
            printf("%s\n",row2);
            close(pipefd[0]);
        }
        pointer+=bridge;
        if(pointer>=weigth){
            break;
        }
    }
    //AQUÍ FINALIZA
    return 0;

}