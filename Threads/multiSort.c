#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define size 10
int arr[10] = {5, 3, 6, 1, 6, 9, 0, 3, 7, 8};

typedef struct {
    int start;
    int end;
} SortArgs;

void* sort(void* args) {
    SortArgs *sa = (SortArgs*) args;
    int start = sa->start;
    int end = sa->end;

    // Bubble sort
    for (int i = start; i < end - 1; ++i) {
        for (int j = start; j < end - 1 - (i - start); ++j) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    pthread_exit(NULL);
}

void* merge(void* arg) {
    int temp[size];
    int i = 0;
    int j = size / 2;
    int k = 0;

    while (i < size / 2 && j < size) {
        if (arr[i] < arr[j]) {
             temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while (i < size / 2) temp[k++] = arr[i++];
    while (j < size)     temp[k++] = arr[j++];

    for (int i = 0; i < size; i++) {
        arr[i] = temp[i];
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t t1, t2;

    SortArgs arg1 = {0, size / 2};
    SortArgs arg2 = {size / 2, size};

    printf("Original array:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    pthread_create(&t1, NULL, sort, &arg1);
    pthread_create(&t2, NULL, sort, &arg2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_t mergeThread;
    pthread_create(&mergeThread, NULL, merge, NULL);
    pthread_join(mergeThread, NULL);

    printf("Sorted array:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
