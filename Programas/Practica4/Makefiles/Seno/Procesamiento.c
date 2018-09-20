#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "Defs.h"
//#include "Procesamiento.h"

void generaSeno(float seno[]){
	float f =1000, fs=45000;
	register int n;
	for (n = 0; n < MUESTRAS; n++){
		seno[n] = sinf(2*n*M_PI*f/fs);
	}

}


