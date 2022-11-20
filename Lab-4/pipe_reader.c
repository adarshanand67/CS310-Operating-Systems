#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/*

The pipe reader program will set up a named pipe using mkfifo() ,
open it read only, and read strings from it until it receives the string exit

Reader
Creating named pipe: /tmp/mypipe
Waiting for input...Got it: ’Thursday’
Waiting for input...Got it: ’OS lab 4
Waiting for input...Got it: ’exit’
Exiting

*/

int main() {
    int fd1; // Reader -> Writer
    int fd2; // Writer -> Reader
    char *myfifo = "/tmp/mypipe";
    char buf[100];
    /* open, read, and display the message from the FIFO */
    fd2 = open(myfifo, O_RDONLY);
    while (1) {
        read(fd2, buf, 100);
        printf("Waiting for input...Got it: ’%s’\n", buf);
        if (strcmp(buf, "exit") == 0) {
            printf("Exiting\n");
            break;
        }
    }
    close(fd2);
}