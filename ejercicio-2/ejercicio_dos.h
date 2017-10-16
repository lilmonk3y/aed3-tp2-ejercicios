#include <vector> /* VECTOR OPERATIONS */
#include <list> /* LIST OPERATIONS */
#include <iostream> /* COUT, ENDL */
#include <climits> /* INT_MAX, INT_MIN */
#include <queue>  /* queue, priority_queue */
#include <cassert> /* assert */
#include <utility> /* pair */

#define NODO int
#define PESO int

using namespace std;

/*                  main y parsers                */
void func_main();
bool hay_entrada(int &primer_numero);


class grafo_lista_adyacencias{
  public:
    vector<list<pair<NODO, PESO> > > lista_adyacencias;

    void crear_instancia_del_problema(int entrada);
    bool existe_arista_entre_nodos(int nodo_uno, int nodo_dos, int peso_arista);
    void crear_instancia_del_problema_sin_cantidad_servidores();
};

struct arista{
  int un_nodo;
  int otro_nodo;
  int peso;

  arista& operator=(const arista& otra_arista)
  {

    un_nodo = otra_arista.un_nodo;
    otro_nodo = otra_arista.otro_nodo;
    peso = otra_arista.peso;
    return *this;
  }
};

struct comparador_de_aristas{
  bool operator()(arista &a1, arista &a2)
  {
    return a1.peso < a2.peso;
  }
};

class grafo_generador_minimo{
  public:
    /* metodos de clase */

    /* principales */
    void crear_agm(grafo_lista_adyacencias grafo_input);
    int peso();
    int elegir_master();
    void imprimir_solucion(int peso_grafo, int nodo_master);

    /* auxiliares */
    void agregar_aristas_adyacentes_a(int nodo_actual, grafo_lista_adyacencias &grafo_entrada);
    void agregar_arista_al_agm(struct arista una_arista);
    struct arista minima_arista_que_no_forma_ciclos();
    bool visite_a(struct arista una_arista);
    bool visite_a(int nodo);
    int nodo_que_no_visite(struct arista una_arista);
    int nodo_mas_lejano_a(int nodo_origen);
    int elegir_nodo_intermedio_entre(int nodo_origen, int nodo_destino);
    vector<int> distancias_de_un_nodo_a_todos_los_demas(int nodo_origen);


    /* colaboradores internos */
    priority_queue<struct arista, vector<struct arista >, comparador_de_aristas> aristas_a_elegir;
    vector<int> visitados;
    vector<list<pair<NODO, PESO> > > lista_adyacencias;

};

bool visite_todos_los_nodos(vector<int> visitados);




/* dos.dos */


void inicializar_vector_con(int inicializador, vector<int> &un_vector, int mi_size);
int indice_del_maximo_de(vector<int> &distancias);
int indice_del_minimo_de(vector<int> &distancias);
int nodo_cuya_distancia_es_igual_a( int valor_a_buscado, vector<int> &distancias);
int maximo_valor_de(vector<int> &distancias);

struct camino_entre_dos_nodos{
  int nodo_origen;
  int nodo_destino;
  vector<list<int> > lista_adyacencias;
  vector<int> camino;
  vector<int> visitados;
};
bool aux_elegir_nodo_intermedio_entre(int nivel, struct camino_entre_dos_nodos &parametros);
