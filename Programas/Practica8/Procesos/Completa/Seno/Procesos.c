#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "Defs.h"
#include <stdlib.h>
#include <stdio.h>

void procesoPadre(int tubo[][2], float *A, float *B, float *C){
	register int np;
	int valor, inicioBloque, tamBloque = MUESTRAS / NUMPROC;
	pid_t pidhijo;

	printf("Proceso padre ejecutado con pid %d\n", getpid());
		
	for (np = 0; np < NUMPROC; np++){
				
		pidhijo = wait(&valor);
		valor = valor >> 8; //Ojo con esto, asi esta super pro
		close( tubo[valor][1] );		
		inicioBloque = valor * tamBloque;
		printf("Resultado del hijo %d y con pid %d\n",valor, pidhijo);
		read(tubo[valor][0], C+inicioBloque, sizeof(int) * tamBloque);
		close( tubo[valor][0] );		
	}
}

void procesoHijo(int np, int tubo[][2], float *A, float *B, float *C){
	int tamBloque = MUESTRAS / NUMPROC;
	int inicioBloque = np * tamBloque;
	int finBloque = inicioBloque + tamBloque;
	int register i;

	printf("Proceso hijo %d ejecutado con pid %d\n",np, getpid());
	close(tubo[np][0]);
	for(i =  inicioBloque; i<finBloque; i++){
		C[i] = A[i] * B[i];
	}
	write(tubo[np][1], C + inicioBloque, sizeof(int)*tamBloque);
	close(tubo[np][1]);
	exit( np );
}
