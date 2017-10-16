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
		int peso_grafo_output = grafo_output.peso();
		// sub-problema-dos
		int nodo_master = grafo_output.elegir_master();
		// output
		grafo_output.imprimir_solucion(peso_grafo_output, nodo_master);
	}
	return;
}

void grafo_generador_minimo::crear_agm(grafo_lista_adyacencias grafo_input)
{
	/* El AGM lo hago con el enfoque de PRIM */

	// init grafo_generador_minimo
  inicializar_vector_con(NO_VISITADO, visitados, grafo_input.lista_adyacencias.size());

  /* Empiezo con el nodo 0 */
  int nodo_actual = 0;
  int cantidad_nodos_visitados = 0;
  while( cantidad_nodos_visitados < grafo_input.lista_adyacencias.size() )
  {
    if( not visite_a(nodo_actual) )
    {
      visitados.at(nodo_actual) = VISITADO;
      cantidad_nodos_visitados++;
      agregar_aristas_adyacentes_a(nodo_actual, grafo_input);
    }
    struct arista una_arista = minima_arista_que_no_forma_ciclos();
    agregar_arista_al_agm(una_arista);
    nodo_actual = nodo_que_no_visite(una_arista);
  }

  assert( visite_todos_los_nodos(visitados) );
  return;
}

int grafo_generador_minimo::peso()
{
	assert( DEBO_IMPLEMENTAR );

	return 0;
}

int grafo_generador_minimo::elegir_master()
{
	//Elijo un nodo aleatorio y lo llamo "s"
  int nodo_s = 0;
  int nodo_v = nodo_mas_lejano_a(nodo_s);
  int nodo_w = nodo_mas_lejano_a(nodo_v);
  return elegir_nodo_intermedio_entre(nodo_v, nodo_w);
}

void grafo_generador_minimo::imprimir_solucion(int peso_grafo, int nodo_master)
{
	assert( DEBO_IMPLEMENTAR );

	return;
}
























/*------------------------------------ Por revisar --------------------*/

bool visite_todos_los_nodos(vector<int> visitados)
{
  for(int indice = 0; indice < visitados.size(); indice++)
  {
    if(visitados.at(indice) == NO_VISITADO) return false;
  }
  return true;
}

/*            dos.dos           */



int grafo_generador_minimo::nodo_mas_lejano_a(int nodo_origen)
{
  vector<int> distancias = distancias_de_un_nodo_a_todos_los_demas(nodo_origen);
  return indice_del_maximo_de(distancias);
}

int grafo_generador_minimo::elegir_nodo_intermedio_entre(int nodo_origen, int nodo_destino)
{
  /* La idea es que el nodo_origen es el de distancia 0 y el nodo_destino es
  el de distancia maxima pero todos en el medio existen, osea que yo elijo a
  uno en el médio y es el que devuelvo. La otra forma es reconstruir el camino
  entre nodo_origen y nodo_destino y tomar un nodo en el medio pero no se
  como reconstruirlo... */
  /* Esto en realidad está mal porque puede haber un nodo a la distancia que
  yo elijo pero que en realidad no está en el camino entre los dos nodos. */

  //vector<int> distancias = distancias_de_un_nodo_a_todos_los_demas(nodo_origen, lista_adyacencias);
  //assert( indice_del_maximo_de(distancias) == nodo_destino );
  //assert( indice_del_minimo_de(distancias) == nodo_origen );
  //int distancia_intermedia = ((int) maximo_valor_de(distancias) / 2);
  //return nodo_cuya_distancia_es_igual_a(distancia_intermedia, distancias);

	/*
  vector<int> camino;
  vector<int> visitados;
  inicializar_vector_con(0,visitados, lista_adyacencias.size());

  struct camino_entre_dos_nodos parametros;
  parametros.nodo_origen = nodo_origen;
  parametros.nodo_destino = nodo_destino;
  parametros.lista_adyacencias = lista_adyacencias;
  parametros.camino = camino;
  parametros.visitados = visitados;

  visitados.at(nodo_origen) = VISITADO;
  aux_elegir_nodo_intermedio_entre(nodo_origen, parametros);
  int respuesta = camino.at( ((int) camino.size() / 2) );
  return respuesta;
	*/
	return 0;
}

bool aux_elegir_nodo_intermedio_entre(int nivel, struct camino_entre_dos_nodos &parametros)
{
	// 		ARREGLAR YA QUE ANTES LO IMPLEMENTE CON VECTOR DE VECTOR Y AHORA ES VECTOR DE LISTAS

  bool respuesta = false;

  // if(parametros.visitados.at(nivel) == VISITADO) return respuesta;
  //
  // parametros.visitados.at(nivel) = VISITADO;
  // if(nivel == parametros.nodo_destino)
  // {
  //   respuesta = true;
  //   parametros.camino.push_back(nivel);
  // }else{
  //   int adyacente;
  //   for(int un_adyacente; un_adyacente < parametros.lista_adyacencias.at(nivel).at(un_adyacente); un_adyacente++)
  //   {
  //     adyacente = parametros.lista_adyacencias.at(nivel).at(un_adyacente);
  //     respuesta = aux_elegir_nodo_intermedio_entre(adyacente, parametros);
  //     if(respuesta) break;
  //   }
  //   if(respuesta) parametros.camino.push_back(nivel);
  // }
  return respuesta;
}

