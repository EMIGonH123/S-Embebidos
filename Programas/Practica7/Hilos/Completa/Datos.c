#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include "Macros.h"

void imprimirArreglo( int * datos ){
	register int i;
	printf("\n--------------------------\n");
	printf("-- Datos en el arreglo ---\n");
	printf("--------------------------\n");
	for (i = 0; i < NUMDATOS; i++){
		if( !(i%16) )
			printf("\n");
		printf("%3d ", datos[i]);
	}printf("\n");
}

void llenarArreglo( int * datos ){
	register int i;
	srand( getpid() );
	for (i = 0; i < NUMDATOS; i++){
		datos[i] = rand() % 255;
	}

}

int * reservarMemoria(){
	int *memoria;
	memoria = (int *)malloc(sizeof(int)* NUMDATOS);
	if(!memoria){
		perror("Error al asignaer memoria\n");
		exit(EXIT_FAILURE);
	}
	return memoria;
}
