/* A simple readers/writers program using a one-word shared memory. */
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>

#define SIZE sizeof(int) /* size of [int] integer */
#define run_length 10    /* number of iterations in test run */

int main(void) {
    pid_t pid;             /* variable to record process id of child */
    caddr_t shared_memory; /* shared memory base address */
    int i_parent, i_child; /* index variables */
    int value;             /* value read by child */

    /* set up shared memory segment */
    shared_memory = mmap(0, SIZE, PROT_READ | PROT_WRITE,
                         MAP_ANONYMOUS | MAP_SHARED, -1, 0);
    if (shared_memory == (caddr_t)-1) {
        perror("error in mmap while allocating shared memory\n");
        exit(1);
    }

    if ((pid = fork()) < 0) /* apply fork and check for error */
    {
        perror("error in fork");
        exit(1);
    }

    if (0 == pid) { /* processing for child */
        printf("The child process begins.\n");
        for (i_child = 0; i_child < run_length; i_child++) {
            // sleep(1); /* wait for memory to be updated */
            value = *shared_memory;
            printf("Child's report:  current value = %2d\n", value);
        }
        printf("The child is done\n");
    } else { /* processing for parent */
        printf("The parent process begins.\n");
        for (i_parent = 0; i_parent < run_length; i_parent++) {
            *shared_memory = i_parent * i_parent; /* square into shared memory */
            printf("Parent's report: current index = %2d\n", i_parent);
            // sleep(1); /* wait for child to read value */
        }
        wait(pid); /* wait for child to finish */
        printf("The parent is done\n");
    }
    exit(0);
}

int main2() {
    pid_t pid;             /* variable to record process id of child */
    caddr_t shared_memory; /* shared memory base address */
    int i_parent, i_child; /* index variables */
    int value;             /* value read by child */

    // Initialize the shared memory location in main memory to -1 before the fork operation.
    shared_memory = mmap(-1, SIZE, PROT_READ | PROT_WRITE,
                         MAP_ANONYMOUS | MAP_SHARED, -1, 0); // -1 is the initial value

    if (shared_memory == (caddr_t)-1) {
        perror("error in mmap while allocating shared memory\n");
        exit(1);
    }

    if ((pid = fork()) < 0) /* apply fork and check for error */
    {
        perror("error in fork");
        exit(1);
    }

    if (0 == pid) { /* processing for child */
        printf("The child process begins.\n");
        for (i_child = 0; i_child < run_length; i_child++) {
            // Replace the sleep statement for the child by a spinlock that checks that the shared
            // memory contains a nonnegative value. At the end of the child’s loop, the shared
            // memory location should be reset to -1.

            while (*shared_memory == -1) {
                // spinlock
            }
            value = *shared_memory;
            printf("Child's report:  current value = %2d\n", value);
            *shared_memory = -1;
        }
        printf("The child is done\n");
    } else { /* processing for parent */
        printf("The parent process begins.\n");
        for (i_parent = 0; i_parent < run_length; i_parent++) {

            while (*shared_memory != -1) {
                // spinlock
            }
            *shared_memory = i_parent * i_parent;
            printf("Parent's report: current index = %2d\n", i_parent);
        }
        wait(pid); /* wait for child to finish */
        printf("The parent is done\n");
    }
}