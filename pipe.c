#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    int pipefd[2];
    pid_t pid;
    char buffer[100];

   
    if (pipe(pipefd) == -1) {
        perror("Pipe failed");
        return 1;
    }
    printf("Enter a message : ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;  
    pid = fork();
   
    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {
       close(pipefd[1]);
        read(pipefd[0], buffer, sizeof(buffer));  
        printf("Child received: %s\n", buffer);
        close(pipefd[0]);

    }
    else {
        close(pipefd[0]);
        write(pipefd[1], buffer, strlen(buffer) + 1);
        close(pipefd[1]);
        exit(0);
    }
}