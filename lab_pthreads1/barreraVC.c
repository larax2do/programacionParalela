
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

const int MAX_THREADS = 1024;
const int MSG_MAX = 100;


char** messages;

int contador=0;
int thread_count;

sem_t count_sem;
sem_t barrier_sem;

void Usage(char* prog_name);
void *Send_msg(void* rank);
pthread_mutex_t barreraaa;
pthread_cond_t cond_var;


int main(int argc, char* argv[]) {
   long       thread;
   pthread_t* thread_handles; 

   if (argc != 2) Usage(argv[0]);
   thread_count = strtol(argv[1], NULL, 10);
   if (thread_count <= 0 || thread_count > MAX_THREADS) Usage(argv[0]);

   thread_handles = (pthread_t*) malloc (thread_count*sizeof(pthread_t));
   messages = (char**) malloc(thread_count*sizeof(char*));

    sem_init(&count_sem, 0, 1);
    sem_init(&barrier_sem, 0, 0);

   for (thread = 0; thread < thread_count; thread++)
      messages[thread] = NULL;

   for (thread = 0; thread < thread_count; thread++)
      pthread_create(&thread_handles[thread], (pthread_attr_t*) NULL,
          Send_msg, (void*) thread);

   for (thread = 0; thread < thread_count; thread++) {
      pthread_join(thread_handles[thread], NULL);
   }

   for (thread = 0; thread < thread_count; thread++)
      free(messages[thread]);
   free(messages);

   free(thread_handles);
   return 0;
} 


void *Send_msg(void* rank) {
   long my_rank = (long) rank;
   long dest = (my_rank + 1) % thread_count;
   long source = (my_rank + thread_count - 1) % thread_count;
   char* my_msg = (char*) malloc(MSG_MAX*sizeof(char));


   sem_wait(&count_sem);
   if(contador==thread_count-1)
   {
       contador=0;
       sem_post(&count_sem);
       for(int j=0;j<thread_count-1;j++)
       {
           sem_post(&barrier_sem);
       }
    }
    else
    {
        contador++;
        sem_post(&count_sem);
        sem_wait(&barrier_sem);
    }
    
    pthread_mutex_lock(&barreraaa);
    contador++;
    if(contador == thread_count)
    {
        contador = 0;
        pthread_cond_broadcast(&cond_var);
    }
    else
    {
        while(pthread_cond_wait(&cond_var, &barreraaa) != 0);
    }
    pthread_mutex_unlock(&barreraaa);
   
   


   sprintf(my_msg, "Hello to %ld from %ld", dest, my_rank);
   messages[dest] = my_msg;

   if (messages[my_rank] != NULL) 
      printf("Thread %ld > %s\n", my_rank, messages[my_rank]);
   else
      printf("Thread %ld > No message from %ld\n", my_rank, source);

   return NULL;
}  
void Usage(char* prog_name) {

   fprintf(stderr, "usage: %s <number of threads>\n", prog_name);
   exit(0);
}
