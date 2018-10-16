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

    private:
        N data;
        int gradoSalida;
        int gradoLlegada;
        double x;
        double y;

};

#endif
