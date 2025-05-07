#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>

#define NUM_THREADS 4
#define gettid() syscall(SYS_gettid)

pthread_t threads[NUM_THREADS];

void sigusr1_handler(int signum) {
    pid_t tid = gettid();
    pid_t pid = getpid();
    pid_t ppid = getppid();
    printf("Thread %lu received SIGUSR1 (parent = %d) [pid=%d] {tid=%d}\n",
           (unsigned long)pthread_self(), ppid, pid, tid);
}

void* thread_function(void* arg) {
    while (1) {
        pause(); 
    }
    return NULL;
}

int main() {
    // Register SIGUSR1 handler
    signal(SIGUSR1, sigusr1_handler);

    // Create threads
    for (int i = 0; i < NUM_THREADS; ++i) {
        if (pthread_create(&threads[i], NULL, thread_function, NULL) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    pid_t tid = gettid(), pid = getpid(), ppid = getppid();
    printf("Parent process ID: %d, Process ID: %d, Main thread ID: %d\n", ppid, pid, tid);

    // Send SIGUSR1 to the process (main thread)
    kill(pid, SIGUSR1);

    // Send SIGUSR1 to thread 2
    pthread_kill(threads[2], SIGUSR1);

    // Wait for threads (this will never happen unless you stop them)
    for (int i = 0; i < NUM_THREADS; ++i) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
