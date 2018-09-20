#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define MUESTRAS 256

/*****************************/
/* Cabecera de las funciones */
/*****************************/
void generaSeno(float seno[]);
void guardaDato(float seno[]);


/*Funcion principal*/
int main(){
	float seno[MUESTRAS];
	generaSeno(seno);
	guardaDato(seno);
	return 0;
}

void generaSeno(float seno[]){
	float f =1000, fs=45000;
	register int n;
	for (n = 0; n < MUESTRAS; n++){
		seno[n] = sinf(2*n*M_PI*f/fs);
	}

}

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
