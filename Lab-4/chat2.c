#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

struct data {
    char buff[100];
    int status, pid1, pid2;
};

struct data *ptr;

void handler(int signum) {
    if (signum == SIGUSR1) {
        printf("Received from User2: ");
        puts(ptr->buff);
    }
}

int main() {

    int pid = getpid(); /* get process id */

    int shmid; /* shared memory id */

    int key = 12345; /* key for shared memory */

    shmid = shmget(key, sizeof(struct data), IPC_CREAT | 0666); /* create shared memory */

    ptr = (struct data *)shmat(shmid, NULL, 0); /* attach shared memory */

    ptr->pid1 = pid;
    ptr->status = -1;

    signal(SIGUSR1, handler); /* register signal handler */

    while (1) {
        while (ptr->status != 1) /* wait for signal */
            continue;
        sleep(1);

        printf("Enter message as User1: "); /* get message from user */
        fgets(ptr->buff, 100, stdin);       /* get message from user */

        ptr->status = 0; /* set status to 0 */

        kill(ptr->pid2, SIGUSR2); /* send signal to other process */
    }

    shmdt((void *)ptr);            /* detach shared memory */
    shmctl(shmid, IPC_RMID, NULL); /* delete shared memory */
    return 0;
}
