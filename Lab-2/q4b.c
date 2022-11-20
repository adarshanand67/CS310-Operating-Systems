#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main(void) {
    int value = 1;
    pid_t PID = fork(); // create a child process
    if (PID >= 0) {
        if (PID == 0) { // child process
            printf("\n\nChild Process:\n Initial Value = %d", value);
            value = 5;
            printf("\nNew Value of value = %d", value);
            printf("\nAddress of value in child= %d", &value);
        } else { // parent process
            printf("\n\nParent process:\n Initial Value = %d", value);
            value = 10;
            printf("\nNew Value = %d", value);
            printf("\nAddress of value in child= %d", &value);
        }
    }
    return 0;
}
