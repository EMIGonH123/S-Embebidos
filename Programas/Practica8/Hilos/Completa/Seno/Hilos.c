#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Defs.h"
#include "Informacion.h"

extern float *A,*B, *C;

void * productoIndices(void * args){
	//Argumentos *aux = (Argumentos *)args;
	//int nh = aux->numHilo;
	int * nh = (int *)args;	
	register int i = 0;
	for(i = *nh ; i< MUESTRAS; i+= NUMHILOS){
		//aux->funcion[i] = aux->seno[i] * aux->hamming[i];
		C[i] = A[i] * B[i];	
	}
	pthread_exit( args );
}
