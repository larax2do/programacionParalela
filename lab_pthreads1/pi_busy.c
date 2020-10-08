#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "timer.h"


//variables globales
long thread_count;
long long n;
double suma;
int flag;

void* Thread_sum(void* rank);//la funcion para los threads


int main(int argc, char* argv[]) 
{
    long       thread;  
    pthread_t* thread_handles;
    double inicio,fin;//para el cronometro

    thread_count = strtol(argv[1], NULL, 10);
    thread_handles = (pthread_t*) malloc (thread_count*sizeof(pthread_t)); 

    n=100000000;
    suma = 0.0;


    GET_TIME(inicio);//INICIO DEL CRONOMETRO :3
    for (thread = 0; thread < thread_count; thread++)  
    {
        pthread_create(&thread_handles[thread], NULL, Thread_sum, (void*)thread);
    }
  
    for (thread = 0; thread < thread_count; thread++) 
    {
        pthread_join(thread_handles[thread], NULL); 
    }
    free(thread_handles);
    GET_TIME(fin);//FIN DEL CRONOMETRO :3

    suma = 4.0*suma;
    printf("COn un n de n = %lld terminos,\n", n);
    printf("EL valor de pi es %.15f\n", suma);
    fin=fin-inicio;
    printf("El tiempo que tarda es: %lf",fin);
    
    return 0;
}


void* Thread_sum(void* rank)
{
    long my_rank = (long) rank;
    double factor;
    long long i;
    long long my_n = n/thread_count;
    long long my_first_i = my_n*my_rank;
    long long my_last_i = my_first_i + my_n;
    double my_sum=0.0;

    if (my_first_i % 2 == 0)
    {
        factor = 1.0;
    }
    else
    {
        factor = -1.0;
    }
    for (i = my_first_i; i < my_last_i; i++, factor = -factor) 
    {
        my_sum += factor/(2*i+1);  
    }


    while (flag != my_rank);
    suma += my_sum;  
    flag = (flag+1) % thread_count;
    return NULL;
}  


