CFLAGS = -O
CC = g++ 

impresionesOrdenadas: main.o ejercicio_uno.o
	$(CC) $(CLAGS) -o impresionesOrdenadas main.o ejercicio_uno.o

ejercicio-1/main.o: main.cpp
	$(CC) $(CLAGS) -c main.cpp

ejercicio-1/impresionesOrdenadas: impresionesOrdenadas
	$(CC) $(CLAGS) -c ejercicio_uno.cpp

clean:
	rm -f core *.o 