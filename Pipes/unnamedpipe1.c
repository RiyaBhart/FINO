#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int main(void) {
    char write_msg[BUFFER_SIZE] = "Greetings";
    char read_msg[BUFFER_SIZE];
    int fd[2];
    pid_t pid;

    if (pipe(fd) == -1) { 
        fprintf(stderr, "Pipe failed");
        return 1;
    }

    pid = fork();
    if (pid < 0) { 
        fprintf(stderr, "Fork Failed");
        return 1;
    }

    if (pid > 0) { 
        close(fd[READ_END]);
        write(fd[WRITE_END], write_msg, strlen(write_msg) + 1);
        close(fd[WRITE_END]);
    } else {
        close(fd[WRITE_END]); 
        read(fd[READ_END], read_msg, BUFFER_SIZE); 
        printf("read %s", read_msg);
        close(fd[READ_END]); 
    }
    printf("Parent Process ID: %d\n", getpid());
    if (pid > 0) {
    printf("Child Process ID: %d\n", pid);
    }


    return 0;
}
