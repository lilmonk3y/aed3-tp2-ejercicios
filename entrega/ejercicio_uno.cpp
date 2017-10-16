#include "ejercicio_uno.h"

vector<int> impresionesOrdenadas(int** costos, const int n)
{
	//Se crea matriz de subproblemas con memoria dinamica ya que no se conoce el tamaño en la compilacion.
	int** subproblemas = new int*[n];
	for (int i = 0; i < n; i++)
	{
		subproblemas[i] = new int[n];
	}

	//Primero encontramos todas las subsoluciones optimas
	completarSubsoluciones(subproblemas, costos, n);


	//Despues reconstruimos la solucion total del problema.
	vector<int> trabajos = reconstruirSolucion(subproblemas, costos, n);

	for (int i = 0; i < n; i++)
	{
		delete[] subproblemas[i];
	}
	delete[] subproblemas;

	return trabajos;
}



void completarSubsoluciones(int** subproblemas, int** costos, const int n)
{
	//El primer subproblema es trivial.
	subproblemas[0][0] = costos[0][0];

	//El resto de los subproblemas:
	for (int i = 1; i < n; i++)
	{
		//Para cada fila i en la matriz de subproblemas: (subproblemas posibles con la maquina mas avanzada que hace el trabajo i)

		//n casos triviales. Mientras i != j, resolver el subproblema (i,j) es el costo del subproblema  (i-1, j) mas el costo de hacer el trabajo i luego del i-1.
		//Se resuelven en O(1).
		for (int j = 0; j < i; j++) {
			subproblemas[i][j] = subproblemas[i - 1][j] + costos[i][i];
		}

		//Un caso de n operaciones. Para la posicion (i, i) hay que elegir el subproblema optimo entre los que estan una linea mas arriba.
		//Se resuelve en O(n).
		int minimo = (subproblemas[i - 1][0] + costos[i][0]);
		for (int j = 1; j < i; j++)
		{
			int iterFila = subproblemas[i - 1][j] + costos[i][j];
			if (minimo > iterFila) minimo = iterFila;
		}
		subproblemas[i][i] = minimo;
	}
}


vector<int> reconstruirSolucion(int** subproblemas, int** costos, const int n)
{
	//Busca la solucion del problema total entre las posibles subsoluciones finales (las que tienen una de las maquinas que hizo el ultimo trabajo)
	int subpMin = 0;
	for (int i = 1; i < n; i++)
	{
		if (subproblemas[n - 1][subpMin] > subproblemas[n - 1][i]) subpMin = i;
	}

	//El vector trabajos es el que guarda toda la informacion de la salida que va a ser impresa por pantalla en orden inverso.
	vector<int> trabajos;
	//Otra guarda los trabajos de la maquina que no vamos a imprimir.
	vector<int> otra;

	//Guarda el costo de la solucion para ser agregado al final de trabajos (y que se imprima primero)
	int costoMin = subproblemas[n - 1][subpMin];

	trabajos.push_back(subpMin - 1);


	//Falta reconstruir la solucion optima en base a la matriz de subproblemas: (se recorre desde la ultima fila hasta la primera siguiendo el camino de esta solucion)
	int i = n - 1;
	while (i > 0)
	{
		//En cada iteracion hay un trabajo i o (subpMin - 1) que no fue asignado a ninguna maquina.
		//Primero buscamos cual es y se asigna
		if (subpMin - 1 == trabajos.back())
		{
			otra.push_back(i);
		}
		else if (i == trabajos.back())
		{
			otra.push_back(subpMin - 1);
		}
		else if (i == otra.back())
		{
			trabajos.push_back(subpMin - 1);
		}
		else {
			trabajos.push_back(i);
		}


		//Buscamos el subproblema del que proviene este.
		//Si no esta en la diagonal es trivial.
		if (i != subpMin) {
			i--;
		}
		//Si esta hay que buscar cual es el anterior.
		else
		{
			
			for (int j = 0; j < i; j++)
			{
				if (subproblemas[i][subpMin] == subproblemas[i - 1][j] + costos[i][j])
				{
					subpMin = j;
					i--;
					break;
				}
			}
		}

	}
	//Falta asignar el trabajo 0
	if (subpMin - 1 == trabajos.back())
	{
		otra.push_back(i);
	}
	else if (i == trabajos.back())
	{
		otra.push_back(subpMin - 1);
	}
	else if (i == otra.back()) 
	{
		trabajos.push_back(subpMin - 1);
	}
	else {
		trabajos.push_back(i);
	}

	if (trabajos.back() == -1) trabajos.pop_back();

	//Se agregan la cantidad de trabajos y el costo total.
	trabajos.push_back(trabajos.size());
	trabajos.push_back(costoMin);

	return trabajos;
}