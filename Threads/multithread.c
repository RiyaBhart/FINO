#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct{
int* arr;
int size;
} ThreadData;


void *findavg(void*arg){
ThreadData* data = (ThreadData*)arg;
double* avg = malloc(sizeof(double));
int sum = 0;
for(int i=0;i<data->size;i++){
sum+=data->arr[i];
*avg = (double)sum/data->size;
return (void*)avg;
}
}
void *findmax(void *arg){
ThreadData* data = (ThreadData*)arg;
int* max = malloc(sizeof(int));
*max = data->arr[0];
for(int i=0;i<data->size;i++){
if(*max<data->arr[i]){
*max = data->arr[i];
}
}
return (void*)max;
}

void *findmin(void *arg){
ThreadData* data = (ThreadData*)arg;
int* min = malloc(sizeof(int));
*min = data->arr[0];
for(int i=0;i<data->size;i++){
if(*min>data->arr[i]){
*min = data->arr[i];
}
}
return (void*)min;
}

int main(int argc, char* argv[]){
if(argc<2){
printf("usage: %s num1 num2 num3 ...\n",argv[0]);
return 1;
}
int size = argc-1;
int* numbers = malloc(size*sizeof(int));
for(int i=0;i<size;i++){
numbers[i]=atoi(argv[i+1]);
}

ThreadData data = {numbers, size};
pthread_t avgthread,maxthread,minthread;

void* avgresult;
void* maxresult;
void* minresult;

pthread_create(&avgthread, NULL, findavg,&data);
pthread_create(&maxthread,NULL,findmax,&data);
pthread_create(&minthread,NULL,findmin,&data);

pthread_join(avgthread,&avgresult);
pthread_join(maxthread,&maxresult);
pthread_join(minthread,&minresult);

printf("Average : %.2f\n",*(double*)avgresult);
printf("maximum : %d\n",*(int*)maxresult);
printf("minimum : %d\n",*(int*)minresult);

free(avgresult);
free(maxresult);
free(minresult);
free(numbers);

return 0;
}
labtask2.c
Displaying labtask2.c.Previous 
