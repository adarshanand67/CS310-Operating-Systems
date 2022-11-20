//  Write a program in C that creates a child process,
//  waits for the termination of the child
//  and lists its PID, together with the state in which the process
//  was terminated (in decimal and hexadecimal)
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main() {
    int status;   // status of the child process
    pid_t pid;    // process id of the child process
    pid = fork(); // creates a child process
    if (pid == 0) {
        // child process created
        printf("Child process created with PID: %d\n", getpid());
        exit(0);
    } else {
        printf("Parent process created with PID: %d\n", getpid());
        wait(&status);                                                                                    // waits for the child process to terminate
        printf("Child process terminated with status %d - decimal & %x - hexadecimal\n", status, status); // prints the status of the child process
    }
    return 0;
}
/*
 Important code:
 - pid: process id
 - status: status of the child process
 - fork(): creates a child process
 - wait(&status): waits for the child process to terminate
 - getpid(): returns the process id of the current process
 - getppid(): returns the process id of the parent process
 - exit(): terminates the current process
 */
