#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5
#define MAX_ROUNDS 3   // 🔥 control how much output you want

sem_t chopstick[N];
sem_t room;

void think(int i) {
    printf("Philosopher %d is thinking.\n", i);
    sleep(1);
}

void eat(int i) {
    printf("Philosopher %d is eating.\n", i);
    sleep(1);
}

void* philosopher(void* num) {
    int i = *(int*)num;

    for (int j = 0; j < MAX_ROUNDS; j++) {   // ✅ limited loop
        think(i);

        sem_wait(&room);

        sem_wait(&chopstick[(i + 1) % N]);
        printf("Philosopher %d picked up right fork %d.\n", i, (i + 1) % N);

        sem_wait(&chopstick[i]);
        printf("Philosopher %d picked up left fork %d.\n", i, i);

        eat(i);

        sem_post(&chopstick[i]);
        sem_post(&chopstick[(i + 1) % N]);

        printf("Philosopher %d put down forks %d and %d.\n",
               i, i, (i + 1) % N);

        sem_post(&room);
    }

    return NULL;
}

int main() {
    pthread_t phil[N];
    int phil_num[N];

    for (int i = 0; i < N; i++) {
        sem_init(&chopstick[i], 0, 1);
        phil_num[i] = i;
    }

    sem_init(&room, 0, N - 1);

    for (int i = 0; i < N; i++) {
        pthread_create(&phil[i], NULL, philosopher, &phil_num[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(phil[i], NULL);
    }

    return 0;
}
