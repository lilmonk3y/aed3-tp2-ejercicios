#include "ejercicio_dos.h"

// FUNCIONA SOLO CON EL test02.txt
bool test02_crear_instancia_del_problema()
{
	bool respuesta = true;

	struct grafo_parametro grafo_input;
	grafo_input = crear_instancia_del_problema_sin_cantidad_servidores();

	struct grafo_parametro grafo_comparación;


		int nodo_uno, nodo_dos, peso_arista;
		nodo_uno = ;
		nodo_dos = ;
		peso_arista = ;

		lista_de_adyacencias.at(nodo_uno).push_back(nodo_dos);
		lista_de_pesos.at(nodo_uno).push_back(nodo_dos);
		lista_de_adyacencias.at(nodo_dos).push_back(nodo_uno);
		lista_de_pesos.at(nodo_dos).push_back(nodo_uno);





	nueva_instancia.lista_adyacencias = lista_de_adyacencias;
	nueva_instancia.lista_pesos = lista_de_pesos;

	return respuesta;
}

int main()
{
	assert( test_crear_instancia_del_problema() );

	cout << "Pasaron los tests" << endl;
	return 0;
}
