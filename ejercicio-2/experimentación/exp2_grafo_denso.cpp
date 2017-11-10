#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <iostream> /* COUT, ENDL */
#include <climits> /* INT_MAX, INT_MIN */
#include <cassert> /* assert */
#include <utility> /* pair */
#include <set> /* set */
#include <unordered_set>

using namespace std;

struct arista{
	int un_extremo;
	int otro_extremo;
	int peso_arista;
	bool operator == ( arista& obj)
	{
    if( un_extremo != obj.un_extremo || otro_extremo != obj.otro_extremo ){
        return false;
    }
		return true;
  }
};

int main()
{
	// declarar archivo e inicializar
	string file_name = "exp2_grafo_denso.txt";
	ofstream file_object;
	file_object.open(file_name);

	// escribo en el archivo todo el grafo.
	int cantidad_vertices = 20; // tiene que ser par
	int cantidad_aristas = (cantidad_vertices * (cantidad_vertices-1)) / 2;
	int un_extremo;
	int otro_extremo;
	int peso_arista;
	unordered_set<struct arista> conjunto_aristas;
	struct arista una_arista;

	file_object << cantidad_vertices << " " << cantidad_aristas <<endl;

	for(int indice_primer_conjunto = 1; indice_primer_conjunto <= cantidad_vertices; indice_primer_conjunto++)
	{
		for(int indice_segundo_conjunto = 1; indice_segundo_conjunto <= cantidad_vertices; indice_segundo_conjunto++)
		{
			if( indice_primer_conjunto == indice_segundo_conjunto) continue;

			un_extremo = indice_primer_conjunto;
			otro_extremo = indice_segundo_conjunto;
			peso_arista = 1 + rand() % 1000;

			una_arista.un_extremo = un_extremo;
			una_arista.otro_extremo = otro_extremo;
			una_arista.peso_arista = peso_arista;

			conjunto_aristas.insert(una_arista);
		}
	}

	unordered_set<arista>::iterator iter_aristas;
	iter_aristas = conjunto_aristas.begin();
	while( iter_aristas != conjunto_aristas.end() )
	{
		file_object << (*iter_aristas).un_extremo << " "<< (*iter_aristas).otro_extremo << " "<< (*iter_aristas).peso_arista << endl;
	}

	file_object<< 0 << endl;
	file_object.close();
}
