#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "Macros.h"
#include "Datos.h"
#include "Hilos.h"
#include "Informacion.h"

	int *datos;
	pthread_mutex_t bloqueo;		
	int nhs[NUMHILOS];

int main(){

	register int nh;
	pthread_t hilos[NUMHILOS];
	int *resultado;

	/*/Informacion informacion;
	pthread_mutex_init(&informacion.bloqueo,NULL);
	informacion.datos = reservarMemoria();
	llenarArreglo( informacion.datos );
	imprimirArreglo( informacion.datos );	
*/



	pthread_mutex_init(&bloqueo,NULL);
	datos = reservarMemoria();
	llenarArreglo(datos);
	imprimirArreglo(datos);
	for(nh = 0; nh < NUMHILOS; nh++){
		nhs[nh] = nh;
		//informacion.nh = nh;
		//printf("Num Hilo MAIN: %d\n",informacion.nh);
		pthread_create(&hilos[nh],NULL, funcionHilo ,(void *)/*&informacion*/&nhs[nh]);
	}

	for(nh = 0; nh < NUMHILOS; nh++){
		pthread_join(hilos[nh],(void **)&resultado);
		printf("Resultado del hilo hijo: %d\n", *resultado);
	}
	pthread_mutex_destroy(&bloqueo);
	//pthread_mutex_destroy(&informacion.bloqueo);

	return 0;
}


