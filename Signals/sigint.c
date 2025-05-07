#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

FILE *temp = NULL;
char filename[] = "newfile.txt";

void handle_signal(int signum) {
    printf("Received signal. Cleaning up...\n");

    if (temp) {
        fclose(temp);
        printf("File closed\n");
    }

    if (remove(filename) == 0) {
        printf("Temp file '%s' deleted successfully\n", filename);
    } else {
        perror("Error deleting file");
    }

    exit(0);
}

int main() {
    temp = fopen(filename, "w");
    if (!temp) {
        perror("fopen failed");
        return 1;
    }

    signal(SIGINT, handle_signal);

    printf("Writing to temp file '%s'; press Ctrl+C to stop\n", filename);

    int counter = 1;
    while (1) {
        fprintf(temp, "Line %d: sample data...\n", counter++);
        fflush(temp);
        sleep(1);
    }

    return 0;
}
