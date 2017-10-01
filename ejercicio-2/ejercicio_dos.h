#include <vector> /* VECTOR OPERATIONS */
#include <iostream> /* COUT, ENDL */
#include <climits> /* INT_MAX, INT_MIN */
#include <queue>  /* queue */
#include <cassert> /* assert */

using namespace std;

int elegir_master(vector<vector<int> > lista_adyacencias);
int nodo_mas_lejano_a(int nodo_origen, vector<vector<int> > lista_adyacencias);
int elegir_nodo_intermedio_entre(int nodo_origen, int nodo_destino, vector<vector<int> > lista_adyacencias);
void inicializar_vector_con(int inicializador, vector<int> &un_vector, int mi_size);
int indice_del_maximo_de(vector<int> &distancias);
int indice_del_minimo_de(vector<int> &distancias);
int nodo_cuya_distancia_es_igual_a( int valor_a_buscado, vector<int> &distancias);
vector<int> distancias_de_un_nodo_a_todos_los_demas(int nodo_origen, vector<vector<int> > lista_adyacencias);
int maximo_valor_de(vector<int> &distancias);

struct camino_entre_dos_nodos{
  int nodo_origen;
  int nodo_destino;
  vector<vector<int> > lista_adyacencias;
  vector<int> camino;
  vector<int> visitados;
};
bool aux_elegir_nodo_intermedio_entre(int nivel, struct camino_entre_dos_nodos &parametros);
