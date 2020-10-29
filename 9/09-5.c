#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <zconf.h>

const char* PATHNAME = "./09-5.c";

int msqid;

struct semaphore
{
    long mtype;
};

void open_messages() {
    key_t key = ftok(PATHNAME, 0);

    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0){
        printf("Can\'t get msqid\n");
        exit(-1);
    }
}

void P() {
    struct semaphore sem;
    msgsnd(msqid, (struct semaphore *) &sem, 0, 0);
}

void V() {
    struct semaphore sem;
    msgrcv(msqid, (struct semaphore *) &sem, 0, 0, 0);
}

int main(void)
{
    open_messages();

//    P(); // Если раскомментировать, то программа не будет зависать

    // На операции V программа зависнет
    V(); // Если убрать, то программа не будет зависать

    return 0;
}
