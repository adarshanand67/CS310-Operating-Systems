/*
1. Consider the following problem: A program is to be written to print all numbers between
1 and 1000 (inclusive) that are not (evenly) divisible by either 2 or 3. This problem is to
be solved using three processes (P0, P1, P2) and two one-integer buffers (B0 and B1)
as follows:
1. P0 is to generate the integers from 1 to 1000, and place them in B0 one at a time.
After placing 1000 in the buffer, P0 places the sentinel 0 in the buffer, and terminates.
2. P1 is to read successive integers from B0. If a value is not divisible by 2, the value is
placed in B1. If the value is positive and divisible by 2, it is ignored. If the value is 0, 0 is
placed in B1, and P1 terminates.
3. P2 is to read successive integers from B1. If a value is not divisible by 3, it is printed.
If the value is positive and divisible by 3, it is ignored. If the value is 0, P2 terminates.
Write a program to implement P0, P1, and P2 as separate processes and B0 and B1 as
separate pieces of shared memory – each the size of just one integer. Use semaphores
to coordinate processing. Access to B0 should be independent of access to B1; for
example, P0 could be writing into B0 while either P1 was writing into B1 or P2 was
reading.
*/

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

// Declare the semaphores
sem_t s0;
sem_t s1;
sem_t s2;

// Declare the shared memory
int B0;
int B1;
short flag = 1;

void *processP0() {
    // P0 is to generate the integers from 1 to 1000, and place them in B0 one at a time.
    for (int i = 1; i <= 1000; i++) {
        // wait
        sem_wait(&s0);
        B0 = i; // place the value in B0
        // signal
        sem_post(&s1);
    }
    flag = 0; // set the flag to 0
    sem_post(&s1);
    sem_post(&s2);
    pthread_exit(NULL);
}

void *processP1() {
    // P1 is to read successive integers from B0. If a value is not divisible by 2, the value is placed in B1.
    // If the value is positive and divisible by 2, it is ignored. If the value is 0, 0 is placed in B1, and P1 terminates.
    while (flag) {
        // wait
        sem_wait(&s1);
        if ((B0 % 2) != 0) { // if the value is not divisible by 2
            B1 = B0;
            // signal
            sem_post(&s2);
        } else {
            // signal
            sem_post(&s0);
        }
    }
    pthread_exit(NULL);
}

void *processP2() {
    // P2 is to read successive integers from B1. If a value is not divisible by 3, it is printed.
    // If the value is positive and divisible by 3, it is ignored. If the value is 0, P2 terminates.
    while (flag) {
        // wait
        sem_wait(&s2);
        if ((B1 % 3) > 0) {
            printf("%d ", B1); // print the value
        }
        // signal
        sem_post(&s0);
    }
    pthread_exit(NULL);
}

int main() {
    // Initialize the semaphores
    sem_init(&s0, 0, 1);
    sem_init(&s1, 0, 0);
    sem_init(&s2, 0, 0);

    // TODO - Do it with Process instead of Thread

    pid_t pid1, pid2, pid3;
    pid1 = fork();
    if (pid1 == 0) {
        printf("Created process P0");
        processP0();
    } else {
        pid2 = fork();
        if (pid2 == 0) {
            printf("Created process P1");
            processP1();
        } else {
            pid3 = fork();
            if (pid3 == 0) {
                printf("Created process P2");
                processP2();
            }
        }
    }

    // pthread_t p0, p1, p2;
    // pthread_create(&p0, NULL, processP0, NULL);
    // pthread_create(&p1, NULL, processP1, NULL);
    // pthread_create(&p2, NULL, processP2, NULL);

    // pthread_join(p0, NULL);
    // pthread_join(p1, NULL);
    // pthread_join(p2, NULL);

    sem_destroy(&s0);
    sem_destroy(&s1);
    sem_destroy(&s2);
    return 0;
}