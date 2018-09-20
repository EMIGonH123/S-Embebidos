#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "Defs.h"
//#include "Archivos.h"

void guardaDato(float seno[]){
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
