#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#define N 4

void * funcion(void * args);
int contador = 0;
pthread_mutex_t aux;
int main(){
	register int nh;

	pthread_mutex_init(&aux, NULL);
	int datos[N], *resultado;
	pthread_t hilos[N];
	for(nh = 0; nh < N; nh++){
		datos[nh] = nh+1;
		pthread_create(&hilos[nh],NULL, funcion ,(void *)&datos[nh]);
	}
	for(nh = 0; nh < N; nh++){
		pthread_join(hilos[nh],(void **)&resultado);
		printf("Hilo %d terminado\n", *resultado);
	}
	pthread_mutex_destroy(&aux);
	return 0;
}

void * funcion(void * args){
	int n = *( int * )args;
	register int i = 0;

	pthread_mutex_lock(&aux);
	contador++;
	
	printf("Iniciando hilo %d con contador %d \n", n, contador);
	//while(-- i);	
	sleep( 5 );
	printf("Terminando hilo %d con contador %d \n", n, contador);
	pthread_mutex_unlock(&aux);
	pthread_exit( args );
}



