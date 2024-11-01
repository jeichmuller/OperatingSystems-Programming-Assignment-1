// Jay Eichmuller
// Operating Systems Programming Assignment #1
// shared.h

#ifndef SHARED_H
#define SHARED_H


#include <semaphore.h>

// Define the max size of the table
#define tableSize 2

// Structure to hold the shared data and semaphores
struct sem {
    char table[tableSize];    // table for storing items
    sem_t empty;          // Semaphore to count empty slots
    sem_t full;           // Semaphore to count full slots
};

#endif // SHARED_H
