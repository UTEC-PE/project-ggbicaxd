//#include <GL/glut.h>
#include <iostream>

#include "graph.h"

using namespace std;

int main(int argc, char *argv[]) {
    Graph<Traits> mygraph(0);
    mygraph.read_file("graph1.txt");
    mygraph.print();
    int x=mygraph.getGradoNodoS(0);
    //cout<<x;
    auto temp=mygraph.buscarnodo(0);
    mygraph.dfs(temp);
    mygraph.kruskal();
    mygraph.prim(temp);

    mygraph.bfs(temp);

    mygraph.isbipartito();
    mygraph.comprobar_conectividad(temp);
    mygraph.getDensity(0.6);



    return EXIT_SUCCESS;
}
