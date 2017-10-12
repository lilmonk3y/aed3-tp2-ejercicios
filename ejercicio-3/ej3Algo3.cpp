//
// Created by reivaj on 29/09/17.
//

#include <utility>
#include <list>
#include <iostream>
#include "DisjointSet.h"
#include "listaDeAdyacencia.hpp"
#include <queue>


struct paraElParser {
    list<Eje> rutas;
    int cantRutas;
    int fabricas;
    int totalNodos;
};



bool existeFabrica(listaAdyacencia<int> lista, int fabricas, int n , int nodoInicial);

int conectandoClientes(int n, int fabricas, std::list<Eje> & edges) {

    DisjointSet uds(n+1);

    // Ordeno de forma ascendente
    edges.sort();
    int costo = 0;
    for(std::list<Eje>::iterator itEjes = edges.begin(); itEjes != edges.end(); ++itEjes) {
        const Eje &eje = *itEjes;

        DisjointSet::Subset setOrigen = uds.find(eje.origen);
        DisjointSet::Subset setDestino = uds.find(eje.destino);

        if (setDestino == setOrigen) {
            // Ruta innecesaria. Destruirla
            itEjes = edges.erase(itEjes);               //erase aumenta el iterador
            itEjes--;
            // No voy a necesitar las rutas innecesarias para el futuro.


        } else {
            // Dejar ruta
            costo += eje.peso;
            uds.unify(eje);
        }
    }


    //ya obtuve el AGMin de los ejes que me pasan como parametro. Pero todavia, podria tener ejes inutiles ya que
        // solo necesito una fabrica por componente conexa, y por ahora estoy agregando todas las fabricas ya que la tome
        // como un nodo mas. Debo buscar que fabricas puedo eliminar del AGM y todavia poder seguir satisfaciendo a los
        // clientes.


    // Invierto aristas
    for(std::list<Eje>::iterator it = uds.edges().begin(); it != uds.edges().end() ; it++) it->peso = it->peso * (-1);

    uds.edges().sort(); // ordeno los ejes de Mayor a Menor

    // creo listaDeAdyacencia
    listaAdyacencia<int> listaAdy(n+1);

    for(std::list<Eje>::iterator itEjes = uds.edges().begin(); itEjes != uds.edges().end(); ++itEjes){
        int origen = itEjes->origen;
        int destino = itEjes->destino;

        listaAdy.agregarVecino(origen, destino);
        listaAdy.agregarVecino(destino, origen);
    }
    std::list<Eje>::iterator itEjes = uds.edges().begin();
    int tam = uds.edges().size();
    for(int i = 0; i < tam; i++){
        Eje &eje = *itEjes;
        eje.peso = eje.peso * (-1);

        int peso = eje.peso;
        int origen = itEjes->origen;
        int destino = itEjes->destino;

        listaAdy.eliminarEje(origen, destino);
        listaAdy.eliminarEje(destino, origen);
        itEjes = uds.edges().erase(itEjes);

        // miro la componente conexa que tendra al origen y me fijo si hay una fabrica, luego miro la cc que tiene a
        // destino y si hay fabrica en ambas, puedo eliminar ese eje

        if(! (existeFabrica(listaAdy, fabricas, n, origen) && existeFabrica(listaAdy, fabricas, n, destino))){
            listaAdy.nodos()[origen].push_back(destino);
            Eje e;
            e.origen = origen;
            e.destino = destino;
            e.peso = peso;
            uds.edges().push_back(e);
            listaAdy.agregarVecino(origen, destino);
            listaAdy.agregarVecino(destino, origen);

            // si no hay fabrica en alguna cc, agrego nuevamente el eje.
        }
        else {
            costo = costo - eje.peso;
            // si existen fabricas en ambas cc resultante de quitar el eje, dejo la listaAdy sin ese eje
        }

    }

    cout << "El grafo resultante es: \n";
    for(std::list<Eje>::iterator itEjes = uds.edges().begin(); itEjes != uds.edges().end(); itEjes++){
        cout << "Eje: \n" << *itEjes << "\n";
    }
    return costo;
}





