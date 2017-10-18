#include <vector> /* VECTOR OPERATIONS */
#include <list> /* LIST OPERATIONS */
#include <iostream> /* COUT, ENDL */
#include <climits> /* INT_MAX, INT_MIN */
#include <queue>  /* queue, priority_queue */
#include <cassert> /* assert */
#include <utility> /* pair */

#define NODO int
#define PESO int
#define INFINITO INT_MAX
#define VISITADO 1
#define NO_VISITADO 0
#define DEBO_IMPLEMENTAR false

using namespace std;



void func_main();

class grafo_lista_adyacencias{
  public:
    //el vector tiene n + 1 posiciones. la posición 0 no es válida.
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
    return a1.peso > a2.peso;
  }
};

class grafo_generador_minimo{
  public:
    /* metodos de clase */

    /* principales */
    void crear_agm(grafo_lista_adyacencias grafo_input);
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
    // solo tengo esto para hacerlo más sencillo de imprimir.
    int peso_agm;
    vector<struct arista> aristas_agm_imprimir;

};

class camino_entre_dos_nodos{
  public:
    /* METODOS DE LA CLASE */
    bool construir_diagonal(int nodo_origen);

    /* COLABORADORES INTERNOS */
    NODO nodo_origen;
    NODO nodo_destino;
    vector<list<pair<NODO,PESO> > > lista_adyacencias;
    vector<NODO> camino;
    vector<NODO> visitados;
};

NODO indice_del_maximo_de(vector<int> &distancias);
NODO indice_del_minimo_de(vector<int> &distancias);
NODO nodo_cuya_distancia_es_igual_a( NODO valor_a_buscado, vector<int> &distancias);




/* AUXILIARES */

bool hay_entrada(int &primer_numero);
void inicializar_vector_con(int inicializador, vector<int> &un_vector, int mi_size);
bool visite_todos_los_nodos(vector<int> visitados);
