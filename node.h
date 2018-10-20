#ifndef NODE_H
#define NODE_H

template <typename G>
class Node {
    public:
        typedef typename G::N N;
        typedef typename G::E E;
        typedef typename G::edge edge;
        typedef typename G::EdgeSeq EdgeSeq;

        EdgeSeq edges;
        Node(N data, double x, double y)
        {
            this->data = data;
            this->x = x;
            this->y = y;
            this->gradoSalida=0;
            this->gradoLlegada=0;
            this->padre=nullptr;
        }
        N getdata(){
          return data;
        }
        int gradosalida(){
          return gradoSalida;
        }
        int gradollegada(){
          return gradoLlegada;
        }
        void setgradosalida(bool x){
          if(x==0)
          this->gradoSalida++;
          else
          this->gradoSalida--;
        }
        void setgradollegada(bool x){
          if(x==0)
          this->gradoLlegada++;
          else
          this->gradoLlegada--;
        }
        Node* buscarpadre(){
          if(this->padre==nullptr){
            return nullptr;
          }
          else if(this->padre!=this){
            this->padre=this->padre->buscarpadre();
          }
          return padre;
        }
        void setpadre(Node<G>* nodo ){
          this-> padre=nodo;
        }
        Node<G>* padre;
    private:

        N data;
        int gradoSalida;
        int gradoLlegada;
        double x;
        double y;

};

#endif
