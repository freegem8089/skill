#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
int main(void)
{
pid_t pid;
if((pid=fork()) < 0)
printf("\tfork error\n");
else
if(pid==0)
printf("child process id is %d\n",getpid());
else
{
sleep(10);
printf("*****parent\n");
system("ps -axj | tail");
}
exit(0);
}