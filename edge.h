#ifndef EDGE_H
#define EDGE_H

#include "node.h"

template <typename G>
class Edge {
    public:
        typedef typename G::E E;
        typedef typename G::node node;

        Edge(node *nodo1, node *nodo2,E dato ,bool dire){
          this->nodes[0]=nodo1;
          this->nodes[1]=nodo2;
          this->data=dato;
          this->dir=dire;
        };
        node* nodes[2];

        E getdata(){
          return data;
        }
    private:
        E data;
        bool dir;
};

#endif
