#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define READ 0
#define WRITE 1

int main(){
    pid_t parent_pid = getpid();
    //piping array, with two file descriptors (reading end and writing end)
    int pipers[2];
    pipe(pipers);
    char message[100];
    char text[100];
    strcpy(text, "do your homework!");
    pid_t child1 = fork();
    if(child1 == 0){
        //code of child process #1                                                                                                          
        close(pipers[WRITE]);
        read(pipers[READ], message, sizeof(message));
        printf("pid %d: Recieved message: %s\n", getpid(), message);
    }else{
        //code of parent process                                                                                                            
        close(pipers[READ]);
        //try using strlen() instead of 18
        write(pipers[WRITE], text, strlen(text));
        printf("pid %d: Enter text: %s\n", parent_pid, text);
    }
}
