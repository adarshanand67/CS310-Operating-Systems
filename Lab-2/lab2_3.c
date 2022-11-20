/* ----------------------------------------------------------------- */
/* PROGRAM  fork-01.c                                                */
/*    This program illustrates the use of fork() and getpid() system */
/* calls.  Note that write() is used instead of printf() since the   */
/* latter is buffered while the former is not.                       */
/* ----------------------------------------------------------------- */

#include <stdio.h>
#include <string.h>
#include <sys/types.h>

#define MAX_COUNT 200
#define BUF_SIZE 100

void main(void) {
    pid_t pid;          /* process id */
    int i;              /* loop counter */
    char buf[BUF_SIZE]; /* buffer for write() */

    fork(); /* create child process */
    pid = getpid();
    for (i = 1; i <= MAX_COUNT; i++) {
        sprintf(buf, "This line is from pid %d, value = %d\n", pid, i); // sprintf() is used to format the string
        write(1, buf, strlen(buf));                                     // write() is used to write to the standard output
                                                                        // printf("%s",buf);
    }
}
