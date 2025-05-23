#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/resource.h>

void proc_exit(){
int wstat;
pid_t pid;

while(1){
pid = wait3(&wstat,WNOHANG,NULL);
if(pid==0||pid==-1){
fprintf(stdout,"return value of wait3() is %d\n",pid);
return;
}
fprintf(stdout,"return code: %d\n",wstat);
}
}
int main(){
signal(SIGCHLD, proc_exit);
switch(fork()){
case -1:
perror("main:fork");
exit(0);
case 0:
printf("i am alive temporarily\n");
int ret_code = rand();
printf("return code : %d\n",ret_code);
exit(ret_code);
default:
pause();
}
exit(0);
}
