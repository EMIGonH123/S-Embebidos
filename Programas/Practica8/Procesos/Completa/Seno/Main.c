#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include "Defs.h"
#include "Archivos.h"
#include "Procesos.h"
#include "Procesamiento.h"



int main(){
	pid_t pid;
	register int np;
	int estadoPipe, tubo[NUMPROC][2];
	float *A, *B, *C;

	A = reservarMemoria();
	generaSeno( A );
	imprimirArreglo(A);

	B = reservarMemoria();	
	generaVentanaHamming( B );
	imprimirArreglo(B);

	C = reservarMemoria();

	for(np =0; np < NUMPROC; np++){
		estadoPipe = pipe( &tubo[np][0] );
		if(estadoPipe == -1){
			perror("Error al crear la tuberia...\n");
			exit(EXIT_FAILURE);
		}		
		pid = fork();
		if(pid == -1){
			perror("No se creo el proceso\n");
			exit(EXIT_FAILURE);
		}
		if(!pid){
			procesoHijo(np, /*&tubo[np][0]*/tubo,A,B,C);
		}
	}
	procesoPadre(tubo,A,B,C);
	imprimirArreglo(C);

	guardaSeno( A );
	guardaHamming( B );
	guardaMult( C );

	free( A );
	free( B );
	free( C );
	return 0;
}


