#MAKEFILE
PROYECTO=Muestreo
DESDIR=/usr/local/bin
CFLAGS=-Wall
LFLAGS=-lm
C=gcc

all: $(PROYECTO)

%.o: %.c
	$(C) -c $< $(CFLAGS)

#Muestreo.o: Muestreo.c
#	$(C) -c Muestreo.c $(CFLAGS)

#Archivos.o: Archivos.c
#	$(C) -c Archivos.c $(CFLAGS)

#Procesamiento.o: Procesamiento.c
#	$(C) -c Procesamiento.c $(CFLAGS)

$(PROYECTO): Main.o Archivos.o Procesamiento.o Procesos.o
	$(C) $^ -o $@ $(LFLAGS)

#$(PROYECTO): Muestreo.o Archivos.o Procesamiento.o
#	$(C) Muestreo.o Archivos.o Procesamiento.o -o $(PROYECTO) $(LFLAGS)

.PHONY: clean

install: all
	if [ ! -d $(DESDIR) ] ; then \
		sudo mkdir $(DESDIR) ;\
	fi; \
	sudo cp $(PROYECTO) $(DESDIR)

uninstall:
	sudo rm -f $(DESDIR)/$(PROYECTO)

clean:
	rm -f *.o *.dat $(PROYECTO)
