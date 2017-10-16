#include <vector>
#include <iostream>
using namespace std;

//Funcion que devuelve la separacion de trabajos optima
//Costos es la matriz de costos, representada por puntero a puntero
//n es la cantidad de trabajos a realizar
//Toma puntero a puntero para poder usar una matriz de tamaño indefinido como parametro
vector<int> impresionesOrdenadas(int** costos, const int n);

//Funcion que completa todas las subsoluciones optimas en la primera matriz bottom-up
void completarSubsoluciones(int** subproblemas, int** costos, const int n);

//Toma una matriz de subsoluciones optimas y reconstruye la solucion del problema total 
vector<int> reconstruirSolucion(int** subproblemas, int** costos, const int n);