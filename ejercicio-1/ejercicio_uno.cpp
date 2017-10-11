#include "ejercicio_uno.h"

vector<int> impresionesOrdenadas(int** costos, const int n){

	int** subproblemas = new int*[n];
	for (int i = 0; i < n; i++)
	{
		subproblemas[i] = new int[n];
	}

	subproblemas[0][0] = costos[0][0];

	for (int i = 1; i < n; i++)
	{
		//n casos triviales
		//estos son los subproblemas que se resuelven en O(1). Es el costo del subproblema una linea mas arriba mas el costo de agregar el trabajo.
		for (int j = 0; j < i; j++){
			subproblemas[i][j] = subproblemas[i-1][j] + costos[i][i];
		}

		//un caso de n operaciones
		//busco el minimo de los subproblemas una linea mas arriba ya que este caso puede venir de cualquiera y necesito el optimo.
		int minimo = (subproblemas[i-1][0] + costos[i][0]);
		for (int j = 1; j < i; j++)
		{
			int iterFila = subproblemas[i - 1][j] + costos[i][j];
			if (minimo > iterFila) minimo = iterFila;
		}
		subproblemas[i][i] = minimo; 
	}


	int subpMin = 0;
	for (int i = 1; i < n; i++)
	{
		if (subproblemas[n - 1][subpMin] > subproblemas[n - 1][i]) subpMin = i;
	}

	int costoMin = subproblemas[n - 1][subpMin];
	vector<int> trabajos;

	int i = n - 1;
	while (i > 0)
	{
		if (subpMin == i) {
			trabajos.push_back(subpMin);
			for (int j = 0; j < i; j++)
			{
				if (subproblemas[i - 1][j] + costos[i][j] == subproblemas[i][subpMin])
				{
					subpMin = j;
				}
			}

		}
		else if (subpMin == 0)
		{
			break;
		}
		else
		{
			i = subpMin;
		}
	}

	for (int i = 0; i < n; i++)
	{
		delete subproblemas[i];
	}
	delete subproblemas;
	
	trabajos.push_back(trabajos.size());
	trabajos.push_back(costoMin);

	return trabajos;
}