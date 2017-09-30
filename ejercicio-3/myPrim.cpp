//
// Created by reivaj on 21/05/17.
//
#include<bits/stdc++.h>
#include "listaAdyacencia.hpp"
# define INF 0x3f3f3f3f


typedef pair<int, int> iPair;

class Graph
{
    int cantVertices;

    list <iPair> *ejesConPeso;

public:

    Graph(int cantVertices);  // Constructor
    void agEje(int nodo1, int nodo2, int peso);

    //imprime el Arbol Generador Minimo con Prim
    void primAGM();
};

Graph::Graph(int V)
{
    this->cantVertices = V;
    ejesConPeso= new list<iPair> [V];
}

void Graph::agEje(int nodo1, int nodo2, int peso)
{
    //cada indice de la lista representa un nodo y sus vecinos, con el peso del eje que los une
    ejesConPeso[nodo1].push_back(make_pair(nodo2, peso));
    ejesConPeso[nodo2].push_back(make_pair(nodo1, peso));
}
void Graph::primAGM()
{
    //Creo una cola de prioridad, mas informacion aqui...
    // http://geeksquiz.com/implement-min-heap-using-stl/
    priority_queue< iPair, vector <iPair> , greater<iPair> > priorCola;

    int src = 0; // Taking vertex 0 as source

    //inicializo un vector para las claves en INF
    vector<int> clave(cantVertices, INF);

    // almaceno los padres
    vector<int> padres(cantVertices, -1);

    // para ver si un nodo pertenece al AGM o no...
    vector<bool> inAGM(cantVertices, false);
    priorCola.push(make_pair(0, src));
    clave[src] = 0;

    while (!priorCola.empty())
    {
        int u = priorCola.top().second;
        priorCola.pop();

        inAGM[u] = true;  // Incluyo el nodo en el AGM

        // recorro todos los vecinos con 'i'
        list< pair<int, int> >::iterator i;
        for (i = ejesConPeso[u].begin(); i != ejesConPeso[u].end(); ++i)
        {
            // tomo los datos del vecino
            int v = (*i).first;
            int weight = (*i).second;

            //  Si v no esta en el AGM y el peso de (u,v) es menor
            // que la clave actual de v.
            if (inAGM[v] == false && clave[v] > weight)
            {
                // Actualizo clave de v
                clave[v] = weight;
                priorCola.push(make_pair(clave[v], v));
                padres[v] = u;
            }
        }
    }

    // Imprimo los ejes usando el vector de padres.
    for (int i = 1; i < cantVertices; ++i)
        printf("%d - %d\n", padres[i], i);
}

int main()
{
    // creando el grafo
    int cantVertices = 9;
    Graph g(cantVertices);

    //  agregando las aristas
    g.agEje(0, 1, 4);
    g.agEje(0, 7, 8);
    g.agEje(1, 2, 8);
    g.agEje(1, 7, 11);
    g.agEje(2, 3, 7);
    g.agEje(2, 8, 2);
    g.agEje(2, 5, 4);
    g.agEje(3, 4, 9);
    g.agEje(3, 5, 14);
    g.agEje(4, 5, 10);
    g.agEje(5, 6, 2);
    g.agEje(6, 7, 1);
    g.agEje(6, 8, 6);
    g.agEje(7, 8, 7);

    g.primAGM();

    return 0;
}