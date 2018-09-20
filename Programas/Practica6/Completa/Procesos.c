#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include "Procesamiento.h"
#include "Ordenamiento.h"
#include "Macros.h"

void procesoPadre( int tuberia[2], int resultado ){
	int valor,dato;
	
	register int np;	
	pid_t pidhijo;
	//int *datos = (int *)malloc(NUMDATOS * sizeof(int));
	printf("Proceso padre ejecutado con pid %d\n", getpid());
	for (np = 0; np < NUMPROC; np++){
		close( tuberia[1] );		
		pidhijo = wait(&valor);
		if((valor>>8) == 3){
			for(int i = 0; i< NUMDATOS; i++){
				read( tuberia[0], &dato, sizeof(int));				
				printf("%d ",dato);
			}printf("\n");
			//printArray(datos, NUMDATOS);				
		}else{		
			read( tuberia[0], &resultado, sizeof(int) );
			printf("Proceso hijo con pid %d termino con resultado %d.\n", pidhijo, resultado);
		}
	}close( tuberia[0] );
}

//Procesamiento paralelo con NP basado en el exit
void procesoHijo( int np, int *datos, int tuberia[2], int resultado ){
	printf("Proceso hijo %d ejecutado con pid %d\n",np, getpid());
	close( tuberia[0] );
	if(np == 0){
		resultado = mayorArreglo( datos );
		printf("El proceso %d con pid %d encontro el mayor: %d\n",np, getpid(), resultado);		
		write(tuberia[1], &resultado,sizeof(int));
				
		exit(np);
	}else if(np ==1){
		resultado = menorArreglo( datos );
		printf("El proceso %d con pid %d encontro el menor: %d\n",np, getpid(), resultado);
		write(tuberia[1], &resultado,sizeof(int));
		exit(np);
	}else if(np == 2){
		resultado = promedioDatos( datos );
		printf("El proceso %d con pid %d encontro el promedio: %d\n",np, getpid(), resultado);
		write(tuberia[1], &resultado,sizeof(int));
		exit(np);
	}else{
		quickSort(datos, 0, NUMDATOS-1);
		printf("El proceso %d con pid %d ordeno el arreglo\n",np, getpid());
		for(int i = 0; i < NUMDATOS; i++){
				write( tuberia[1], &datos[i], sizeof(int));					
		}
		exit( np );
	}close(tuberia[1]);
	
}
