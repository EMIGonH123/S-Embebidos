#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#define NUMHILOS 4
#define N 64

int *A,promedio = 0;
pthread_mutex_t bloqueo;
void * productoBloques(void * args);
void * productoIndices(void * args);
void imprimirArreglo(int * datos);
void llenarArreglo(int * datos);
int * reservarMemoria();

int main(){
	register int nh;
	int nhs[NUMHILOS], *resultado;
	pthread_t hilos[NUMHILOS];
	

	pthread_mutex_init( &bloqueo, NULL);	
	A = reservarMemoria();
	llenarArreglo(A);
	imprimirArreglo(A);

	for(nh = 0; nh < NUMHILOS; nh++){
		nhs[nh] = nh;
		pthread_create(&hilos[nh],NULL, productoIndices ,(void *)&nhs[nh]);
	}

	for(nh = 0; nh < NUMHILOS; nh++){
		pthread_join(hilos[nh],(void **)&resultado);
		printf("El hilo %d termino.\n", *resultado);
	}

	pthread_mutex_destroy( &bloqueo );
	printf("El promedio es: %0.2lf \n\n", (promedio/64.0));
		
	free(A);
	
	return 0;
}

/*void * productoBloques(void * args){
	int *nh = (int *)args;
	register int i;
	int tamBloque = (int)(N / NUMHILOS);
	int inicio = (*nh) * tamBloque;
	int fin = inicio + tamBloque;
	static int contador = 0;	
	for(i = inicio ; i< fin; i++){
		contador += A[i];
	}
	pthread_exit( &contador );
}*/


void * productoIndices(void * args){
	int *nh = ( int * )args;
	register int i = 0;
	int sumaparcial = 0;
	for(i = *nh ; i< N; i+= NUMHILOS){
		sumaparcial += A[i];
	}
	pthread_mutex_lock( &bloqueo);
	promedio += sumaparcial;	
	pthread_mutex_unlock( &bloqueo);
	pthread_exit( args );
}

void imprimirArreglo(int * datos){
	register int i;
	printf("\n--------------------------\n");
	printf("-- Datos en el arreglo ---\n");
	printf("--------------------------\n");
	for (i = 0; i < N; i++){
		if( !(i%8) )
			printf("\n");
		printf("%5d ", datos[i]);
	}printf("\n");
}

void llenarArreglo(int * datos){
	register int i;
	srand( getpid() );
	for (i = 0; i < N; i++){
		datos[i] = rand() % 255;
	}

}

int * reservarMemoria(){
	int *memoria;
	memoria = (int *)malloc(sizeof(int)* N);
	if(!memoria){
		perror("Error al asignaer memoria\n");
		exit(EXIT_FAILURE);
	}
	return memoria;
}
