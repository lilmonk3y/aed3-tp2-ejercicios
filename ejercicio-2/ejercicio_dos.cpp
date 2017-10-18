#include "ejercicio_dos.h"
#define INFINITO INT_MAX
#define VISITADO 1
#define NO_VISITADO 0
#define DEBO_IMPLEMENTAR false


/* YA ESTOY EN CONDICIONES DE TESTEAR LA FUNCION crear_agm. TENGO QUE CREAR
GRAFOS PARA VERIFICAR LOS RESULTADOS QUE ME DÉ LA FUNCION */



/*                  main y parsers                */

void func_main()
{
	int cantidad_servidores;
	while( hay_entrada(cantidad_servidores) )
	{
		// init
		class grafo_lista_adyacencias  grafo_input;
		grafo_input.crear_instancia_del_problema(cantidad_servidores);
		// sub-problema-uno
		class grafo_generador_minimo grafo_output;
		grafo_output.crear_agm(grafo_input);
		int peso_grafo_output = grafo_output.peso_agm;
		cout<<endl; cout<< "El peso del grafo generado es: "<< grafo_output.peso_agm <<endl; cout<<endl;
		// sub-problema-dos
		int nodo_master = grafo_output.elegir_master();
		cout<<endl; cout<< "El master del grafo generado es: "<< nodo_master <<endl; cout<<endl;

		// // output
		// grafo_output.imprimir_solucion(peso_grafo_output, nodo_master);
	}
	return;
}



int grafo_generador_minimo::elegir_master()
{
	//Elijo un nodo cualquiera, pero para simplificar empiezo por el 1 y lo llamo "s"
  int nodo_s = 1;
  int nodo_v = nodo_mas_lejano_a(nodo_s);
  int nodo_w = nodo_mas_lejano_a(nodo_v);
  return elegir_nodo_intermedio_entre(nodo_v, nodo_w);
}

int grafo_generador_minimo::nodo_mas_lejano_a(int nodo_origen)
{
  vector<int> distancias = distancias_de_un_nodo_a_todos_los_demas(nodo_origen);
  return indice_del_maximo_de(distancias);
}

vector<int> grafo_generador_minimo::distancias_de_un_nodo_a_todos_los_demas(int nodo_origen)
{
	/*Elijo un enfoque BFS para encontrar el nodo más lejano a nodo_origen */
  vector<NODO> elementos_visitados;
  inicializar_vector_con( NO_VISITADO, elementos_visitados , lista_adyacencias.size() );
  vector<int> distancias;
  inicializar_vector_con( INFINITO, distancias, lista_adyacencias.size() );
  queue<int> cola;

  cola.push(nodo_origen);
  elementos_visitados.at(nodo_origen) = VISITADO;
  distancias.at(nodo_origen) = 0;
  while( not cola.empty() ){
    int un_nodo = cola.front();
    cola.pop();

		auto it = lista_adyacencias.at(un_nodo).cbegin();
		auto it_final = lista_adyacencias.at(un_nodo).cend();
		int adyacente_a_un_nodo;
		for(it; it != it_final; ++it )
		{
			adyacente_a_un_nodo = (*it).first;
      if( elementos_visitados.at(adyacente_a_un_nodo) == NO_VISITADO )
      {
        elementos_visitados.at(adyacente_a_un_nodo) = VISITADO;
        distancias.at(adyacente_a_un_nodo) = distancias.at(un_nodo) + 1;
        cola.push(adyacente_a_un_nodo);
      }
    } /* ya mire todos los adyacentes a un_nodo */
  } /* ya mire todos los nodos del arbol */
  return distancias;
}

NODO grafo_generador_minimo::elegir_nodo_intermedio_entre(int nodo_origen, int nodo_destino)
{
	/* IDEA: reconstruyo el camino entre nodo_origen y nodo_destino y el nodo que
	esté en el medio es el nodo que debo entregar. */

	/* init */
  vector<NODO> camino;

  vector<NODO> visitados;
	visitados.resize(lista_adyacencias.size());
  inicializar_vector_con(NO_VISITADO ,visitados, lista_adyacencias.size());

  class camino_entre_dos_nodos diagonal_agm;
  diagonal_agm.nodo_origen = nodo_origen;
  diagonal_agm.nodo_destino = nodo_destino;
  diagonal_agm.lista_adyacencias = lista_adyacencias;
  diagonal_agm.camino = camino;
  diagonal_agm.visitados = visitados;

	/* construyo la diagonal desde una punta a la otra con este algoritmo recursivo */
  diagonal_agm.construir_diagonal(nodo_origen);
  int nodo_master = diagonal_agm.camino.at( ((int) diagonal_agm.camino.size() / 2) );
  return nodo_master;
}

