#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int frv, pid; // fork return value, process id
    int status;   // status of the child process

    frv = fork(); // creates a child process
    if (frv > 0) {
        printf("I am in the parent, my process id  = %d, my parent's process id = %d, the child's process id  = %d and return value of the fork  = %d\n", getpid(), getppid(), frv, frv);
        pid = wait(&status);
        printf("I am in the parent after the child exited and the exited child's process id  = %d \n ", pid);
    }

    else {
        printf("I am in the child, my process id  = %d,  and my parents's process id = %d and return value of the fork  = %d\n", getpid(), getppid(), frv);
        exit(0);
    }
}