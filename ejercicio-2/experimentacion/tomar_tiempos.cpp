#include "../ejercicio_dos.h"
#include <time.h> /* clock_t, clock, CLOCKS_PER_SEC */
#include <fstream>
#include <math.h>

int handler_tiempos()
{

	ofstream file_object;
	string file_name = "cambiar_nombre_exp.csv";
	file_object.open(file_name);
	file_object << "# vertices" << ","<< "# aristas" << "," << "tiempo_global"
  << "," << "tiempo_crear_agm" << "," << "tiempo_elegir_master" << std::endl;

  // int cantidad_iteraciones_para_eliminar_ruido = 50;
	int cantidad_iteraciones_para_eliminar_ruido = 50;
  double promedio;
  double tiempo_primera_parte;
  double tiempo_segunda_parte;
  int cantidad_vertices;
  int cantidad_aristas;
	while(  hay_entrada(cantidad_vertices) )
  {
    class grafo_lista_adyacencias  grafo_input;
    cantidad_aristas = grafo_input.crear_instancia_del_problema(
		cantidad_vertices);

    /* Tiempos primera parte. */
    vector<double> vector_para_promediar_tiempos;
    clock_t cantidad_de_ticks_de_clock_cpu;

    for(int indice_ruido = 0; indice_ruido <
		cantidad_iteraciones_para_eliminar_ruido; indice_ruido++)
    {
      cantidad_de_ticks_de_clock_cpu = clock();

      class grafo_generador_minimo grafo_output;
      grafo_output.crear_agm_v2(grafo_input);

      cantidad_de_ticks_de_clock_cpu = clock() - cantidad_de_ticks_de_clock_cpu;
      /* Tiempo de la iteracion en segundos */
      double tiempo_iteracion =
			((double)cantidad_de_ticks_de_clock_cpu)/CLOCKS_PER_SEC;
      /* Tiempo de la iteracion en milisegundos */
      tiempo_iteracion = tiempo_iteracion * 1000;
      vector_para_promediar_tiempos.push_back(tiempo_iteracion);
    }
    /* Saco el promedio de clocks de correr esta instancia y lo imprimo en el
    archivo. */
    promedio = 0;

    for(int indice_promedios = 0; indice_promedios<
		cantidad_iteraciones_para_eliminar_ruido; indice_promedios++)
    {
      promedio += vector_para_promediar_tiempos[indice_promedios];
    }
    promedio = promedio /((double) cantidad_iteraciones_para_eliminar_ruido);
    // promedio = log(promedio);

    tiempo_primera_parte = promedio;



    /* Tiempos segunda parte. */
    class grafo_generador_minimo grafo_output;
    grafo_output.crear_agm_v2(grafo_input);

    vector<double> vector_promedios_de_iteraciones;
    //clock_t cantidad_de_ticks_de_clock_cpu;
    for(int indice_ruido = 0; indice_ruido <
		cantidad_iteraciones_para_eliminar_ruido; indice_ruido++)
    {
      cantidad_de_ticks_de_clock_cpu = clock();

      int nodo_master = grafo_output.elegir_master();

      cantidad_de_ticks_de_clock_cpu = clock() - cantidad_de_ticks_de_clock_cpu;
      /* Tiempo de la iteracion en segundos */
      double tiempo_iteracion =
			((double)cantidad_de_ticks_de_clock_cpu)/CLOCKS_PER_SEC;
      /* Tiempo de la iteracion en milisegundos */
      tiempo_iteracion = tiempo_iteracion * 1000;
      vector_promedios_de_iteraciones.push_back(tiempo_iteracion);
    }
    /* Saco el promedio de clocks de correr esta instancia y lo imprimo en el
    archivo. */
    promedio = 0;
    for(int indice_promedios = 0; indice_promedios<
		cantidad_iteraciones_para_eliminar_ruido; indice_promedios++)
    {
      promedio += vector_promedios_de_iteraciones[indice_promedios];
    }
    promedio = promedio /((double) cantidad_iteraciones_para_eliminar_ruido);
    // promedio = log(promedio);

    tiempo_segunda_parte = promedio;

    /* IMPRIMIR EN EL CSV A "promedio" */
    file_object << cantidad_vertices<< ","<< cantidad_aristas
    << ","<< tiempo_primera_parte + tiempo_segunda_parte <<","<<tiempo_primera_parte
    <<","<<tiempo_segunda_parte<< std::endl;
		cantidad_vertices = 0;
  }
}

int main()
{
  handler_tiempos();
  return 0;
}
