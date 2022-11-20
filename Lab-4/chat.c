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

    if (signum == SIGUSR2) {
        printf("Received from User1: ");
        puts(ptr->buff);
    }
}

int main() {

    int pid = getpid(); /* get process id */

    int shmid; /* shared memory id */

    int key = 12345; /* key for shared memory */

    shmid = shmget(key, sizeof(struct data), IPC_CREAT | 0666); /* create shared memory */

    ptr = (struct data *)shmat(shmid, NULL, 0); /* attach shared memory */

    ptr->pid2 = pid; /* store pid in shared memory */

    ptr->status = -1;

    signal(SIGUSR2, handler);

    while (1) {
        sleep(1);

        printf("Enter message as User2: ");
        fgets(ptr->buff, 100, stdin); /* get message from user */
        ptr->status = 1;

        kill(ptr->pid1, SIGUSR1); /* send signal to other process */

        while (ptr->status == 1)
            continue;
    }

    shmdt((void *)ptr); /* detach shared memory */
    return 0;
}
