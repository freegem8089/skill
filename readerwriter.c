#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

sem_t mutex, wrt;
int sharedvar = 99;
int readercount = 0;
pthread_t writers[5], readers[5];

void *reader(void *param)
{
    long id = (long)param;

    sem_wait(&mutex);
    readercount++;
    if (readercount == 1)
        sem_wait(&wrt); // first reader blocks writers
    sem_post(&mutex);

    printf("\nReader %ld is READING sharedvar = %d", id, sharedvar);
    sleep(1); // simulate reading time

    sem_wait(&mutex);
    readercount--;
    if (readercount == 0)
        sem_post(&wrt); // last reader unblocks writers
    sem_post(&mutex);

    printf("\nReader %ld is DONE reading", id);
    return NULL;
}

void *writer(void *param)
{
    long id = (long)param;

    printf("\nWriter %ld is TRYING to enter", id);
    sem_wait(&wrt);

    printf("\nWriter %ld has ENTERED CS", id);
    sharedvar++;
    printf("\nWriter %ld CHANGED sharedvar to %d", id, sharedvar);
    sleep(1); // simulate writing time

    sem_post(&wrt);
    printf("\nWriter %ld has LEFT CS", id);

    return NULL;
}

int main()
{
    int n, i;
    printf("Enter number of readers/writers (max 5): ");
    scanf("%d", &n);
    if (n > 5) n = 5;

    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    for (i = 0; i < n; i++)
    {
        pthread_create(&readers[i], NULL, reader, (void *)(long)(i + 1));
        pthread_create(&writers[i], NULL, writer, (void *)(long)(i + 1));
    }

    for (i = 0; i < n; i++)
    {
        pthread_join(readers[i], NULL);
        pthread_join(writers[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&wrt);

    printf("\nAll threads finished. Final sharedvar = %d\n", sharedvar);
    return 0;
}
