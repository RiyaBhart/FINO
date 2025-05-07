#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

volatile sig_atomic_t sigint_count = 0;

void sigint_handler(int signum) {
    sigint_count++;

    if (sigint_count == 1) {
        printf("\nCaught SIGINT (Ctrl+C). Press again to exit.\n");
    } else {
        printf("\nSecond SIGINT received. Exiting gracefully.\n");
        exit(0);
    }
}

int main() {
    if (signal(SIGINT, sigint_handler) == SIG_ERR) {
        printf("Error setting up SIGINT handler\n");
        return 1;
    }

    printf("Program running. Press Ctrl+C once to see a message, twice to exit.\n");

    while (1) {
        sleep(1);
    }

    return 0;
}
