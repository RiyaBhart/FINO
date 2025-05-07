#include <stdio.h>
#include <signal.h>
#include <unistd.h>

//void sigint_handler(int signum){
//fprintf(stdout,"caught sigint signal (%d)\n",signum);
//}

int main(){
if(signal(SIGINT,SIG_IGN)==SIG_ERR){
printf("error setting up signal handler for SIGINT\n");
return 1;
}

printf("press ctrl+c - it will be ignored\n");

while(1){
sleep(1);
}

return 0;
}
