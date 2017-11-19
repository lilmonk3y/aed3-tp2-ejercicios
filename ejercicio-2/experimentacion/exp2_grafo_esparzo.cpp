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
	string file_name = "exp2_grafo_esparzo.txt";
	ofstream file_object;
	file_object.open(file_name);

	// escribo en el archivo todo el grafo.
	int cantidad_vertices = 500; // tiene que ser par
	int un_extremo;
	int otro_extremo;
	int peso_arista;
	for(int cantidad_parcial_vertices = 2; cantidad_parcial_vertices <=
	cantidad_vertices; cantidad_parcial_vertices=cantidad_parcial_vertices+2)
	{
		set<class arista> conjunto_aristas;

	  // Hago conexo al grafo.
		for(int indice = 1; indice < cantidad_parcial_vertices;
		indice = indice +1)
		{
	  	un_extremo = indice;
	  	otro_extremo = indice + 1;
	  	peso_arista = 1 + rand() % 1000;

	  	conjunto_aristas.insert(arista(otro_extremo,un_extremo,peso_arista));
		}

	  // Agrego un 10% de las aristas del denso
	  int aristas_extra =
		(cantidad_parcial_vertices*(cantidad_parcial_vertices-1))/(2*10);

	  for(int indice = 1; indice < aristas_extra; indice++)
		{
	  	un_extremo = 1 + rand() % cantidad_parcial_vertices;
	  	otro_extremo = 1 + rand() % cantidad_parcial_vertices;
	  	peso_arista = 1 + rand() % 1000;

	  	conjunto_aristas.insert(arista(otro_extremo,un_extremo,peso_arista));
		}

	  int cantidad_aristas = conjunto_aristas.size();
	  file_object << cantidad_parcial_vertices <<
	 	" " << cantidad_aristas <<endl;

	  // Escribo aristas resultantes.
		for( set<arista>::iterator iter_aristas = conjunto_aristas.begin();
		iter_aristas != conjunto_aristas.end(); ++iter_aristas )
		{
			file_object << (*iter_aristas).un_extremo << " "<< (*iter_aristas).otro_extremo
			<< " "<< (*iter_aristas).peso_arista << endl;
		}
	}
	file_object<< 0 << endl;
	file_object.close();
}
