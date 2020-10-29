#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <string.h>

const int MAX_MESSAGE_SIZE = 65565;
const char* FILENAME = "08-4.c";

int pipe_descriptors[2];
int semid;

int open_pipes() {
    if (pipe(pipe_descriptors) < 0)
    {
        printf("Can\'t open pipe\n");
        return -1;
    }
    return 0;
}
void open_sem() {
    key_t key = ftok(FILENAME, 0);
    semid = semget(key, 1, 0666 | IPC_CREAT);
}

void A(int n) {
    struct sembuf unlock;
    unlock.sem_op = n;
    unlock.sem_flg = 0;
    unlock.sem_num = 0;
    semop(semid, &unlock, 1);
}

void D(int n) {
    struct sembuf lock;
    lock.sem_op = -n;
    lock.sem_flg = 0;
    lock.sem_num = 0;
    semop(semid, &lock, 1);
}

void Z() {
    struct sembuf lock;
    lock.sem_op = 0;
    lock.sem_flg = 0;
    lock.sem_num = 0;
    semop(semid, &lock, 1);
}

void write_to_pipe(char *data) {
    write(pipe_descriptors[1], data, strlen(data));
    D(1);
}

void read_from_pipe(char *buffer) {
    read(pipe_descriptors[0], buffer, MAX_MESSAGE_SIZE);
    A(1);
    Z();
}

void parent_process() {
    char result[MAX_MESSAGE_SIZE];
    write_to_pipe("Hello, Child!\n");
    read_from_pipe(result);
    printf("%s", result);
}

void child_process() {
    char result[MAX_MESSAGE_SIZE];
    read_from_pipe(result);
    write_to_pipe("Hello, Parent!\n");
    printf("%s", result);
}

int main()
{
    if (open_pipes() < 0)
        return -1;

    open_sem();
    int result = fork();

    if (result < 0)
    {
        printf("Can\'t fork child\n");
        return -1;
    } else if (result > 0)
        parent_process();
    else
        child_process();

    return 0;
}
