//
// Created by reivaj on 29/09/17.
//

#include <utility>
#include <list>
#include <iostream>
#include "DisjointSet.h"
#include "GrafoListaIncidencias.h"
#include "listaDeAdyacencia.hpp"
#include <queue>
#include "EjeSinPeso.h"
#include <fstream>
#include <math.h>
#include <chrono>
#include <vector>
#include <random>
#include <time.h>


struct paraElParser {
    list<Eje> rutas;
    int cantRutas;
    int fabricas;
    int clientes;
};


//Para Experimentos
int randomEnRangoDoble(int cotaMin, int cotaMax);
int randomEnRango(int cotaMax);
list<Eje> generarGrafoAleatorioConFabricas(int cantNodos, int cantEjes, int fabricas);
list<Eje> generarGrafoAleatorio(int cantNodos, int cantEjes);
list<Eje> generarGrafoConexo1Fabrica(int cantNodos, int cantEjes);
list<Eje> generarGrafoMaxCC(int cantNodos, int cantEjes);
list<Eje> generarGrafoCompleto(int cantNodos);
void printGrafo(std::list<Eje> grafo);
int calcularTiempo(int cantNodos, int fabricas, list<Eje>& rutas);
void escribirCsvEjesIgualNodos();



//Del problema original

bool existeFabrica(listaAdyacencia<int> & lista, int fabricas, int n , int nodoInicial);

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

//    cout << "El grafo resultante es: \n";
//    for(std::list<Eje>::iterator itEjes = uds.edges().begin(); itEjes != uds.edges().end(); itEjes++){
//        cout << "Eje: \n" << *itEjes << "\n";
//    }
    return costo;
}





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

//==============================EXPERIMENTOS=====================================\\\\\\\\\\\

int calcularTiempo(int cantNodos, int fabricas, list<Eje>& rutas){
    auto start = chrono::high_resolution_clock::now();
    conectandoClientes(cantNodos, fabricas, rutas);
    auto stop = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::nanoseconds>(stop-start).count();
}


void escribirCsvMuchosEjesvsPocos(){
    fstream archivo;
    long int acumuladorDeTiemposMuchosEjes = 0;
    long int acumuladorDeTiemposAleatorioPocosEjes = 0;
    long int acumuladorDeTiemposAleatorio = 0;
    int corridas = 8;
    archivo.open("/home/reivaj/CLionProjects/AGMKruskalEj3/csvVarianEjesLog.txt");
    archivo << "NODOS,   +Ejes,   ALEAT, -EJES " << "\n";
    for(int cantNodos = 5; cantNodos <= 200; cantNodos++){
        for(int h = 0; h < corridas; h++){

            int fabricas = randomEnRangoDoble(cantNodos/8,cantNodos/4);

            list<Eje> grafoAleatorioMuchosEjes(cantNodos);
            grafoAleatorioMuchosEjes = generarGrafoCompleto(cantNodos);
            acumuladorDeTiemposMuchosEjes = calcularTiempo(cantNodos, fabricas, grafoAleatorioMuchosEjes);

            list<Eje> grafoAleatorio(cantNodos);
            grafoAleatorio = generarGrafoAleatorio(cantNodos, randomEnRangoDoble(cantNodos*(cantNodos-1)/8,cantNodos*((cantNodos-1)/4)));
            acumuladorDeTiemposAleatorio = calcularTiempo(cantNodos, fabricas, grafoAleatorio);


            list<Eje> grafoAleatorioPocosEjes(cantNodos);
            grafoAleatorioPocosEjes = generarGrafoAleatorioConFabricas(cantNodos, cantNodos-1, fabricas);
            acumuladorDeTiemposAleatorioPocosEjes = calcularTiempo(cantNodos, fabricas, grafoAleatorioPocosEjes);


        }
        cout << cantNodos << "\n";
        archivo << cantNodos <<", " << log(acumuladorDeTiemposMuchosEjes / corridas)  << ", " << log(acumuladorDeTiemposAleatorio / corridas) << ", " << log(acumuladorDeTiemposAleatorioPocosEjes / corridas) << "\n";
    }
    archivo.close();
}

