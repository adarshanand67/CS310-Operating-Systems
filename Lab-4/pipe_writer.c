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
The writer will
open the named pipe file, read strings from the user and write them to the named pipe.
When the user enters exit , the program will write the string to the pipe and then exit.

Writer:
mypc:$ ./pipe
Writer
Opening named pipe: /tmp/mypipe
Enter Input: Thursday
Writing buffer to pipe...done
Enter Input: OS lab 4
Writing buffer to pipe...done
Enter Input: exit
Writing buffer to pipe...done
Exiting
*/
int main() {
    int fd1; // Reader -> Writer
    int fd2; // Writer -> Reader
    char *myfifo = "/tmp/mypipe";
    mkfifo(myfifo, 0777);
    char buf[100];
    /* open, read, and display the message from the FIFO */
    fd1 = open(myfifo, O_WRONLY);
    while (1) {
        printf("Enter Input: ");
        scanf("%s", buf);
        write(fd1, buf, strlen(buf) + 1);
        printf("Writing buffer to pipe...done\n");
        if (strcmp(buf, "exit") == 0) {
            break;
        }
    }
    close(fd1);
    return 0;
}