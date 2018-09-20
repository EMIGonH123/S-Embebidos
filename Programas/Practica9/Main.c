#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define NUMDATOS 64
#define NUMHILOS 4
#define NUMPROC 4 

//Funciones
int * reservaMemoria();
void llenaArreglo( int *arreglo );
void imprimeArreglo( int *arreglo );
void * productoPorIndice( void * args );
void procesoHijo(int np, int tubo[][2]);
void procesoPadre(int tubo[][2]);

int *A,*B,*C, productoPunto = 0;
int tubo[NUMPROC][2];
 
int main(){
	//Declaracion de variables
	register int np,nh,nt;
	int resPipe;	
	pid_t pid;

	pthread_t hilos[NUMHILOS];
	int nhs[NUMHILOS], *resultadoHilo;
	

	//Llenamos los dos arreglos e imprimimos
	//sus valores
	A = reservaMemoria();
	if( A != NULL )
		llenaArreglo( A );
		imprimeArreglo( A );

	B = reservaMemoria();
	if( B != NULL )
		llenaArreglo( B );
		imprimeArreglo( B );

	C = reservaMemoria();

	for(nh = 0; nh< NUMHILOS; nh++){
		nhs[nh] = nh;			
		pthread_create(&hilos[nh], NULL, productoPorIndice,(void *)&nhs[nh]);
	}

	for(nh = 0; nh< NUMHILOS; nh++){
		pthread_join(hilos[nh], (void **)&resultadoHilo);
		printf("El hilo %d termino\n", *resultadoHilo);
	}

	imprimeArreglo( C );
	
	for(nt = 0; nt<NUMPROC; nt++){
		resPipe = pipe(&tubo[nt][2]);
		if( resPipe == -1){
			perror("ERROR");
			exit(EXIT_FAILURE);
		}
	}


	for(np = 0; np< NUMPROC; np++){
		pid = fork();
		if( pid == -1)
			perror("ERROR");
			exit(EXIT_FAILURE);
		procesoHijo(np, tubo);
	}procesoPadre(tubo);
	
	printf("El producto punto de los vectores es: %d", productoPunto);
	free( A );
	free( B );
	free( C );
	return 0;
}

void * productoPorIndice( void * args ){
	int * nh = (int *)args;	
	register int i;
	for(i = *nh; i<NUMDATOS; i+= NUMHILOS){
		C[i] = A[i] * B[i];
	}
	pthread_exit(args);
}

void procesoPadre(int tubo[][2]){
	register int i;
	pid_t pidHijo;
	int valorDevuelto;

	for( i=0; i< NUMPROC; i++){
		 pidHijo = wait(&valorDevuelto);
		valorDevuelto = valorDevuelto >>8;
		close(tubo[valorDevuelto][1]);
		printf("El proceso %d termino con valor: %d\n",pidHijo,valorDevuelto);
		int *aux;		
		read(tubo[valorDevuelto][0],aux,sizeof(int));		
		close(tubo[valorDevuelto][0]);
		productoPunto += *aux;	
	}
}

void procesoHijo(int np, int tubo[][2]){
	int tamBloque = NUMDATOS / NUMPROC;
	int inicioBloque = np * tamBloque;
	int finBloque = inicioBloque + tamBloque;
	register int i;
	int sumaParcial = 0;
	
	for(i = inicioBloque; i<finBloque; i++){
		sumaParcial += C[i];
	}//productoPunto += sumaParcial;
	close(tubo[np][0]);
	write(tubo[np][1], &sumaParcial, sizeof(int));
	close(tubo[np][1]);	
	exit(np);
}


int * reservaMemoria(){
	int  * memoria = (int *)malloc(sizeof(int)*NUMDATOS);
	if(memoria != NULL)
		return memoria;
	return NULL;
}

void llenaArreglo( int *arreglo ){
	register int i;
	srand(getpid());	
	for(i =0; i<NUMDATOS; i++){
		arreglo[i] = rand() % 255;	
	}
}

void imprimeArreglo( int *arreglo ){
	register int i;
	printf("\n-----------------------\n");
	printf("-- Datos del arreglo --\n");	
	printf("-----------------------\n");	
	for(i =0; i<NUMDATOS; i++){
		if(!(i%8))
			printf("\n");
		printf("%8d", arreglo[i]);	
	}printf("\n");
}
