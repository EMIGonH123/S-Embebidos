#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include "Procesamiento.h"
#include "Macros.h"
#include "Ordenamiento.h"

void procesoPadre(){
	int np,valor;
	pid_t pidhijo;
	printf("------------------------------------------\n");	
	printf("-- Proceso padre ejecutado con pid %d --\n", getpid());
	printf("------------------------------------------\n");
	for (np = 0; np < NUMPROC; np++){
		pidhijo = wait(&valor);
		if((valor>>8) == 3)
			printf("Hijo %d con pid %d ordeno el arreglo anteriormente\n\n",valor>>8, pidhijo);
		printf("Resultado: %d del hijo con pid %d\n\n",valor>>8, pidhijo);		
		
	}
}

//Procesamiento paralelo con NP basado en el exit
void procesoHijo(int np, int *datos){
	printf("Proceso hijo %d con pid %d se ejecutó.\n",np, getpid());
	if(np == 0){
		exit(mayorArreglo( datos ));
	}else if(np ==1){
		exit(menorArreglo( datos ));
	}else if(np == 2){
		exit(promedioDatos( datos ));
	}else{
		quickSort(datos, 0, NUMDATOS-1); 
		printf("Arreglo ordenado:\n"); 
		printArray(datos, NUMDATOS);
		printf("\n"); 
		exit( np );
	}
}