bool camino_entre_dos_nodos::construir_diagonal(int nodo_actual)
{
	if(visitados.at(nodo_actual) == VISITADO) return false;

	visitados.at(nodo_actual) = VISITADO;
  bool respuesta = false;
	/* si soy el nodo que estoy buscando entonces devuelvo true y me agrego al camino */
  if(nodo_actual == nodo_destino)
  {
    respuesta = true;
  }else{
		/* llamo recursivamente por todos los nodos adyacentes a nodo_actual */
		auto it = lista_adyacencias.at(nodo_actual).cbegin();
		auto it_final = lista_adyacencias.at(nodo_actual).cend();
		for(it; it != it_final; ++it )
		{
			int adyacente = (*it).first;
      respuesta = construir_diagonal(adyacente);
      if(respuesta) break;
    }
  }
	if(respuesta) camino.push_back(nodo_actual);
  return respuesta;
}



void grafo_generador_minimo::imprimir_solucion(int peso_grafo, int nodo_master)
{
	assert( DEBO_IMPLEMENTAR );

	return;
}




















































/*------------------------------------ Revisadas  ----------------------------*/

int indice_del_minimo_de(vector<NODO> &distancias)
{
  int indice_minimo = 1;
  for(int indice = 2; indice < distancias.size(); indice++ )
    if( distancias.at(indice_minimo) >  distancias.at(indice) ) indice_minimo = indice;

  return indice_minimo;
}

int indice_del_maximo_de(vector<NODO> &distancias)
{
  int indice_maximo = 1;
  for(int indice = 2; indice < distancias.size(); indice++ )
    if( distancias.at(indice_maximo) < distancias.at(indice) ) indice_maximo = indice;

  return indice_maximo;
}

void grafo_generador_minimo::crear_agm(grafo_lista_adyacencias grafo_input)
{
	/* El AGM lo hago con el enfoque de PRIM */

	// init grafo_generador_minimo
	peso_agm = 0;
	lista_adyacencias.resize( grafo_input.lista_adyacencias.size() );
  inicializar_vector_con(NO_VISITADO, visitados, grafo_input.lista_adyacencias.size());

  /* Empiezo con el nodo 1 */
  int nodo_actual = 1;
  int cantidad_nodos_visitados = 0;
	struct arista una_arista;
  while( cantidad_nodos_visitados < (grafo_input.lista_adyacencias.size() - 2 ) )
  {
    if( not visite_a(nodo_actual) )
    {
      visitados.at(nodo_actual) = VISITADO;
      cantidad_nodos_visitados++;
      agregar_aristas_adyacentes_a(nodo_actual, grafo_input);
    }
    una_arista = minima_arista_que_no_forma_ciclos();
    agregar_arista_al_agm(una_arista);
    nodo_actual = nodo_que_no_visite(una_arista);
  }
  return;
}

int grafo_generador_minimo::nodo_que_no_visite(struct arista una_arista)
{
  int respuesta;
  if( visite_a(una_arista.un_nodo) )
  {
    respuesta = una_arista.otro_nodo;
    assert( not visite_a(una_arista.otro_nodo) );
  }else{
    respuesta = una_arista.un_nodo;
  }
  return respuesta;
}

void grafo_generador_minimo::agregar_arista_al_agm(struct arista una_arista)
{
	// cout << endl; cout << "estoy en agregar_arista_al_agm" << endl; cout << endl;
	// cout<<endl; cout<< "el numero de nodo que quiero agregar es: "<< una_arista.un_nodo << endl; cout << endl;


	pair<NODO,PESO> unNodo(una_arista.otro_nodo, una_arista.peso);
	pair<NODO,PESO> otroNodo(una_arista.un_nodo, una_arista.peso);
	lista_adyacencias.at(una_arista.un_nodo).push_back(unNodo);
  lista_adyacencias.at(una_arista.otro_nodo).push_back(otroNodo);

	peso_agm = peso_agm + una_arista.peso;

	aristas_agm_imprimir.push_back(una_arista);

  return;
}

