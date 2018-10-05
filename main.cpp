//#include <GL/glut.h>
#include <iostream>

#include "graph.h"

using namespace std;

int main(int argc, char *argv[]) {
    Graph<Traits> mygraph;
    mygraph.read_file("graph1.txt");
    system("PAUSE");


    return EXIT_SUCCESS;
}