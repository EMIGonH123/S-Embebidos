#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define TAM 10

void * suma(void * args);
void * resta(void * args);
void * multiplicacion(void * args);
void * division(void * args);
void * menor(void * args);
void * mayor(void * args);
int arreglo[10] = {1,2,3,4,5,6,7,8,9,10};
int num1 = 52, num2 = 10;

int main(){
	
	pthread_t hSuma,hResta, hMult, hDiv, hMayor, hMenor;
	int *rSuma, *rResta, *rMult, *rDiv, *rMenor,  *rMayor;	
	
	printf("PROBANDO HILOS...\n");
	pthread_create(&hSuma, NULL,suma, NULL);
	pthread_create(&hResta, NULL,resta, NULL );
	pthread_create(&hMult, NULL,multiplicacion, NULL );
	pthread_create(&hDiv, NULL, division, NULL );
	pthread_create(&hMayor, NULL, mayor, NULL );
	pthread_create(&hMenor, NULL, menor, NULL );
	
	pthread_join(hMayor,(void **)&rMayor);
	pthread_join(hMenor,(void **)&rMenor);
	pthread_join(hSuma,(void **)&rSuma);
	pthread_join(hResta,(void **)&rResta);
	pthread_join(hMult,(void **)&rMult);
	pthread_join(hDiv,(void **)&rDiv);
	
	printf("La suma es: %d\n", *rSuma );
	printf("La resta es: %d\n",  *rResta);
	printf("La multiplicacion es: %d\n", *rMult);
	printf("La division es: %d\n", *rDiv );
	printf("El mayor es: %d\n", *rMayor );
	printf("El menor es: %d\n", *rMenor );
	return 0;
}

void * suma(void * args){
	int *res = (int *)malloc(sizeof(int)); 
	*res = num1 + num2;
	pthread_exit((void *)res);
}

void * resta(void * args){
	int *res = (int *)malloc(sizeof(int));
	*res = num1 - num2;
	pthread_exit((void *)res);
}
void * multiplicacion(void * args){
	int *res = (int *)malloc(sizeof(int));	
	*res = num1 * num2;
	pthread_exit((void *)res);
}

void * division(void * args){
	int *res = (int *)malloc(sizeof(int));	
	*res = num1 / num2;
	pthread_exit((void *)res);
}

void * mayor(void * args){
	register int i ;
	int * cont  = (int *) malloc(sizeof(int));
	*cont = arreglo[0];	
	for(i =0; i< TAM; i++){
		if(arreglo[i] > *cont){
			*cont = arreglo[i];	
		}
	}
	pthread_exit((void *)cont);	
}

void * menor(void * args){
	register int i ;
	int * cont  = (int *) malloc(sizeof(int));
	*cont = arreglo[0];	
	for(i =0; i< TAM; i++){
		if(arreglo[i] < *cont){
			*cont = arreglo[i];	
		}
	}
	pthread_exit((void *)cont);
}



