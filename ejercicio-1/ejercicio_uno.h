#include <vector>
using namespace std;

//funcion que devuelve la separacion de trabajos optima
//costos es la matriz de costos, representada por puntero a puntero
//n es la cantidad de trabajos a realizar
//toma puntero a puntero para poder usar una matriz de tamaño indefinido como parametro
int impresionesOrdenadas(int** costos, const int n);