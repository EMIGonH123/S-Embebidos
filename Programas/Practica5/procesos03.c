#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <stdlib.h>
#define NUMDATOS 32

int * reservarMemoria();
void llenarArreglo( int * datos );
void imprimirArreglo( int * datos );
int mayorArreglo( int * datos );
int menorArreglo( int * datos );

int main(){
	int *datos;
	datos = reservarMemoria();
	llenarArreglo( datos );
	imprimirArreglo( datos );
	printf("\nEl numero mayor es: %d \nEl numero menor es: %d\n",mayorArreglo(datos) ,menorArreglo(datos) );
	free( datos );
	return 0;
}

int mayorArreglo( int * datos ){
	register int i,mayor;
	mayor = datos[0];
	for(i =0; i<NUMDATOS; i++){
		if(mayor < datos[i]){
			mayor = datos[i];
		}
	}
	return mayor;
}


int menorArreglo( int * datos ){
	register int i,menor;
	menor = datos[0];
	for(i =0; i<NUMDATOS; i++){
		if(datos[i] < menor){
			menor = datos[i];
		}
	}
	return menor;
}

void imprimirArreglo(int * datos){
	register int i;
	for (i = 0; i < NUMDATOS; i++){
		if( !(i%16) )
			printf("\n");
		printf("%3d ", datos[i]);
	}printf("\n");
}

void llenarArreglo(int * datos){
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
