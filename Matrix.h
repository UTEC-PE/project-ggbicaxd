#ifndef MATRIX_H
#define MATRIX_H

template <typename G>
struct Matrix{
public:
    typedef typename G::N N;
    typedef typename G::E E;
    typedef typename G::edge edge;
    typedef typename G::EdgeSeq EdgeSeq;

    int V;
    int **matriz1;
    int **matriz2;

    Matrix(int V):V(V){
      matriz1=new int*[V];
      for(int x=0;x<V;x++){
        matriz1[x]=new int[V];
      }
      matriz2=new int*[V];
      for(int x=0;x<V;x++){
        matriz2[x]=new int[V];
      }
    }
    void print(){
      cout<<"Matriz de distancias"<<endl;
      for(int f=0;f<V;f++){
        for(int h=0;h<V;h++){
          if(matriz1[f][h]==INT_MAX){
            cout<<"I ";
          }
          else{
            cout<<matriz1[f][h]<<" ";
          }
        }
        cout<<endl;
      }

      cout<<"Matriz caminos"<<endl;
      for(int q=0;q<V;q++){
        for(int w=0;w<V;w++){
          cout<<matriz2[q][w]<<" ";
        }
        cout<<endl;
      }
    }
};




#endif
