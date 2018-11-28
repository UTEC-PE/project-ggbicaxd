#ifndef CAMINO_H
#define CAMINO_H

template <typename G>
struct Camino{
  typedef typename G::N N;
  typedef typename G::E E;
  typedef typename G::node node;
  typedef typename G::edge edge;
  typedef typename G::EdgeSeq EdgeSeq;

  EdgeSeq nodos;
  int peso;
  node* nodo;

  Camino(node* nodito, int weight){
    peso=weight;
    nodo=nodito;
  }
  void print(){
    cout<<nodo->getdata()<<" ";
    auto temp=nodo;
    for(auto item: nodos){
      if(item->nodes[0]!=temp){
        cout<<item->nodes[0]->getdata()<<" ";
        temp=item->nodes[0];
      }
      else if(item->nodes[1]!=temp){
        cout<<item->nodes[1]->getdata()<<" ";
        temp=item->nodes[1];
      }
    }

  }
};

#endif
