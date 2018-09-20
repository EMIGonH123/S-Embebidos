#Makefile para el programa de Procesos
#Variables de make
C = gcc
CFLAGS = -Wall
PROYECTO = Pipes

all: $(PROYECTO)

%.o : %.c
	$(C) -c $< $(CFLAGS)

$(PROYECTO): Main.o Datos.o Procesamiento.o Procesos.o Ordenamiento.o
	$(C) $^ -o $@

.PHONY: clean

clean: 
	sudo rm -f *.o $(PROYECTO)

