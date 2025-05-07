#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 10000000
#define THREADS 10

float *A,*B,*C;

typedef struct{
int start;
int end;
} ThreadData;

void* addarrays(void* arg){
ThreadData* data = (ThreadData*)arg;
int start = data->start;
int end = data->end;

for(int i=start;i<end;i++){
C[i] = A[i]+B[i];
}
pthread_exit(NULL);
}

int main(){

pthread_t threads[THREADS];
ThreadData threaddata[THREADS];

A = (float*)malloc(SIZE*sizeof(float));
B = (float*)malloc(SIZE*sizeof(float));
C = (float*)malloc(SIZE*sizeof(float));

for(int i=0;i<SIZE ;i++){
A[i]=i*0.1f;
B[i]=i*0.2f;
}

int chunk = SIZE/THREADS;
for(int i=0;i<THREADS;i++){
threaddata[i].start = i*chunk;
threaddata[i].end=(i==THREADS-1)?SIZE:(i+1)*chunk;
pthread_create(&threads[i],NULL,addarrays,&threaddata[i]);
}
for(int i=0;i<THREADS;i++){
pthread_join(threads[i],NULL);
}
printf("C[0] = %f\n",C[0]);
printf("C[1] = %f\n",C[1]);
printf("C[SIZE-1] = %f\n",C[SIZE-1]);

free(A);
free(B);
free(C);

return 0;
}
