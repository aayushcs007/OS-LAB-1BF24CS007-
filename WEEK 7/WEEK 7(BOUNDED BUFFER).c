#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define MAX_ITEMS 15

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

// Semaphores
sem_t empty;
sem_t full;
sem_t mutex;

// Simulate producing an item
int produce_item(int i) {
    return i;
}

// Simulate consuming an item
void consume_item(int item, int index) {
    printf("Consumed: %d from buffer[%d]\n", item, index);
}

// Producer function
void* producer(void* arg) {
    int next_produced;

    for (int i = 0; i < MAX_ITEMS; i++) {
        // produce an item
        next_produced = produce_item(i);

        sem_wait(&empty);   // check for empty slot
        sem_wait(&mutex);   // enter critical section

        buffer[in] = next_produced;
        printf("Produced: %d at buffer[%d]\n", next_produced, in);
        in = (in + 1) % BUFFER_SIZE;

        sem_post(&mutex);   // exit critical section
        sem_post(&full);    // increase filled slots

        usleep(100000);
    }
    return NULL;
}

// Consumer function
void* consumer(void* arg) {
    int next_consumed;

    for (int i = 0; i < MAX_ITEMS; i++) {
        sem_wait(&full);    // check if item available
        sem_wait(&mutex);   // enter critical section

        next_consumed = buffer[out];
        int index = out;
        out = (out + 1) % BUFFER_SIZE;

        sem_post(&mutex);   // exit critical section
        sem_post(&empty);   // increase empty slots

        consume_item(next_consumed, index);

        usleep(150000);
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;

    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE); // initially all slots empty
    sem_init(&full, 0, 0);            // initially no items
    sem_init(&mutex, 0, 1);           // binary semaphore (mutex)

    // Create threads
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    // Destroy semaphores
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}
