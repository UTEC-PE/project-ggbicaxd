//#include <GL/glut.h>
#include <iostream>

#include "graph.h"

using namespace std;

int main(int argc, char *argv[]) {
    Graph<Traits> mygraph(0);
    mygraph.read_file("graph2.txt");
    mygraph.print();
    //system("PAUSE");


    return EXIT_SUCCESS;
}
