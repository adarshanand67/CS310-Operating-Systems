#include <pthread.h>   // for threads compile with -pthread
#include <semaphore.h> // for semaphores
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // random number generator
#include <unistd.h>

#define N 14
sem_t sem;
sem_t binarySemaphores;

void *thread_function(void *arg) {
    int index = *((int *)arg);
    sem_wait(&sem); // wait for semaphore
    sleep(1);
    printf("Hello from thread %d\n", index);
    sem_post(&sem); // release the semaphore
}

void *loginQueue(void *arg) {
    int index = *((int *)arg);
    sem_wait(&sem);
    printf("+Login %d is now logged in\n", index);
    sleep(rand() % 5 + 1);
    printf("-Login %d is now logged out\n", index);
    sem_post(&sem);
}

void *binarySemaphore(void *arg) {
    // Using binary semaphores to implement a mutex
    int index = *((int *)arg);
    sem_wait(&binarySemaphores);
    printf("Thread %d is now in the critical section\n", index);
    sleep(rand() % 5 + 1);
    printf("Thread %d is now leaving the critical section\n", index);
    sem_post(&binarySemaphores);
}

int main(int argc, char const *argv[]) {
    pthread_t thread[N];
    sem_init(&sem, 0, 6);
    sem_init(&binarySemaphores, 0, 1);

    for (int i = 0; i < N; i++) {
        int *thread_id = malloc(sizeof(int));
        *thread_id = i;
        pthread_create(&thread[i], NULL, binarySemaphore, thread_id);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(thread[i], NULL);
    }
    return 0;
}
