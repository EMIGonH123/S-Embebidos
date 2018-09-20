#Makefile para el programa de Procesos
#Variables de make
C = gcc
CFLAGS = -Wall
PROYECTO = HILOS
CFLAGSO = -lpthread

all: $(PROYECTO)

%.o : %.c
	$(C) -c $< $(CFLAGS)

$(PROYECTO): Main.o Datos.o Ordenamiento.o Procesamiento.o Hilos.o 
	$(C) $^ -o $@ $(CFLAGSO)

.PHONY: clean

clean: 
	sudo rm -f *.o $(PROYECTO)

