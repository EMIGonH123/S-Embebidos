#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include "Procesos.h"
#include "Procesamiento.h"
#include "Datos.h"
#include "Macros.h"

int main(){
	pid_t pid;
	register int np;
	int *datos, resultado = 0 , tuberia[2];
	pipe( tuberia );
	datos = reservarMemoria();
	llenarArreglo( datos );
	imprimirArreglo( datos );
	printf("\n-------------------------\n");
	printf("--- Probando procesos ---\n");
	printf("-------------------------\n\n");
	for(np =0; np < NUMPROC; np++){
		pid = fork();
		if(pid == -1){
			perror("No se creo el proceso\n");
			exit(EXIT_FAILURE);
		}else	if(!pid){
			procesoHijo(np,datos, tuberia, resultado);
		}
	}
	procesoPadre( tuberia, resultado );

	free( datos );
	return 0;
}