void escribirCsvEjesIgualNodos(){
    fstream archivo;
    long int acumuladorDeTiemposConexo = 0;
    long int acumuladorDeTiemposMaxCC = 0;
    long int acumuladorDeTiemposAleatorio = 0;
    int corridas = 15;
    archivo.open("/home/reivaj/CLionProjects/AGMKruskalEj3/csvMaxCCvsConexo.txt");
    archivo << "NODOS,   CONEXO,   MAXCC, ALEAT " << "\n";
    for(int cantNodos = 5; cantNodos <= 300; cantNodos++){
        for(int h = 0; h < corridas; h++){

            list<Eje> grafoConexo(cantNodos);
            grafoConexo = generarGrafoConexo1Fabrica(cantNodos, cantNodos-1);
            acumuladorDeTiemposConexo = calcularTiempo(cantNodos, 1, grafoConexo);

            list<Eje> grafoMaxCC(cantNodos);
            grafoMaxCC = generarGrafoMaxCC(cantNodos, cantNodos-1);
            acumuladorDeTiemposMaxCC = calcularTiempo(cantNodos, cantNodos/2, grafoMaxCC);

            int fabricas = randomEnRango(cantNodos/2);
            list<Eje> grafoAleatorio(cantNodos);
            grafoAleatorio = generarGrafoAleatorioConFabricas(cantNodos, cantNodos-1, fabricas);
            acumuladorDeTiemposAleatorio = calcularTiempo(cantNodos, fabricas, grafoAleatorio);


        }
        cout << cantNodos << "\n";
        archivo << cantNodos <<", " << (acumuladorDeTiemposConexo / corridas)  << ", " << (acumuladorDeTiemposMaxCC / corridas) << ", " << (acumuladorDeTiemposAleatorio / corridas) << "\n";
    }
    archivo.close();
}



void escribirCsvEjesIgualNodosVariaFabricas(){
    fstream archivo;
    long int acumuladorDeTiemposConexo = 0;
    long int acumuladorDeTiemposMaxCC = 0;
    long int acumuladorDeTiemposAleatorio = 0;
    int corridas = 15;
    archivo.open("/home/reivaj/CLionProjects/AGMKruskalEj3/csvMaxFabricasvs1Fabrica.txt");
    archivo << "NODOS,   1Fabrica,  ALEATFab, MaxFabr  " << "\n";
    for(int cantNodos = 5; cantNodos <= 300; cantNodos++){
        for(int h = 0; h < corridas; h++){

            list<Eje> grafoConexo(cantNodos);
            grafoConexo = generarGrafoConexo1Fabrica(cantNodos, cantNodos-1);
            acumuladorDeTiemposConexo = calcularTiempo(cantNodos, 1, grafoConexo);

            list<Eje> grafoMaxCC(cantNodos);
            grafoMaxCC = generarGrafoConexo1Fabrica(cantNodos, cantNodos-1);
            acumuladorDeTiemposMaxCC = calcularTiempo(cantNodos, cantNodos/2, grafoMaxCC);

            int fabricas = randomEnRangoDoble(cantNodos/8, cantNodos/4);
            list<Eje> grafoAleatorio(cantNodos);
            grafoAleatorio = generarGrafoConexo1Fabrica(cantNodos, cantNodos-1);
            acumuladorDeTiemposAleatorio = calcularTiempo(cantNodos, fabricas, grafoAleatorio);


        }
        cout << cantNodos << "\n";
        archivo << cantNodos <<", " << (acumuladorDeTiemposConexo / corridas)   << ", " << (acumuladorDeTiemposAleatorio / corridas) << ", " << (acumuladorDeTiemposMaxCC / corridas) << "\n";
    }
    archivo.close();
}



int randomEnRango(int cotaMax){
    int i = ((rand()+1) % (cotaMax+1));
    if(i == 0){
        return i+1;
    }
    else{
        return i;
    }
}

int randomEnRangoDoble(int cotaMin, int cotaMax){
    int i = ((rand()+1) % (cotaMax+1));
    if(i < cotaMin){
        i = i + cotaMin;
    }
    if(i == 0){
        return i+1;
    }
    else{
        return i;
    }
}

list<Eje> generarGrafoCompleto(int cantNodos) {
    list<Eje> grafo;
    int i = 0;
    int j = 1;
    while(j <= cantNodos){
        i = j+1;
        while (i <= cantNodos) {
            Eje eje;
            eje.origen = j;
            eje.destino = i;
            eje.peso = randomEnRango(50);
            grafo.push_back(eje);
            i++;
        }
        j++;
    }
    return grafo;
}

list<Eje> generarGrafoAleatorio(int cantNodos, int cantEjes){

    list<Eje> grafo;

    int ejesMarcados[cantNodos+1][cantNodos+1];
    for(int i = 0; i <= cantNodos; i++){
        for(int j = 0; j <= cantNodos; j++){
            ejesMarcados[i][j] = 0;
            if(j == i){
                ejesMarcados[i][j] = 1;
            }
        }
    }

    int i = 0;

    while(i < cantEjes){
        Eje eje;
        eje.origen = randomEnRango(cantNodos);
        eje.destino = randomEnRango(cantNodos);
        if(ejesMarcados[eje.origen][eje.destino] != 1){
            ejesMarcados[eje.origen][eje.destino] = 1;
            ejesMarcados[eje.destino][eje.origen] = 1;
            // el grafo que quiero no es DIRIGIDO
            eje.peso = randomEnRango(50);
            grafo.push_back(eje);
            i++;
        }
    }
    if(grafo.size() != cantEjes) cout << "ERROR: EJES != GRAFO SIZE\n";

    return grafo;
}

