#ifndef INFORMACION_H
#define INFORMACION_H
	typedef struct informacion{
		int *datos;
		pthread_mutex_t bloqueo;		
		int nh;
	}Informacion;
#endif
