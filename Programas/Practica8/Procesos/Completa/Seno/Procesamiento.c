#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "Defs.h"

void generaSeno(float seno[]){
	float f =1000, fs=45000;
	register int n;
	for (n = 0; n < MUESTRAS; n++){
		seno[n] = sinf(2*n*M_PI*f/fs);
	}
}

float * reservarMemoria(){
	float *memoria;
	memoria = (float *)malloc(sizeof(float)* MUESTRAS);
	if(!memoria){
		perror("Error al asignaer memoria\n");
		exit(EXIT_FAILURE);
	}
	return memoria;
}

void imprimirArreglo(float * datos){
	register int i;
	for (i = 0; i < MUESTRAS; i++){
		if( !(i%6) )
			printf("\n");
		printf("%5f ", datos[i]);
	}printf("\n\n");
}

void generaVentanaHamming(float *vhamm){
	register int i;	
	for(i =0; i<MUESTRAS; i++){
		float argumento = (2*PI*i)/(MUESTRAS-1);		
		vhamm[i] = 0.53836 - (0.46164*cos(argumento));
	}
}
