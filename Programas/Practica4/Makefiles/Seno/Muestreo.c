
#include <stdio.h>
#include "Defs.h"
#include "Archivos.h"
#include "Procesamiento.h"

/*Funcion principal*/
int main(){
	float seno[MUESTRAS];
	generaSeno(seno);
	guardaDato(seno);
	return 0;
}
