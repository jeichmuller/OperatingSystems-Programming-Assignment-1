// Jay Eichmuller
// Operating Systems Programming Assignment #1
// producer.c

#include "shared.h"
#include <fcntl.h> 
#include <sys/mman.h>
#include <sys/stat.h> 
#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

int main() {
    shm_unlink("/table"); // unlink table incase of unsuccessful exit previously
    // Open the shared memory, if unsuccessful exit
    int open = shm_open("/table", O_CREAT | O_EXCL | O_RDWR, S_IRUSR | S_IWUSR);
    if (open < 0) {
        perror("shm_open");
        return 1;
    }

    // Set size of shared memory table
    if (ftruncate(open, sizeof(struct sem) + sizeof(char) * tableSize) == -1) {
        perror("ftruncate");
        return 1;
    }
    // Construct the semaphore
    struct sem *semaphore = mmap(NULL, sizeof(struct sem) + sizeof(char) * tableSize, PROT_READ | PROT_WRITE, MAP_SHARED, open, 0);
    if (semaphore == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    sem_init(&semaphore->empty, 1, tableSize);
    sem_init(&semaphore->full, 1, 0);

    char c = 'a';
    int j = 0;
    while(1) {
        sem_wait(&semaphore->empty);
        semaphore->table[j] = c; // Produced char put into table
        printf("Producer sent item on %d: %c\n", j, c);
        fflush(stdout);
        j = (j + 1) % tableSize;
        if (c == 'z'){ // doesnt need to be here but dont want it infinitely producing
            break;
        }
        ++c;
        sem_post(&semaphore->full);
    }
    sem_wait(&semaphore->empty);
    semaphore->table[j] = '\0'; // A terminator value
    sem_post(&semaphore->full); 

    sleep(1);
    shm_unlink("/table"); // unlink table
    return 0;
}
