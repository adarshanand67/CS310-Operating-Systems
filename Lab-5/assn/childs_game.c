/*
Write a C program to implement the following game.
The parent program P first creates two pipes and then spawns two child processes
C and D. One of the two pipes is meant for communication between P and C and the
other one for communication between P and D. Now a loop runs as follows.
In each iteration (also called a round), P first randomly chooses one of the
flags MIN or MAX. The choices randomly varies from one iteration to another.
Each of the two child processes C and D generates a random positive integer and
sends that to P via its pipe. P reads the two integers. Let these be c and d
respectively. If P has chosen MIN, then the child which sends the smaller of c
and d gets one point and if P has chosen MAX, then the child which sends the
larger of c and d gets one point. If c == d, then this round is ignored. The
child process which first obtains 10 points wins the game.
When the game ends, P sends a user-defined signal to both C and D and the child
processes exit after handling the signal (in order to know who was the winner).
After C and D exits, the parent process also exists. During each iteration of
the game, P should also print appropriate messages like P's choice of flag,
the integers received from C and D, which child gets the point, the current
scores of C and D in order to let the user know how the game is going on.
*/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define BUFSIZE 20           /* Buffer size */
#define WINNING_CONDITION 10 /* Winning condition */

static int stop = 0; /* Flag to stop the game */

void end_process(int sig) { /* Custom signal handler to handle the termination of game */
    if (sig == SIGUSR1) {
        stop = 1;
    } else if (sig == SIGUSR2) {
        stop = 2;
    }
}

int main() {
    pid_t pid1, pid2; /* Process IDs */

    int fd1[2], fd2[2]; /* Create the pipe descriptors */
    pipe(fd1);          /* Pipe 1 */
    pipe(fd2);          /* Pipe 2 */

    signal(SIGUSR1, end_process); /* Assign the custom signal handler to SIGUSR1 signal */
    signal(SIGUSR2, end_process); /* Assign the custom signal handler to SIGUSR2 signal */

    if ((pid1 = fork()) == 0) { /* Child 1 */

        srand((unsigned int)time(NULL) ^ getpid()); /* Seed the random number generator */
        close(fd1[0]);

        while (!stop) {
            int n = rand() % 100;         /* Generate a random number */
            char line[BUFSIZE];           /* Buffer to store the number */
            sprintf(line, "%d", n);       /* Convert the number to string */
            write(fd1[1], line, BUFSIZE); /* Write the number to the pipe */
        }

        if (stop == 1) { /* If the game is stopped by SIGUSR1 */
            printf("C: I am the winner\n");
        } else if (stop == 2) {
            printf("C: D is the winner\n");
        }

    } else {
        if ((pid2 = fork()) == 0) {

            srand((unsigned int)time(NULL) ^ getpid()); /* Seed the random number generator */
            close(fd2[0]);

            while (!stop) {
                int n = rand() % 100;         /* Generate a random number */
                char line[BUFSIZE];           /* Buffer to store the number */
                sprintf(line, "%d", n);       /* Convert the number to string */
                write(fd2[1], line, BUFSIZE); /* Write the number to the pipe */
            }

            if (stop == 1) {
                printf("D: C is the winner\n");
            } else if (stop == 2) {
                printf("D: I am the winner\n");
            }

        } else {
            /*Parent Process*/
            close(fd1[1]); /* Close the write end of pipe 1 */
            close(fd2[1]);

            srand((unsigned int)time(NULL) ^ getpid()); /* Seed the random number generator */
            int round = 1;                              /* Round counter */
            int score1 = 0, score2 = 0;                 /* Score counters */
            char line[BUFSIZE];
            int num1, num2, choice;

            while (1) {

                if (score1 == WINNING_CONDITION || score2 == WINNING_CONDITION) /* If any of the scores reaches the winning condition */
                    break;
                printf("Round number: %d\n", round++);
                choice = rand() % 2; /* Randomly choose MIN or MAX */

                read(fd1[0], line, BUFSIZE);                   /* Read from pipe 1 */
                sscanf(line, "%d", &num1);                     /* Convert the string to integer */
                printf("Integer received from C: %d\n", num1); /* Print the number received from C */

                read(fd2[0], line, BUFSIZE); /* Read from pipe 2 */
                sscanf(line, "%d", &num2);
                printf("Integer received from D: %d\n", num2);

                if (choice) { /* If choice is MAX */
                    printf("P's choice of flag: MIN\n");
                } else {
                    printf("P's choice of flag: MAX\n");
                }

                if (num1 == num2) /* If both the numbers are equal */
                    printf("This round is a tie!\n");
                else if ((num1 < num2 && choice) || (num1 > num2 && !choice)) { /* If C wins */
                    printf("C gets the point\n");
                    score1++;
                } else {
                    printf("D gets the point\n"); /* If D wins */
                    score2++;
                }
                printf("Updated scores: C = %d, D = %d\n\n", score1, score2); /* Print the updated scores */
            }

            if (score1 > score2) { /* If C wins */
                kill(pid1, SIGUSR1);
                kill(pid2, SIGUSR1);
            } else { /* If D wins */
                kill(pid1, SIGUSR2);
                kill(pid2, SIGUSR2);
            }

            waitpid(pid1, &num1, 0); /* Wait for the child processes to exit */
            waitpid(pid2, &num2, 0); /* Wait for the child processes to exit */
        }
    }
    return 0;
}

// The idea is to use a single pipe to communicate between parent and child processes. The parent process writes the random number to the pipe and the child process reads it from the pipe. The parent process also writes the flag to the pipe and the child process reads it from the pipe. The child process then compares the two numbers and prints the result.