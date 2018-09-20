#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "Informacion.h"
#include "Procesamiento.h"
#include "Ordenamiento.h"
#include "Macros.h"

extern pthread_mutex_t bloqueo;
extern int *datos;

void * funcionHilo(void * args){
	//Informacion * informacion = (Informacion *)args;
	//printf("Num hilo: %d\n", informacion->nh);
	int *nh = (int *) args;	
	int * resultado= (int *)malloc(sizeof(int));
	
	
	switch(*nh){
		case 0:
			//pthread_mutex_lock(&bloqueo);
			pthread_mutex_lock(&bloqueo);			
			*resultado = mayorArreglo(/*informacion->datos*/datos);
			printf("Mayor: %d\n", *resultado);
			//pthread_mutex_unlock(&informacion->bloqueo);
			pthread_mutex_unlock(&bloqueo);		
			break;
		case 1:	
			//pthread_mutex_lock(&informacion->bloqueo);
			pthread_mutex_lock(&bloqueo);
			*resultado = menorArreglo(/*informacion->datos*/datos);
			printf("Menor: %d\n", *resultado);
			//pthread_mutex_unlock(&informacion->bloqueo);
			pthread_mutex_unlock(&bloqueo);
			break;
		case 2:	
			//pthread_mutex_lock(&informacion->bloqueo);
			pthread_mutex_lock(&bloqueo);			
			*resultado = promedioDatos(/*informacion->datos*/datos); 			
			printf("Promedio: %d\n", *resultado);
//			pthread_mutex_unlock(&informacion->bloqueo);
			pthread_mutex_unlock(&bloqueo);
			break;		
		case 3:
			//pthread_mutex_lock(&informacion->bloqueo);
			printf("Ordenamiento\n");
			/*quickSort(informacion->datos, 0, NUMDATOS -1);
			printf("Arreglo ordenado...\n");
			printArray(informacion->datos, NUMDATOS -1);
			printf("\n");
			*/
			pthread_mutex_lock(&bloqueo);			
			*resultado = *nh;
			quickSort(datos, 0, NUMDATOS -1);
			printf("Arreglo ordenado...\n");
			printArray(datos, NUMDATOS -1);
			printf("\n");
			//pthread_mutex_unlock(&informacion->bloqueo);
			pthread_mutex_unlock(&bloqueo);			
			break;
	}
	
	pthread_exit((void *)resultado);
}
