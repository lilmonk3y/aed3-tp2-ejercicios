#include "ejercicio_dos.h"
#define INFINITO INT_MAX
#define VISITADO 1
#define NO_VISITADO 0
#define DEBO_IMPLEMENTAR false

int elegir_master(vector<vector<int> > lista_adyacencias)
{
  //Elijo un nodo aleatorio y lo llamo "s"
  int nodo_s = 0;
  int nodo_v = nodo_mas_lejano_a(nodo_s, lista_adyacencias);
  int nodo_w = nodo_mas_lejano_a(nodo_v, lista_adyacencias);
  return elegir_nodo_intermedio_entre(nodo_v, nodo_w, lista_adyacencias);
}

int nodo_mas_lejano_a(int nodo_origen, vector<vector<int> > lista_adyacencias)
{
  vector<int> distancias = distancias_de_un_nodo_a_todos_los_demas(nodo_origen,lista_adyacencias);
  return indice_del_maximo_de(distancias);
}

int elegir_nodo_intermedio_entre(int nodo_origen, int nodo_destino, vector<vector<int> > lista_adyacencias)
{
  vector<int> distancias = distancias_de_un_nodo_a_todos_los_demas(nodo_origen, lista_adyacencias);

  assert( indice_del_maximo_de(distancias) == nodo_destino );
  assert( indice_del_minimo_de(distancias) == nodo_origen );

  int distancia_intermedia = ((int) maximo_valor_de(distancias) / 2);
  return nodo_cuya_distancia_es_igual_a(distancia_intermedia, distancias);
}

int nodo_cuya_distancia_es_igual_a( int valor_a_buscado, vector<int> &distancias)
{
  for(int indice = 0; indice < distancias.size(); indice++)
    if(distancias.at(indice) == valor_a_buscado) return distancias.at(indice);

  assert( false ); /* NO DEBO LLEGAR ACÁ PORQUE EL ELEMENTO QUE BUSCO EXISTE */
}

vector<int> distancias_de_un_nodo_a_todos_los_demas(int nodo_origen, vector<vector<int> > lista_adyacencias)
{
  /*Elijo un enfoque BFS para encontrar el nodo más lejano a nodo_origen */
  vector<int> elementos_visitados;
  inicializar_vector_con( 0, elementos_visitados , lista_adyacencias.size() );
  vector<int> distancias;
  inicializar_vector_con( INFINITO, distancias, lista_adyacencias.size() );
  queue<int> cola;

  cola.push(nodo_origen);
  elementos_visitados.at(nodo_origen) = VISITADO;
  distancias.at(nodo_origen) = 0;
  while( not cola.empty() ){
    int un_nodo = cola.front();
    cola.pop();
    int adyacente_a_un_nodo;
    for(int un_adyacente = 0; un_adyacente < lista_adyacencias.at(un_nodo).size(); un_adyacente++)
    {
      adyacente_a_un_nodo = lista_adyacencias.at(un_nodo).at(un_adyacente);
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

void inicializar_vector_con(int inicializador, vector<int> &un_vector, int mi_size )
{
  for(int i = 0; i < mi_size; i++)
  {
    un_vector.push_back( inicializador );
  }
  un_vector.resize(mi_size);
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
