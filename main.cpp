//#include <GL/glut.h>
#include <iostream>

#include "graph.h"

using namespace std;

int main(int argc, char *argv[]) {
    Graph<Traits> mygraph(1);
    mygraph.read_file("graph1.txt");
    mygraph.print();
    auto temp=mygraph.buscarnodo(0);
    mygraph.comprobar_conectividad(temp);
    //mygraph.bfs(temp);
    //mygraph.dfs(temp);
    //mygraph.prim(temp);
    //mygraph.isbipartito();
    //system("PAUSE");


    return EXIT_SUCCESS;
}
