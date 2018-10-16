//#include <GL/glut.h>
#include <iostream>

#include "graph.h"

using namespace std;

int main(int argc, char *argv[]) {
    Graph<Traits> mygraph(0);
    mygraph.read_file("graph2.txt");
    mygraph.print();
    cout<<"grado del nodo 2: "<<mygraph.getGradoNodo(2)<<endl;
    cout<<"grado de salida del nodo 2: "<<mygraph.getGradoNodoS(2)<<endl;
    cout<<"grado de llegada del nodo 2: "<<mygraph.getGradoNodoLL(2)<<endl;
    cout<<"nodos "<<mygraph.nodos<<endl;
    cout<<"aristas "<<mygraph.aristas<<endl;
    cout<<endl;
    mygraph.removerNodo(4);
    //mygraph.removerNodo(1);
    mygraph.removerArista(2,0);
    mygraph.removerArista(0,3);
    mygraph.print();
    cout<<endl;
    cout<<"grado del nodo 2: "<<mygraph.getGradoNodo(2)<<endl;
    cout<<"grado de salida del nodo 2: "<<mygraph.getGradoNodoS(2)<<endl;
    cout<<"grado de llegada del nodo 2: "<<mygraph.getGradoNodoLL(2)<<endl;
    cout<<"nodos "<<mygraph.nodos<<endl;
    cout<<"aristas "<<mygraph.aristas<<endl;
    //system("PAUSE");


    return EXIT_SUCCESS;
}
