#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#define NUMPROC 4

void procesoHijo(int np);
void procesoPadre();

int main(){
	pid_t pid;
	int np;
	printf("Probando procesos...\n");
	for(np =0; np < NUMPROC; np++){
		pid = fork();
		if(pid == -1){
			perror("No se creo el proceso\n");
			exit(EXIT_FAILURE);
		}
		if(!pid){
			procesoHijo(np);
		}
	}
	procesoPadre();
	return 0;
}

void procesoPadre(){
	int np,estado;
	pid_t pidhijo;
	printf("Proceso padre ejecutado con pid %d\n", getpid());
	for (np = 0; np < NUMPROC; np++){
		pidhijo = wait(&estado);
		printf("El proceso hijo %d termino con pid %d\n",estado>>8, pidhijo);		
	}
}

//Procesamiento paralelo con NP basado en el exit
void procesoHijo(int np){
	printf("Proceso hijo %d ejecutado con pid %d\n",np, getpid());
	while(1);
	exit(np);
}
