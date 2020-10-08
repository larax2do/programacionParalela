#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

const int MAX_THREADS = 1024;
const int MSG_MAX = 100;

//Variables globales
int thread_count;
char** messages;
pthread_mutex_t mutex;
pthread_mutex_t mutexm;

void Usage(char* prog_name);
void *Send_msg(void* rank);  //

int main(int argc, char* argv[]) {
   long       thread;
   pthread_t* thread_handles; 

   //if (argc != 2) Usage(argv[0]);
   thread_count = strtol(argv[1], NULL, 10);
   //if (thread_count <= 0 || thread_count > MAX_THREADS) Usage(argv[0]);

   thread_handles = (pthread_t*) malloc (thread_count*sizeof(pthread_t));
   pthread_mutex_init(&mutex, NULL);
   pthread_mutex_init(&mutexm, NULL);
   messages = (char**) malloc(thread_count*sizeof(char*));

   for (thread = 0; thread < thread_count; thread++)
   {
       messages[thread] = NULL;
   }
      

   for (thread = 0; thread < thread_count; thread++)
   {
       pthread_create(&thread_handles[thread], (pthread_attr_t*) NULL, Send_msg, (void*) thread);
   }
      

   for (thread = 0; thread < thread_count; thread++) 
   {
      pthread_join(thread_handles[thread], NULL);
   }

   for (thread = 0; thread < thread_count; thread++)
      free(messages[thread]);
   free(messages);

   free(thread_handles);
   pthread_mutex_destroy(&mutex);
   pthread_mutex_destroy(&mutexm);
   return 0;
}  



void *Send_msg(void* rank)
{
    long my_rank = (long) rank;
    long dest = (my_rank + 1) % thread_count;
    
    char* my_msg = (char*) malloc(MSG_MAX*sizeof(char));

    pthread_mutex_lock(&mutex);
    sprintf(my_msg, "HOla a %ld de %ld", dest, my_rank);
    messages[dest] = my_msg;
    pthread_mutex_unlock(&mutex);

    
    if (messages[my_rank] != NULL) 
    {
        pthread_mutex_lock(&mutexm);
        printf("Thread %ld > %s\n", my_rank, messages[my_rank]);
        pthread_mutex_unlock(&mutexm);
    }
        
    else
    {
        pthread_mutex_lock(&mutexm);
        printf("Thread %ld > NO hay mesnajes de :c %d\n", my_rank, 10);
        pthread_mutex_unlock(&mutexm);
    }
        
    return NULL;
}
