#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "Defs.h"

void guardaSeno(float seno[]){
	FILE * ap;
	register int n;
	ap = fopen("Seno.dat","w");
	if(!ap){
		perror("Error al abrir el archivo");
		exit(EXIT_FAILURE);
	}
	for (n = 0; n < MUESTRAS; n++){
		fprintf(ap, "%f\n",seno[n] );
	}
	fclose(ap);
}

void guardaHamming(float seno[]){
	FILE * ap;
	register int n;
	ap = fopen("Hamming.dat","w");
	if(!ap){
		perror("Error al abrir el archivo");
		exit(EXIT_FAILURE);
	}
	for (n = 0; n < MUESTRAS; n++){
		fprintf(ap, "%f\n",seno[n] );
	}
	fclose(ap);
}

void guardaMult(float seno[]){
	FILE * ap;
	register int n;
	ap = fopen("Multiplicacion.dat","w");
	if(!ap){
		perror("Error al abrir el archivo");
		exit(EXIT_FAILURE);
	}
	for (n = 0; n < MUESTRAS; n++){
		fprintf(ap, "%f\n",seno[n] );
	}
	fclose(ap);
}