/* Devuelvo una arista en la que uno de sus dos extremos no fue visitado */
struct arista grafo_generador_minimo::minima_arista_que_no_forma_ciclos()
{
  struct arista una_arista;

	/* saco aristas hasta que me de una arista que no forma ciclos  o ya no alla
	más aristas para elegir */
  while( aristas_a_elegir.size() != 0 )
  {
    una_arista = aristas_a_elegir.top();
    aristas_a_elegir.pop();

    if( not visite_a(una_arista) ) break;
  }
  return una_arista;
}

bool grafo_generador_minimo::visite_a(struct arista una_arista)
{
  return ( (visitados.at(una_arista.otro_nodo) == VISITADO)
	and  (visitados.at(una_arista.un_nodo) == VISITADO) );
}

void grafo_generador_minimo::agregar_aristas_adyacentes_a(int nodo_actual,
	class grafo_lista_adyacencias  &grafo_input)
{

	auto it = grafo_input.lista_adyacencias.at(nodo_actual).cbegin();
	auto it_final = grafo_input.lista_adyacencias.at(nodo_actual).cend();
	for(it; it != it_final; ++it )
	{
    if( visitados.at((*it).first) == VISITADO)
		{
			continue;
		}else{
			struct arista una_arista;
			una_arista.un_nodo = nodo_actual;
			una_arista.otro_nodo = ((*it).first);
			una_arista.peso = ((*it).second);
			aristas_a_elegir.push(una_arista);
		}
  }
  return;
}

bool grafo_generador_minimo::visite_a(int nodo)
{
  return visitados.at(nodo) == VISITADO;
}

void inicializar_vector_con(int inicializador, vector<int> &un_vector, int mi_size )
{
  for(int i = 0; i < mi_size; i++)
  {
    un_vector.push_back( inicializador );
  }
  un_vector.resize(mi_size);

	return;
}

bool hay_entrada(int &primer_numero)
{
	cin >> primer_numero;
	bool respuesta;
	if(primer_numero == 0)
		respuesta = false;
	else
		respuesta = true;
	return respuesta;
}

void grafo_lista_adyacencias::crear_instancia_del_problema(int cantidad_servidores)
{
	int cantidad_enlaces;
	cin >> cantidad_enlaces;

	lista_adyacencias.resize(cantidad_servidores + 1);


	for( int indice = 0; indice < cantidad_enlaces; indice++)
	{
		int nodo_uno, nodo_dos, peso_arista;
		cin >> nodo_uno;
		cin >> nodo_dos;
		cin >> peso_arista;

		pair<NODO,PESO> una_arista(nodo_dos, peso_arista);
		lista_adyacencias.at(nodo_uno).push_back(una_arista);

		pair<NODO,PESO> misma_arista(nodo_uno, peso_arista);
		lista_adyacencias.at(nodo_dos).push_back(misma_arista);

	}

	return;
}

bool grafo_lista_adyacencias::existe_arista_entre_nodos(int nodo_uno, int nodo_dos, int peso_arista)
{
	bool existe_arista_n1_a_n2 = false;
	auto it = lista_adyacencias.at(nodo_uno).cbegin();
	auto it_final = lista_adyacencias.at(nodo_uno).cend();
	for(it; it != it_final; ++it )
	{
		if( ((*it).first == nodo_dos) and ((*it).second == peso_arista) )
			existe_arista_n1_a_n2 = true;
	}

	return existe_arista_n1_a_n2 ;
}

void grafo_lista_adyacencias::crear_instancia_del_problema_sin_cantidad_servidores()
{
	int cantidad_servidores;
	cin >> cantidad_servidores;

	this->crear_instancia_del_problema(cantidad_servidores);
}

bool visite_todos_los_nodos(vector<int> visitados)
{
  for(int indice = 1; indice < visitados.size(); indice++)
  {
    if(visitados.at(indice) == NO_VISITADO) return false;
  }
  return true;
}