list<Eje> generarGrafoConexo1Fabrica(int cantNodos, int cantEjes){

    list<Eje> grafo;

    int ejesMarcados[cantNodos+1][cantNodos+1];
    for(int i = 0; i <= cantNodos; i++){
        for(int j = 0; j <= cantNodos; j++){
            ejesMarcados[i][j] = 0;
            if(j == i){
                ejesMarcados[i][j] = 1;
            }
        }
    }

    int i = 0;

    while(i < cantEjes){
        Eje eje;
        //primero hago que el grafo sea conexo
        if(i == 0){
            for(int j = 1; j < cantNodos; j++ ){
                eje.origen = j;
                eje.destino = j+1;
                eje.peso = randomEnRango(50);
                ejesMarcados[eje.origen][eje.destino] = 1;
                ejesMarcados[eje.destino][eje.origen] = 1;
                grafo.push_back(eje);
                i++;
            }
        }
        if(i == cantEjes) break;
        eje.origen = randomEnRango(cantNodos);
        eje.destino = randomEnRango(cantNodos);
        if(ejesMarcados[eje.origen][eje.destino] != 1){
            ejesMarcados[eje.origen][eje.destino] = 1;
            ejesMarcados[eje.destino][eje.origen] = 1;
            // el grafo que quiero no es DIRIGIDO
            eje.peso = randomEnRango(50);
            grafo.push_back(eje);
            i++;
        }
    }
    if(grafo.size() != cantEjes) cout << "ERROR: EJES != GRAFO SIZE\n";

    return grafo;
}


list<Eje> generarGrafoMaxCC(int cantNodos, int cantEjes){
    //maxCC = fabricas

    int fabricas = cantNodos/2;
    list<Eje> grafo;

    int j = fabricas+1;
    int ejesAgregados = 0;
    while(j <= cantNodos){
        Eje eje;
        eje.origen = 1;
        eje.destino = j;
        eje.peso = randomEnRango(50);
        grafo.push_back(eje);
        ejesAgregados++;
        j++;
    }
    // los ejes restantes los agrego a alguna cc, teniendo cuidado de no unir alguna cc.
    int q = fabricas+1;
    int l = q+1;
    while(l <= cantNodos && ejesAgregados < cantEjes){
        Eje eje;
        eje.origen = q;
        eje.destino = l;
        eje.peso = randomEnRango(50);
        grafo.push_back(eje);
        ejesAgregados++;
        if(l == cantNodos) q++;
        l++;

    }

    if(grafo.size() != cantEjes) cout << "ERROR: EJES != GRAFO SIZE\n";

    return grafo;
}

list<Eje> generarGrafoAleatorioConFabricas(int cantNodos, int cantEjes, int fabricas){
    //maxCC = fabricas

    list<Eje> grafo;

    int j = fabricas+1;
    int ejesAgregados = 0;
    while(j <= cantNodos){
        Eje eje;
        eje.origen = 1;
        eje.destino = j;
        eje.peso = randomEnRango(50);
        grafo.push_back(eje);
        ejesAgregados++;
        j++;
    }
    // los ejes restantes los agrego a alguna cc, teniendo cuidado de no unir alguna cc.
    int q = fabricas+1;
    int l = q+1;
    while(l <= cantNodos && ejesAgregados < cantEjes){
        Eje eje;
        eje.origen = q;
        eje.destino = l;
        eje.peso = randomEnRango(50);
        grafo.push_back(eje);
        ejesAgregados++;
        if(l == cantNodos) q++;
        l++;

    }

    if(grafo.size() != cantEjes) cout << "ERROR: EJES != GRAFO SIZE\n";

    return grafo;
}



void printGrafo(std::list<Eje> grafo){
    for (std::list<Eje>::iterator it = grafo.begin(); it != grafo.end(); it++) {
        Eje &eje = *it;
        int u = eje.origen;
        int v = eje.destino;
        int weight = eje.peso;
        cout << "c1:" << u << "| c2: " << v << "| peso: " << weight << endl;
    }
}

int main(){

    int tiempo = (time(NULL));
    srand(tiempo);

//    printGrafo(generarGrafoCompleto(5));
    escribirCsvMuchosEjesvsPocos();


//    std::ifstream in("/home/reivaj/CLionProjects/AGMKruskalEj3/ejDeEntrada.txt");
//    //std::ofstream out("/home/reivaj/CLionProjects/AGMKruskalEj3/salidasEjemplo.txt");
//    std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
//    //std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
//    std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
//    //std::cout.rdbuf(out.rdbuf()); //redirect std::cin to in.txt!
//
//    paraElParser miEntrada = parser();
//    int fabricas = miEntrada.fabricas;
//    int clientes = miEntrada.clientes;

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

