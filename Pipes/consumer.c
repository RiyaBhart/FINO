#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#define FIFO_FILE "/tmp/myfifo"

int main() {
    int fd;
    char buffer[BUFSIZ];
    ssize_t num_bytes;

    // Open FIFO for reading
    fd = open(FIFO_FILE, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    while (1) {
        num_bytes = read(fd, buffer, BUFSIZ - 1);  // leave space for null-terminator
        if (num_bytes == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        buffer[num_bytes] = '\0'; // null-terminate
        printf("\nConsumer: Received message: %s", buffer);

        if (strncmp(buffer, "exit", 4) == 0) {
            break;
        }
    }

    close(fd);
    unlink(FIFO_FILE); // remove the FIFO file

    return 0;
}
