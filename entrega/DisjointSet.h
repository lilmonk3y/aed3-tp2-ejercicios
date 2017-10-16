//
// Created by jscherman on 24/05/17.
//

#ifndef ALGO3_TP2_RUTAS_DISJOINTSET_H
#define ALGO3_TP2_RUTAS_DISJOINTSET_H


#include "Eje.h"
#include <list>
#include <iostream>

class DisjointSet {

public:

    struct Subset {
        int parent;
        std::list<Eje> edges;
        int rank;
        int size;

        friend std::ostream& operator<<(std::ostream& os, const Subset& s){
            os << "[Subset] parent: " << s.parent << ", rank: " << s.rank << ", size: " << s.size << ", edges: ";
            for (std::list<Eje>::const_iterator it = s.edges.begin(); it != s.edges.end(); it++) {
                os << *it << " ";
            }
            return os;
        }

        bool operator==(const Subset& s){
            return parent == s.parent;
        }

        bool operator!=(const Subset& s){
            return parent != s.parent;
        }
    };

    DisjointSet(int n) : totalSize(n) {
        subsets = new Subset*[n]();
        for (int i = 1; i < n; ++i) {
            makeSet(i);
        }
    };

    ~DisjointSet(){
        for (int i = 1; i < totalSize; ++i) {
            delete subsets[i];
        }
        delete[] subsets;
    }

    std::list<Eje> & edges() {return totalEdges;};


    void makeSet(int v) {
        subsets[v] = new Subset();
        subsets[v]->parent = v;
        subsets[v]->rank = 0;
        subsets[v]->size = 1;
    }

    Subset & find(int v) const {
        if (subsets[v]->parent == v) return *subsets[v];
        else find(subsets[v]->parent);
    }

    void unify(const Eje & eje) {
        Subset &srcSet = find(eje.origen);
        Subset &destSet = find(eje.destino);

        if (srcSet.rank > destSet.rank) {
            if (srcSet.parent != destSet.parent) srcSet.size += destSet.size;
            srcSet.edges.splice(srcSet.edges.begin(), destSet.edges);
            srcSet.edges.push_back(eje);
            destSet.parent = srcSet.parent;
        } else if (srcSet.rank < destSet.rank) {
            if (srcSet.parent != destSet.parent) destSet.size += srcSet.size;
            destSet.edges.splice(destSet.edges.begin(), srcSet.edges);
            destSet.edges.push_back(eje);
            srcSet.parent = destSet.parent;
        } else {
            if (srcSet.parent != destSet.parent) destSet.size += srcSet.size;
            destSet.edges.splice(destSet.edges.begin(), srcSet.edges);
            destSet.edges.push_back(eje);
            srcSet.parent = destSet.parent;
            destSet.rank++;
        }
        totalEdges.push_back(eje);
    };

    std::list<Subset*> sets() const {
        bool seen [totalSize] = {false};

        std::list<Subset*> ss;
        for (int i = 0; i < totalSize; ++i) {
            Subset &subset = find(i);
            if (!seen[subset.parent]) {
                seen[subset.parent] = true;
                ss.push_back(&subset);
            }
        }
        return ss;
    }

    friend std::ostream& operator<<(std::ostream& os, const DisjointSet& d){
        std::list<Subset*> subsets = d.sets();
        os << "[DisjointSet] totalSize: "<< d.totalSize << ", " << subsets.size() << " subsets: " << std::endl;
        for (std::list<Subset*>::const_iterator it = subsets.begin(); it != subsets.end(); it++) {
            os << "--> " << **it << std::endl;
        }
        return os;
    }

private:

    int totalSize;
    std::list<Eje> totalEdges;
    Subset ** subsets;

};


#endif //ALGO3_TP2_RUTAS_DISJOINTSET_H
