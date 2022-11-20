#include <pthread.h>   // for threads compile with -pthread
#include <semaphore.h> // for semaphores
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // random number generator
#include <unistd.h>

int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void *routine(void *arg) {
    int index = *((int *)arg);
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        sum += primes[index + i];
    }
    printf("Local sum is %d\n", sum);
    *((int *)arg) = sum;
    return arg;
}

int main(int argc, char *argv[]) {
    pthread_t th[2];

    for (int i = 0; i < 2; i++) {
        int *thread_id = (int *)malloc(sizeof(int));
        *thread_id = i * 5;
        pthread_create(&th[i], NULL, &routine, thread_id);
    }

    int global_sum = 0;

    for (int i = 0; i < 2; i++) {
        int *sum;
        pthread_join(th[i], (void **)&sum);
        global_sum += *sum;
    }
    printf("Global sum is %d\n", global_sum);
}