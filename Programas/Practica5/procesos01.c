#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

int main(){
	float num1= 23, num2 =12, suma, resta ;
	pid_t pid, pidhijo;
	int estado;
	printf("Probando procesos...\n");
	pid = fork();
	if(!pid){
		printf("Proceso hijo ejecutado con pid %d\n", getpid());
		suma = num1 + num2;
		printf("Suma: %f\n",suma);
		exit(0);
	}else{
		sleep(5);
		printf("Proceso padre ejecutado con pid %d\n", getpid());
		resta = num1 -num2;
		printf("Resta: %f\n", resta);
		pidhijo = wait(&estado);
		printf("El proceso hijo termino con pid %d\n", pidhijo);
	}
	return 0;
}