int nodo_cuya_distancia_es_igual_a( int valor_a_buscado, vector<int> &distancias)
{
  for(int indice = 0; indice < distancias.size(); indice++)
    if(distancias.at(indice) == valor_a_buscado) return distancias.at(indice);

  assert( false ); /* NO DEBO LLEGAR ACÁ PORQUE EL ELEMENTO QUE BUSCO EXISTE */
}

vector<int> grafo_generador_minimo::distancias_de_un_nodo_a_todos_los_demas(int nodo_origen)
{
	// ARREGLAR PORQUE ANTES ERA UN VECTOR DE VECTOR Y AHORA ES UN VECTOR DE LISTAS;



  /*Elijo un enfoque BFS para encontrar el nodo más lejano a nodo_origen */
  vector<int> elementos_visitados;
  inicializar_vector_con( 0, elementos_visitados , lista_adyacencias.size() );
  vector<int> distancias;
  inicializar_vector_con( INFINITO, distancias, lista_adyacencias.size() );
  queue<int> cola;

  // cola.push(nodo_origen);
  // elementos_visitados.at(nodo_origen) = VISITADO;
  // distancias.at(nodo_origen) = 0;
  // while( not cola.empty() ){
  //   int un_nodo = cola.front();
  //   cola.pop();
  //   int adyacente_a_un_nodo;
  //   for(int un_adyacente = 0; un_adyacente < lista_adyacencias.at(un_nodo).size(); un_adyacente++)
  //   {
  //     adyacente_a_un_nodo = lista_adyacencias.at(un_nodo).at(un_adyacente);
  //     if( elementos_visitados.at(adyacente_a_un_nodo) == NO_VISITADO )
  //     {
  //       elementos_visitados.at(adyacente_a_un_nodo) = VISITADO;
  //       distancias.at(adyacente_a_un_nodo) = distancias.at(un_nodo) + 1;
  //       cola.push(adyacente_a_un_nodo);
  //     }
  //   } /* ya mire todos los adyacentes a un_nodo */
  // } /* ya mire todos los nodos del arbol */
  return distancias;
}



int indice_del_maximo_de(vector<int> &distancias)
{
  int maximo = 0;
  for(int indice = 1; indice < distancias.size(); indice++ )
    if( distancias.at(maximo) < distancias.at(indice) ) maximo = indice;

  return maximo;
}

int indice_del_minimo_de(vector<int> &distancias)
{
  int minimo = 0;
  for(int indice = 1; indice < distancias.size(); indice++ )
    if( distancias.at(minimo) >  distancias.at(indice) ) minimo = indice;

  return minimo;
}

int maximo_valor_de(vector<int> &distancias)
{
  int maximo = INT_MIN;
  for(int indice = 0; indice < distancias.size(); indice++)
    if( maximo < distancias.at(indice) ) maximo = distancias.at(indice);

  return maximo;
}


































/*--------------------------- Revisadas y auxiliares ------------------------*/

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
	pair<NODO,PESO> un_nodo(una_arista.otro_nodo, una_arista.peso);
	pair<NODO,PESO> otro_nodo(una_arista.un_nodo, una_arista.peso);

  lista_adyacencias.at(una_arista.un_nodo).push_back(un_nodo);
  lista_adyacencias.at(una_arista.otro_nodo).push_back(otro_nodo);

  return;
}

/* Devuelvo una arista en la que uno de sus dos extremos no fue visitado */
struct arista grafo_generador_minimo::minima_arista_que_no_forma_ciclos()
{
  struct arista una_arista;

	/* saco aristas hasta que me de una arista que no forma ciclos */
  while(true)
  {
    una_arista = aristas_a_elegir.top();
    aristas_a_elegir.pop();

    if( not visite_a(una_arista) ) break;
  }
  return una_arista;
}

bool grafo_generador_minimo::visite_a(struct arista una_arista)
{
  return ( (visitados.at(una_arista.otro_nodo) == VISITADO) and  (visitados.at(una_arista.un_nodo) == VISITADO) );
}

void grafo_generador_minimo::agregar_aristas_adyacentes_a(int nodo_actual, grafo_lista_adyacencias  &grafo_input)
{
	auto it = lista_adyacencias.at(nodo_actual).cbegin();
	auto it_final = lista_adyacencias.at(nodo_actual).cend();
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

	lista_adyacencias.resize(cantidad_servidores +1);

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
