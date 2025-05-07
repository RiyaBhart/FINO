#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

#define SHM_NAME "/my_shm"
#define SIZE 1024

typedef struct {
    int ready;
    char message[SIZE - sizeof(int)];
} SharedData;

int main() {
    int shm_fd;
    SharedData *data;

    // Open the existing shared memory
    shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(1);
    }

    // Map into memory
    data = mmap(0, sizeof(SharedData), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (data == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    // Wait for message
    while (!data->ready) {
        usleep(100000); // sleep 100ms
    }

    printf("Consumer: Received message: %s\n", data->message);

    // Cleanup
    munmap(data, sizeof(SharedData));
    close(shm_fd);
    shm_unlink(SHM_NAME); // optional: remove shared memory

    return 0;
}
