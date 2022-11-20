#include <pthread.h>   // for threads compile with -pthread
#include <semaphore.h> // for semaphores
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // random number generator
#include <unistd.h>

pthread_mutex_t mutex;

int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
void *routine(void *arg) {
    int index = *((int *)arg);
    printf("Prime number from thread %d is %d\n", index, primes[index]);
    free(arg);
}

int sum = 0;
void routine2(void *arg) {
    for (int i = 0; i < 100000; i++) {
        pthread_mutex_lock(&mutex);
        sum++;
        pthread_mutex_unlock(&mutex);
    }
}

int main(int argc, char *argv[]) {
    pthread_t thread[10]; // Creating 10 threads
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < 10; i++) {
        int *thread_id = (int *)malloc(sizeof(int));
        *thread_id = i;
        pthread_create(&thread[i], NULL, &routine2, thread_id);
    }
    for (int i = 0; i < 10; i++) {
        pthread_join(thread[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    printf("Global sum is %d\n", sum);

    return 0;
}