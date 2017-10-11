#include <vector>
#include <list>


using namespace std;

template<typename T>
class listaAdyacencia{

private:

	vector<list<T>> _nodos;

public:

	listaAdyacencia(int cantNodos):
		 _nodos(cantNodos, list<T>()){

	};


	void agregarVecino(int nodo, int dato){
		int numNodo = nodo;
		_nodos[numNodo].push_back(dato);
	}

	void eliminarEje(int origen, int destino){
		for(std::list<int>::const_iterator itEjes = vecinos(origen).begin(); itEjes != vecinos(origen).end(); ++itEjes){
			int destino1 = *itEjes;
			if(destino = destino1){
				_nodos[origen].remove(destino1);
				break;
			}
		}
	}

    vector<list<T>> nodos(){
        return _nodos;
    }

	const list<T>& vecinos(int nodo) {
		int numNodo = nodo;
		return _nodos[numNodo];
	}

};