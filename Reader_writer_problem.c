#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Shared data
int data = 0;           // The shared resource
int read_count = 0;     // Number of readers currently reading

// Mutexes and condition variables
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;      // Protect read_count
pthread_mutex_t write_mutex = PTHREAD_MUTEX_INITIALIZER; // Protect writing (resource)

// Reader function
void* reader(void* arg) {
    int id = *((int*)arg);
    free(arg);

    while (1) {
        // Entry section
        pthread_mutex_lock(&mutex);
        read_count++;
        if (read_count == 1) {
            // First reader locks the resource for writing (prevents writers)
            pthread_mutex_lock(&write_mutex);
        }
        pthread_mutex_unlock(&mutex);

        // Critical section: Reading
        printf("Reader %d: Reading data = %d\n", id, data);
        sleep(1); // Simulate reading time

        // Exit section
        pthread_mutex_lock(&mutex);
        read_count--;
        if (read_count == 0) {
            // Last reader unlocks the resource for writing
            pthread_mutex_unlock(&write_mutex);
        }
        pthread_mutex_unlock(&mutex);

        // Pause before next read
        sleep(rand() % 3);
    }
    return NULL;
}

// Writer function
void* writer(void* arg) {
    int id = *((int*)arg);
    free(arg);

    while (1) {
        // Writers lock the write_mutex directly
        pthread_mutex_lock(&write_mutex);

        // Critical section: Writing
        data++;
        printf("Writer %d: Writing data = %d\n", id, data);
        sleep(2); // Simulate writing time

        pthread_mutex_unlock(&write_mutex);

        // Pause before next write
        sleep(rand() % 4);
    }
    return NULL;
}

int main() {
    pthread_t r_threads[5], w_threads[2];

    // Create reader threads
    for (int i = 0; i < 5; i++) {
        int* id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&r_threads[i], NULL, reader, id);
    }

    // Create writer threads
    for (int i = 0; i < 2; i++) {
        int* id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&w_threads[i], NULL, writer, id);
    }

    // Join threads (in this infinite loop demo, it won't join)
    for (int i = 0; i < 5; i++)
        pthread_join(r_threads[i], NULL);
    for (int i = 0; i < 2; i++)
        pthread_join(w_threads[i], NULL);

    return 0;
}


