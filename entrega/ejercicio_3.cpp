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
    int clientes;
};


struct paraSalida {
    list<int> rutasFinal;
    int cantRutasNecesarias;
    int costo;
};

//Del problema original

bool existeFabrica(listaAdyacencia<int> & lista, int fabricas, int n , int nodoInicial);

paraSalida conectandoClientes(int n, int fabricas, std::list<Eje> & edges) {

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

    //preparo la salida
    paraSalida salida;
    salida.costo = costo;
    salida.cantRutasNecesarias = uds.edges().size();

    for(std::list<Eje>::iterator itEjes = uds.edges().begin(); itEjes != uds.edges().end(); itEjes++){
        Eje eje = *itEjes;
        salida.rutasFinal.push_back(eje.origen);
        salida.rutasFinal.push_back(eje.destino);
    }
//    cout << "El grafo resultante es: \n";
//    for(std::list<int>::iterator itEjes = salida.rutasFinal.begin(); itEjes != salida.rutasFinal.end(); itEjes++){
//        cout << "Eje: \n" << *itEjes << " -> ";
//        itEjes++;
//        cout << *itEjes <<"\n";
//    }

    return salida;
}
//=========================AUXILIAR==========================

bool existeFabrica(listaAdyacencia<int> & lista, int fabricas, int n , int nodoInicial) {
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

    int clientes = 0;
    int fabricas = 0;
    int cantRutas = 0;
    paraElParser salida;

    cin >> fabricas >> clientes >> cantRutas;
    // tomo los parametros F C R

    salida.cantRutas = cantRutas;
    salida.fabricas = fabricas;
    salida.clientes = clientes;

    // me creo una lista para las rutas
    // cada lista sera una instancia del problema

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
        salida.rutas.push_back(eje);
        //agrego el eje a la lista de rutas

        countLines++;
    }
    return salida;
}


int main(){
// Estas tres lineas las usaba para el INPUT
   // std::ifstream in("/home/reivaj/CLionProjects/AGMKruskalEj3/ejDeEntrada.txt");
   // std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
   // std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!

   paraElParser miEntrada = parser();
   int fabricas = miEntrada.fabricas;
   int clientes = miEntrada.clientes;

   paraSalida miSalida = conectandoClientes(fabricas+clientes, fabricas, miEntrada.rutas);
   cout << miSalida.costo << " " << miSalida.cantRutasNecesarias;

   for(std::list<int>::iterator itEjes = miSalida.rutasFinal.begin(); itEjes != miSalida.rutasFinal.end(); itEjes++){
       cout << " " << *itEjes;
       itEjes++;
       cout << " " << *itEjes;
   }


//    std::ofstream out("/home/reivaj/CLionProjects/AGMKruskalEj3/grafoAleatorio.txt");
//    std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
//    std::cout.rdbuf(out.rdbuf()); //redirect std::cin to in.txt!

//

//
//    std::cout.rdbuf(coutbuf); //reset to standard output again



//    cout << conectandoClientes(fabricas+clientes, fabricas, miEntrada.rutas) << endl;
//
//    std::cin.rdbuf(cinbuf);   //reset to standard input again


}
