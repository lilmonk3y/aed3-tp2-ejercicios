#include "../ejercicio_dos.h"

// FUNCIONA SOLO CON EL test02.txt
bool test02_crear_instancia_del_problema()
{
	bool respuesta = true;

	struct grafo_parametro grafo_input;
	grafo_input.crear_instancia_del_problema_sin_cantidad_servidores();


	respuesta = respuesta and grafo_input.existe_arista_entre_nodos(2,1,7);
	respuesta = respuesta and grafo_input.existe_arista_entre_nodos(1,2,7);

	respuesta = respuesta and grafo_input.existe_arista_entre_nodos(2,3,5);
	respuesta = respuesta and grafo_input.existe_arista_entre_nodos(3,2,5);

	respuesta = respuesta and grafo_input.existe_arista_entre_nodos(3,1,1);
	respuesta = respuesta and grafo_input.existe_arista_entre_nodos(1,3,1);

	respuesta = respuesta and grafo_input.existe_arista_entre_nodos(3,4,2);
	respuesta = respuesta and grafo_input.existe_arista_entre_nodos(4,3,2);

	respuesta = respuesta and grafo_input.existe_arista_entre_nodos(5,4,3);
	respuesta = respuesta and grafo_input.existe_arista_entre_nodos(4,5,3);

	respuesta = respuesta and grafo_input.existe_arista_entre_nodos(5,2,7);
	respuesta = respuesta and grafo_input.existe_arista_entre_nodos(2,5,7);

	respuesta = respuesta and grafo_input.existe_arista_entre_nodos(4,2,1);
	respuesta = respuesta and grafo_input.existe_arista_entre_nodos(2,4,1);

	return respuesta;
}

bool test03_crear_instancia_del_problema()
{
	bool respuesta = true;
	struct grafo_parametro grafo_input;
	grafo_input.crear_instancia_del_problema_sin_cantidad_servidores();

	respuesta = respuesta and grafo_input.existe_arista_entre_nodos(2,1,1);
	respuesta = respuesta and grafo_input.existe_arista_entre_nodos(1,2,1);

	respuesta = respuesta and grafo_input.existe_arista_entre_nodos(2,3,3);
	respuesta = respuesta and grafo_input.existe_arista_entre_nodos(3,2,3);

	respuesta = respuesta and grafo_input.existe_arista_entre_nodos(4,1,4);
	respuesta = respuesta and grafo_input.existe_arista_entre_nodos(1,4,4);

	respuesta = respuesta and grafo_input.existe_arista_entre_nodos(1,8,5);
	respuesta = respuesta and grafo_input.existe_arista_entre_nodos(8,1,5);

	respuesta = respuesta and grafo_input.existe_arista_entre_nodos(8,4,4);
	respuesta = respuesta and grafo_input.existe_arista_entre_nodos(4,8,4);

	respuesta = respuesta and grafo_input.existe_arista_entre_nodos(8,7,1);
	respuesta = respuesta and grafo_input.existe_arista_entre_nodos(7,8,1);

	respuesta = respuesta and grafo_input.existe_arista_entre_nodos(7,6,2);
	respuesta = respuesta and grafo_input.existe_arista_entre_nodos(6,7,2);

	respuesta = respuesta and grafo_input.existe_arista_entre_nodos(6,5,7);
	respuesta = respuesta and grafo_input.existe_arista_entre_nodos(5,6,7);

	respuesta = respuesta and grafo_input.existe_arista_entre_nodos(4,5,6);
	respuesta = respuesta and grafo_input.existe_arista_entre_nodos(5,4,6);

	respuesta = respuesta and grafo_input.existe_arista_entre_nodos(4,6,10);
	respuesta = respuesta and grafo_input.existe_arista_entre_nodos(6,4,10);

	respuesta = respuesta and grafo_input.existe_arista_entre_nodos(1,6,11);
	respuesta = respuesta and grafo_input.existe_arista_entre_nodos(6,1,11);

	respuesta = respuesta and grafo_input.existe_arista_entre_nodos(6,8,3);
	respuesta = respuesta and grafo_input.existe_arista_entre_nodos(8,6,3);

	return respuesta;
}


int main()
{
	//assert( test02_crear_instancia_del_problema() );
	assert( test03_crear_instancia_del_problema() );


	cout << "Pasaron los tests" << endl;
	return 0;
}
