#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>

int main(){
  int pid = fork();

  if(pid>0){
    printf("Parent process %d\n",getpid());
    printf("Child process %d\n",pid);
  }
  else if(pid==0){
    sleep(10);
    printf("Child process %d\n",getpid());
    printf("Parent process %d\n",getppid());
  }
  return 0;
}


//Childs are there but parents are not taking care of the child not paying attention