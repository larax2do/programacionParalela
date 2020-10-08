#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


//Variables globales que se pueden acceder de todos los threads
int thread_count;
void* Hello(void* rank);//FUncion de Thread
int main(int argc, char* argv[]) 
{
    long thread; // Use long in case of a 64 − bit system 
    pthread_t* thread_handles;

    // Get number of threads from command line 
    thread_count = strtol(argv[1], NULL, 10);
    thread_handles = malloc(thread_count*sizeof(pthread_t));
    for (thread = 0; thread < thread_count; thread++)
    {
        pthread_create(&thread_handles[thread], NULL,
        Hello, (void*) thread);
    }
    printf("Hola del thread principal\n");
    for (thread = 0; thread < thread_count; thread++)
    {
        pthread_join(thread_handles[thread], NULL);
    }


    free(thread_handles);
    return 0;
}

void* Hello(void* rank)
{
    long my_rank = (long) rank; // Use long in case of 64 − bit system */
    printf("Hello from thread %ld of %d\n", my_rank, thread_count);
    return NULL;
}

