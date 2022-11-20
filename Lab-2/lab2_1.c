#include <stdio.h>
#include <sys/types.h> //includes various data type declarations
                       // https://pubs.opengroup.org/onlinepubs/009696899/basedefs/sys/types.h.html
#include <sys/wait.h>  //includes declarations for waiting
                       // https://pubs.opengroup.org/onlinepubs/009604599/basedefs/sys/wait.h.html
#include <stdlib.h>
#include <unistd.h> //includes standard symbolic constants and types
                    // provides access to the POSIX  operating system API
// https://pubs.opengroup.org/onlinepubs/7908799/xsh/unistd.h.html

int main() {

    int pid;    // process id
    int status; // status of the child process

    pid = fork(); // creates a child process
    if (pid > 0) {
        pid = wait(&status); // waits for the child process to finish
                             // and returns the status of the child process
    } else {
        execlp("ls", "", NULL); // executes the ls command
        exit(0);                // exits the child process
    }
}
