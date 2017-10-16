#include "ejercicio_dos.h"

// FUNCIONA SOLO CON EL test02.txt
bool test02_crear_instancia_del_problema()
{
	bool respuesta = true;

	struct grafo_parametro grafo_input;
	grafo_input = crear_instancia_del_problema_sin_cantidad_servidores();

	

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
