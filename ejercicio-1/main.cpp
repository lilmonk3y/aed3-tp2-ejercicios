#include <iostream>
#include "ejercicio_uno.h"
using namespace std;

int main(){
	int n;
	while (cin >> n)
	{
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
		vector<int> out;
		out = impresionesOrdenadas(costos, n);

		while (!out.empty())
		{
			cout << out.back() << " ";
			out.pop_back();
		}
		cout << endl;
		for (int i = 0; i < n; i++)
		{
			delete costos[i];
		}
		delete costos;
	}
	return 0;
}