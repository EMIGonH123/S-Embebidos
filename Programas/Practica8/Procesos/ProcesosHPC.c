#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#define NUMPROC 4
#define NUMDATOS 32

int *A,*B,*C;
int * reservarMemoria();
void llenarArreglo( int * datos );
void imprimirArreglo( int * datos );

void procesoHijo(int np, int tubo[]);
void procesoPadre(int  tubo[]);

int main(){
	pid_t pid;
	register int np;
	int tubo[2], estadoPipe;	
	A = reservarMemoria();
	llenarArreglo( A );
	imprimirArreglo( A );
	
	B = reservarMemoria();
	llenarArreglo( B );
	imprimirArreglo( B );

	C = reservarMemoria();
	
	estadoPipe = pipe(tubo);
	if(estadoPipe == -1){
		perror("Error al crear la tuberia...\n");
		exit(EXIT_FAILURE);
	}

	printf("\n\nProbando procesos...\n");
	for(np =0; np < NUMPROC; np++){
		pid = fork();
		if(pid == -1){
			perror("No se creo el proceso\n");
			exit(EXIT_FAILURE);
		}
		if(!pid){
			procesoHijo(np,tubo);
		}
	}
	procesoPadre(tubo);
	imprimirArreglo( C );
	free( A );
	free( B );
	free( C );
	return 0;
}

void procesoPadre(int tubo[]){
	int np, valor, inicioBloque;
	int tamBloque = NUMDATOS / NUMPROC;
	pid_t pidhijo;
	printf("Proceso padre ejecutado con pid %d\n", getpid());
	close( tubo[1] );	
	for (np = 0; np < NUMPROC; np++){
		pidhijo = wait(&valor);
		valor = valor >>8;		
		inicioBloque = valor * tamBloque;
		printf("Resultado del hijo %d y con pid %d\n",valor, pidhijo);
		read(tubo[0], C+inicioBloque, sizeof(int) * tamBloque);		
	}
	close(tubo[0]);
}

void procesoHijo(int np, int tubo[]){
	int tamBloque = NUMDATOS / NUMPROC;
	int inicioBloque = np * tamBloque;
	int finBloque = inicioBloque + tamBloque;
	int register i;

	printf("Proceso hijo %d ejecutado con pid %d\n",np, getpid());
	close(tubo[0]);
	for(i =  inicioBloque; i<finBloque; i++){
		C[i] = A[i] * B[i];
	}
	write(tubo[1], C + inicioBloque, sizeof(int)*tamBloque);
	close(tubo[1]);
	exit( np );
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
	//srand( getpid() );
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
