#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <iostream> /* COUT, ENDL */
#include <climits> /* INT_MAX, INT_MIN */
#include <cassert> /* assert */
#include <utility> /* pair */
#include <set> /* set */
#include <tuple>

using namespace std;

class arista{
public:
	int un_extremo;
	int otro_extremo;
	int peso_arista;
	arista(int numero, int otro, int otro_mas)
	{
		un_extremo = numero;
		otro_extremo = otro;
		peso_arista = otro_mas;
	}
	bool operator < (arista const & obj) const
	{
		return (un_extremo > obj.otro_extremo) ;
	}

};

int main()
{
	// declarar archivo e inicializar
	string file_name = "exp2_grafo_denso.txt";
	ofstream file_object;
	file_object.open(file_name);

	// escribo en el archivo todo el grafo.
	int cantidad_vertices = 500; // tiene que ser par
	int un_extremo;
	int otro_extremo;
	int peso_arista;
	for(int indice = 2; indice <= cantidad_vertices; indice = indice+2)
	{
		int cantidad_aristas = (indice*(indice-1)) / 2;
		set<class arista> conjunto_aristas;
		file_object << indice << " " << cantidad_aristas <<endl;

		for(int indice_primer_conjunto = 1; indice_primer_conjunto
		<= indice; indice_primer_conjunto++)
		{
			for(int indice_segundo_conjunto = 1; indice_segundo_conjunto
			<= indice; indice_segundo_conjunto++)
			{
				if( indice_primer_conjunto == indice_segundo_conjunto) continue;

				un_extremo = indice_primer_conjunto;
				otro_extremo = indice_segundo_conjunto;
				peso_arista = 1 + rand() % 1000;

				conjunto_aristas.insert(arista(un_extremo,otro_extremo,peso_arista));
			}
		}

		for( set<arista>::iterator iter_aristas = conjunto_aristas.begin();
		iter_aristas != conjunto_aristas.end(); ++iter_aristas )
		{
			file_object << (*iter_aristas).un_extremo << " "
			<< (*iter_aristas).otro_extremo
			<< " "<< (*iter_aristas).peso_arista << endl;
		}
	}
	file_object<< 0 << endl;
	file_object.close();
}
