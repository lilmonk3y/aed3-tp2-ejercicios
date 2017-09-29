#include <vector>
#include <list>


using namespace std;

template<typename T>
class listaAdyacencia{

private:

	vector<list<T>> _nodos;
	bool _indexadoEnCero;

public:

	listaAdyacencia(unsigned cantNodos, bool indexadoEnCero):
		 _nodos(cantNodos, list<T>()),
		 _indexadoEnCero(indexadoEnCero){

	}

	void agregarVecino(unsigned nodo, T dato){
		unsigned numNodo = nodo - _indexadoEnCero*1;
		_nodos[numNodo].push_back(dato);
	}

	const list<T>& vecinos(unsigned nodo) const{
		unsigned numNodo = nodo - _indexadoEnCero*1;
		return _nodos[numNodo];
	}
};