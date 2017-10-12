

#ifndef ALGO3_TP2_RUTAS_EJE_H
#define ALGO3_TP2_RUTAS_EJE_H

#include <ostream>

struct Eje {
    int origen, destino, peso;
    bool operator<(const Eje& r) {return peso < r.peso;}
    bool operator>(const Eje& r) {return peso > r.peso;}

    friend std::ostream & operator<<(std::ostream & os, const Eje& e) {
        os << "(" << e.origen << ", " << e.destino << ", " << e.peso << ")";
    }
};

#endif //ALGO3_TP2_RUTAS_EJE_H
