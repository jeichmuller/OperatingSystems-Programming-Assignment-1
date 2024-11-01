// Jay Eichmuller
// Operating Systems Programming Assignment #1
// consumer.c

#include "shared.h"
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>

int main() {
    // Open the shared memory table
    int open = shm_open("/table", O_RDWR, 0);
    if (open < 0) {
        perror("shm_open");
        return 1;
    }
    // Construct the semaphore
    struct sem *semaphore = mmap(NULL, sizeof(struct sem) + sizeof(char) * tableSize, PROT_READ | PROT_WRITE, MAP_SHARED, open, 0);
    if (semaphore == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    int o = 0;
    while (1) {
        sem_wait(&semaphore->full);
        char j = semaphore->table[o]; // Consume the tokens
        if (j=='\0') break; // If terminator end program
        printf("Consumer got item on %d: %c\n", o, j);
        fflush(stdout);
        o = (o + 1) % tableSize;
        sem_post(&semaphore->empty);
    }

    shm_unlink("/table"); // unlink
    return 0;
}
