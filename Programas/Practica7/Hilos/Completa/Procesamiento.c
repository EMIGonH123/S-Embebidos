#include <stdio.h>
#include <stdlib.h>
#include "Macros.h"

int promedioDatos( int * datos ){
	register int i, suma =0;
	for(i =0; i< NUMDATOS; i++){
		suma += datos[i];
	}
	int resultado = suma/NUMDATOS;
	return resultado;
	
}

int mayorArreglo( int * datos ){
	register int i,mayor;
	mayor = datos[0];
	for(i =0; i<NUMDATOS; i++){
		if(mayor < datos[i]){
			mayor = datos[i];
		}
	}
	return mayor;
}


int menorArreglo( int * datos ){
	register int i,menor;
	menor = datos[0];
	for(i =0; i<NUMDATOS; i++){
		if(datos[i] < menor){
			menor = datos[i];
		}
	}
	return menor;
}
