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

    // Create shared memory object
    shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(1);
    }

    // Resize the memory object
    ftruncate(shm_fd, sizeof(SharedData));

    // Map into memory
    data = mmap(0, sizeof(SharedData), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (data == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    // Write message
    printf("Producer: Enter a message: ");
    fgets(data->message, sizeof(data->message), stdin);
    data->message[strcspn(data->message, "\n")] = '\0';

    data->ready = 1;
    printf("Producer: Message written to shared memory.\n");

    // Cleanup
    munmap(data, sizeof(SharedData));
    close(shm_fd);

    return 0;
}
