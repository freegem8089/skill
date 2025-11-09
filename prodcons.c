#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>  // for sleep()
#include <time.h>    // for srand()

#define MaxItems 5     // Maximum items a producer can produce or a consumer can consume
#define BufferSize 5   // Size of the buffer

sem_t empty;
sem_t full;
pthread_mutex_t mutex;

int in = 0;
int out = 0;
int buffer[BufferSize];

void *producer(void *pno)
{
    int item;
    int id = *((int *)pno);

    for (int i = 0; i < MaxItems; i++) {
        item = rand() % 100;  // Produce a random item (0–99)
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        buffer[in] = item;
        printf("Producer %d: Insert Item %d at %d\n", id, buffer[in], in);
        in = (in + 1) % BufferSize;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);

        sleep(1); // simulate production delay
    }

    return NULL;
}

void *consumer(void *cno)
{
    int id = *((int *)cno);

    for (int i = 0; i < MaxItems; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        int item = buffer[out];
        printf("Consumer %d: Remove Item %d from %d\n", id, item, out);
        out = (out + 1) % BufferSize;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);

        sleep(1); // simulate consumption delay
    }

    return NULL;
}

int main()
{
    pthread_t pro[5], con[5];
    int a[5] = {1, 2, 3, 4, 5}; // numbering producers and consumers

    srand(time(NULL)); // seed random number generator

    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BufferSize);
    sem_init(&full, 0, 0);

    // Create producer threads
    for (int i = 0; i < 5; i++) {
        pthread_create(&pro[i], NULL, producer, &a[i]);
    }

    // Create consumer threads
    for (int i = 0; i < 5; i++) {
        pthread_create(&con[i], NULL, consumer, &a[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < 5; i++) {
        pthread_join(pro[i], NULL);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(con[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    printf("\nAll producers and consumers have finished.\n");
    return 0;
}
