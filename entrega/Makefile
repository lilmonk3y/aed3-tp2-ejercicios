CFLAGS = -O
CC = g++ 

all: impresionesOrdenadas transportesPesados

impresionesOrdenadas: main.o ejercicio_uno.o
	$(CC) $(CLAGS) -o impresionesOrdenadas main.o ejercicio_uno.o

ejercicio-1/main.o: main.cpp
	$(CC) $(CLAGS) -c main.cpp

ejercicio-1/impresionesOrdenadas: impresionesOrdenadas
	$(CC) $(CLAGS) -c ejercicio_uno.cpp

transportesPesados: ejercicio_3.o
	$(CC) $(CLAGS) -o transportesPesados ejercicio_3.o

ejercicio-3/transportesPesados: ejercicio_3
	$(CC) $(CLAGS) -c ejercicio_3.cpp

clean:
	rm -f core *.o 
