#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "Defs.h"
#include "Informacion.h"
#include "Archivos.h"
#include "Hilos.h"
#include "Procesamiento.h"

float *A,*B, *C;

int main(){
	register int nh;
	pthread_t hilos[NUMHILOS];
	int nhs[NUMHILOS], *resultado;
		
	A = reservarMemoria();
	B = reservarMemoria();
	C = reservarMemoria();
	generaSeno( A );
	imprimirArreglo( A);

	generaVentanaHamming( B );
	imprimirArreglo( B );
	
	/*Argumentos argumentos;

	argumentos.seno = reservarMemoria();
	generaSeno( argumentos.seno );
	imprimirArreglo(argumentos.seno);

	argumentos.hamming = reservarMemoria();	
	generaVentanaHamming( argumentos.hamming );
	imprimirArreglo(argumentos.hamming);

	argumentos.funcion = reservarMemoria();
*/
	for(nh = 0; nh < NUMHILOS; nh++){
		//argumentos.numHilo = nh;
		nhs[nh] = nh;
		pthread_create(&hilos[nh],NULL, productoIndices ,(void *)&nhs[nh]);
	}

	for(nh = 0; nh < NUMHILOS; nh++){
		pthread_join(hilos[nh],(void **)&resultado);
		printf("Hilo %d terminado\n", *resultado);
	}

	imprimirArreglo(C );

	guardaSeno( A );
	guardaHamming( B );
	guardaMult( C );	

	free( A );
	free( B );
	free( C );
	
	
	return 0;
}


