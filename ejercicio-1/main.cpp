#include <iostream>
#include "ejercicio_uno.h"
using namespace std;

int main(){
	int n;
	cin >> n;

	int** costos = new int*[n];
	for (int i = 0; i < n; i++)
	{
		costos[i] = new int[n];
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			cin >> costos[i][j];
		}
	}
	int c;
	c = impresionesOrdenadas(costos, n);
		
	cout << c;

	for (int i = 0; i < n; i++)
	{
		delete costos[i];
	}
	delete costos;

	return 0;
}