CC=gcc
CFLAGS= -g -lm
Diccionario: main.o libreria.o
	$(CC) $(CFLAGS) -o Diccionario main.o

main.o: main.c libreria.h
	$(CC) $(CFLAGS) -c main.c

libreria.o: libreria.c libreria.h
	$(CC) $(CFLAGS) -c libreria.c

clean:
	rm -rf *.o
