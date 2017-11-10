#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <iostream> /* COUT, ENDL */
#include <climits> /* INT_MAX, INT_MIN */
#include <cassert> /* assert */
#include <utility> /* pair */

using namespace std;

int main()
{
	// declarar archivo e inicializar
	string file_name = "exp2_grafo_bipartito_2.txt";
	ofstream file_object;
	file_object.open(file_name);

	// escribo en el archivo todo el grafo.
	int cantidad_vertices = 500; // tiene que ser par
	int cantidad_aristas = (cantidad_vertices / 2) * ((cantidad_vertices / 2) -1);
	int un_extremo;
	int otro_extremo;
	int peso_arista;

	file_object << cantidad_vertices << " " << cantidad_aristas <<endl;

	for(int indice_primer_conjunto = 1; indice_primer_conjunto <= (cantidad_vertices / 2); indice_primer_conjunto++)
	{
		for(int indice_segundo_conjunto = (cantidad_vertices / 2) + 1; indice_segundo_conjunto <= cantidad_vertices; indice_segundo_conjunto++)
		{
			un_extremo = indice_primer_conjunto;
			otro_extremo = indice_segundo_conjunto;
			peso_arista = 1 + rand() % 1000;
			file_object << un_extremo << " "<< otro_extremo << " "<< peso_arista << endl;
		}
	}

	file_object<< 0 << endl;
	file_object.close();
}
