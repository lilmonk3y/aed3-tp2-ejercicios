#include "../ejercicio_dos.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
// void hacer_un_grafo_conexo(int cantidad_vertices, ofstream &file_object)
// {
//   int un_extremo;
//   int otro_extremo;
//   int peso_arista;
//   for(int un_vertice = 1; un_vertice < cantidad_vertices; un_vertice++)
//   {
//     un_extremo = un_vertice;
//     otro_extremo = un_vertice + 1;
//     peso_arista = rand() % cantidad_vertices + 1;
//     file_object << un_extremo << otro_extremo << peso_arista << endl;
//   }
//   return;
// }

/* Creo instancias de grafos con una cantidad de aristas que va entre */
int main()
{
  //string file_name = "instancias_exp1/exp1_pocos_ejes.txt";
  string file_name = "exp1_pocos_ejes.txt";
  ofstream file_object;
  file_object.open(file_name);
  int cantidad_servidores = 50;
  int cantidad_enlaces = 49;
  int maxima_cantidad_de_enlaces = cantidad_servidores*cantidad_servidores;
  int cantidad_de_enlaces_para_agregar = maxima_cantidad_de_enlaces - (cantidad_servidores - 1);
  int un_extremo;
  int otro_extremo;
  int peso_arista;
  for(int indice = 0; indice < cantidad_de_enlaces_para_agregar;indice++)
  {
    file_object << cantidad_servidores << " " << cantidad_enlaces + indice <<endl;
    //hacer_un_grafo_conexo
    for(int un_vertice = 1; un_vertice < cantidad_servidores; un_vertice++)
    {
      un_extremo = un_vertice;
      otro_extremo = un_vertice + 1;
      peso_arista = rand();
      file_object << un_extremo << " "<< otro_extremo << " "<< peso_arista << endl;
    }
    //agregar_las_demas_aristas
    for(int cantidad_aristas = indice; cantidad_aristas > 0; cantidad_aristas--)
    {
      un_extremo = rand() % cantidad_servidores + 1;
      otro_extremo = rand() % cantidad_servidores + 1;
      // while(un_extremo == otro_extremo)
      //   otro_extremo = rand() % cantidad_servidores + 1;
      peso_arista = rand();
      file_object << un_extremo << " "<< otro_extremo << " "<< peso_arista << endl;
    }
  }
  file_object<< 0 << endl;
  file_object.close();
  return 0;
}
