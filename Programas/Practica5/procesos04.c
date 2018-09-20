#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#define NUMPROC 4
#define NUMDATOS 32

int * reservarMemoria();
void llenarArreglo( int * datos );
void imprimirArreglo( int * datos );
int mayorArreglo( int * datos );
int menorArreglo( int * datos );
double promedioDatos( int * datos );
void ordenarDatos( int * datos );


void procesoHijo(int np, int *datos);
void procesoPadre();

int main(){
	pid_t pid;
	int np;
	
	int *datos;
	datos = reservarMemoria();
	llenarArreglo( datos );
	imprimirArreglo( datos );
	printf("\n\nProbando procesos...\n");
	for(np =0; np < NUMPROC; np++){
		pid = fork();
		if(pid == -1){
			perror("No se creo el proceso\n");
			exit(EXIT_FAILURE);
		}
		if(!pid){
			procesoHijo(np,datos);
		}
	}
	procesoPadre();

	free( datos );
	return 0;
}

void procesoPadre(){
	int np,valor;
	pid_t pidhijo;
	printf("Proceso padre ejecutado con pid %d\n", getpid());
	for (np = 0; np < NUMPROC; np++){
		pidhijo = wait(&valor);
		printf("Resultado del hijo %d y con pid %d\n",valor>>8, pidhijo);		
	}
}

//Promedio y ordenamiento

//Procesamiento paralelo con NP basado en el exit
void procesoHijo(int np, int *datos){
	printf("Proceso hijo %d ejecutado con pid %d\n",np, getpid());
	if(np == 0){
		//printf("\nEl numero mayor es: %d \n",mayorArreglo(datos));
		exit(mayorArreglo( datos ));
	}else if(np ==1){
		//printf("\nEl numero menor es: %d \n",menorArreglo(datos));
		exit(menorArreglo( datos ));
	}else if(np == 2){

	}else{
		ordenarDatos( datos );
		imprimirArreglo( datos );
		exit( np );
	}
}

double promedioDatos( int * datos ){
	register int i, suma =0;
	
	for(i =0; i< NUMDATOS; i++){
		suma += datos[i];
	}
	return (suma/NUMDATOS.0);
}

void ordenarDatos( int * datos ){

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
