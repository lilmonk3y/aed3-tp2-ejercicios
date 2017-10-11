#include <iostream>
#include "ejercicio_uno.h"
using namespace std;

int main(){
	int n;
	cin >> n;
	int costos [n][n];
	for(int i = 0; i < n; i++){
		for (int j = 0; j <= i; j++){
			cin >> costos[i][j];
		}
	}
	int c;
	c = impresionesOrdenadas((int**)&costos[0][0], n);
		
	cout << c;

	return 0;
}