bool existeFabrica(listaAdyacencia<int> lista, int fabricas, int n , int nodoInicial) {
    vector<bool> visitado(n+1); // Inicializado False −>vector<Bool>(N,False) ;
    int t;
    queue<int> cola;
    cola.push(nodoInicial);
    visitado[nodoInicial] = true;

    while(!cola.empty()){
        t = cola.front();
        cola.pop();
        for (std::list<int>::const_iterator itEjes = lista.vecinos(t).begin(); itEjes != lista.vecinos(t).end(); ++itEjes){

            int destino = *itEjes;
            if(!visitado[destino]){ // si no tengo al eje en cuenta, no lo evaluo
                if(destino <= fabricas || t <= fabricas) return true;              // por lo tanto nunca agregare a la cola al
                visitado[destino] = true;                        // nodo destino que no quiero considerar
                cola.push(destino);                              // por lo que solo mirare la cc que contiene
            }                                                                // a destino y no a origen

        }
    }
    return false;
}


paraElParser parser(){

    int cantNodos = 0;
    int fabricas = 0;
    int cantRutas = 0;
    paraElParser salida;

    cin >> fabricas >> cantNodos >> cantRutas;
    // tomo los parametros F C R


    salida.cantRutas = cantRutas;
    salida.fabricas = fabricas;
    salida.totalNodos = cantNodos;

    // me creo una lista para las rutas
    // cada lista sera una instancia del problema
    list<Eje> rutas(cantRutas);

    int countLines = 0;
    int origen = 0;
    int destino = 0;
    int peso = 0;

    while((countLines < cantRutas)){
        cin >> origen >> destino >> peso; //aca recorrerria todos los ejes
        Eje eje;
        eje.origen = origen;
        eje.destino = destino;
        eje.peso = peso;
        rutas.push_back(eje);
        //agrego el eje a la lista de rutas

        countLines++;
    }

    salida.rutas = rutas;
    return salida;
}



int main(){

    Eje newEdge;
    newEdge.destino = 3;
    newEdge.origen = 1;
    newEdge.peso = 7;
    Eje newEdge1;
    newEdge1.destino = 6;
    newEdge1.origen = 1;
    newEdge1.peso = 100;
    Eje newEdge2;
    newEdge2.destino = 5;
    newEdge2.origen = 1;
    newEdge2.peso = 3;
    Eje newEdge3;
    newEdge3.destino = 4;
    newEdge3.origen = 3;
    newEdge3.peso = 5;
    Eje newEdge4;
    newEdge4.destino = 5;
    newEdge4.origen = 4;
    newEdge4.peso = 2;
    Eje newEdge5;
    newEdge5.destino = 6;
    newEdge5.origen = 5;
    newEdge5.peso = 10;
    // CC2

    Eje newEdge6;
    newEdge6.destino = 7;
    newEdge6.origen = 2;
    newEdge6.peso = 4;
    Eje newEdge7;
    newEdge7.destino = 8;
    newEdge7.origen = 2;
    newEdge7.peso = 100;
    Eje newEdge8;
    newEdge8.destino = 10;
    newEdge8.origen = 2;
    newEdge8.peso = 10;
    Eje newEdge9;
    newEdge9.destino = 8;
    newEdge9.origen = 10;
    newEdge9.peso = 2;
    Eje newEdge10;
    newEdge10.destino = 9;
    newEdge10.origen = 8;
    newEdge10.peso = 50;
    Eje newEdge11;
    newEdge11.destino = 9;
    newEdge11.origen = 10;
    newEdge11.peso = 2;
    Eje newEdge12;
    newEdge12.destino = 11;
    newEdge12.origen = 2;
    newEdge12.peso = 5;

    std::list<Eje> newGraph;
    newGraph.push_back(newEdge);
    newGraph.push_back(newEdge1);
    newGraph.push_back(newEdge2);
    newGraph.push_back(newEdge3);
    newGraph.push_back(newEdge4);
    newGraph.push_back(newEdge5);
    newGraph.push_back(newEdge6);
    newGraph.push_back(newEdge7);
    newGraph.push_back(newEdge8);
    newGraph.push_back(newEdge9);
    newGraph.push_back(newEdge10);
    newGraph.push_back(newEdge11);
    newGraph.push_back(newEdge12);

    cout << conectandoClientes(11, 2, newGraph) << endl;

    //paraElParser miEntrada = parser();



}
