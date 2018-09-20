#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#define NUMHILOS 4
#define N 64

int *A, *B, *C;

int* reservarMemoria();
void llenarArreglo(int * datos);
void imprimeArreglo(int * datos);
void producto( void );

int main(void){
	A = reservarMemoria();
	llenarArreglo(A);
	imprimeArreglo( A );
	B = reservarMemoria();
	llenarArreglo(B);
	imprimeArreglo( B );
	C = reservarMemoria();
   clock_t t_ini, t_fin;
   double secs;

	t_ini = clock();
	producto();
   t_fin = clock();

   secs = (double)(t_fin - t_ini) / CLOCKS_PER_SEC;
   printf("%.16g milisegundos\n", secs * 1000.0);

	imprimeArreglo( C );
	
	free(A);
	free(B);
	free(C);

	return 0;
}

int *reservarMemoria(){
	int * memoria = (int *)malloc(N* sizeof(int));	
	if(memoria != NULL)
		return memoria;
	return NULL;
}


void producto(void ){
	register int i;
	for(i=0; i<N; i++){
		C[i] = A[i] * B[i];
	}
}

void llenarArreglo(int* datos){
	register int i;
	srand(getpid());
	for(i=0; i<N; i++){
		datos[i] = rand() % 255;
	}
}

void imprimeArreglo(int * datos){
	register int i;
	printf("\n--------------------------\n");
	printf("-- Datos en el arreglo ---\n");
	printf("--------------------------\n");
	for (i = 0; i < N; i++){
		if( !(i%8) )
			printf("\n");
		printf("%5d ", datos[i]);
	}printf("\n");
}

