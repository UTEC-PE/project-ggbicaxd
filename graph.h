#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "node.h"
#include "edge.h"

using namespace std;

class Traits {
	public:
		typedef int N;
		typedef int E;
};

template <typename Tr>
class Graph {
    public:
        typedef Graph<Tr> self;
        typedef Node<self> node;
        typedef Edge<self> edge;
        typedef vector<node*> NodeSeq;
        typedef list<edge*> EdgeSeq;
        typedef typename Tr::N N;
        typedef typename Tr::E E;
        typedef typename NodeSeq::iterator NodeIte;
        typedef typename EdgeSeq::iterator EdgeIte;

        void read_file(string file)
        {
            ifstream read(file);
            string lines;
            double x; 
            double y;

            getline(read,lines);
            int new_node = stoi (lines);
            cout << new_node << "\n";
            for(int i = 0; i<new_node; i++)
            {
                //insert_nodo
                getline(read, lines);
                stringstream ss(lines);
                ss >> x >> y;
                node* nodo = new node(i,x,y);
                cout << x << " " << y << "\n";
            }
            
            getline(read, lines);
            int vertex0, vertexf;
            E height;
            bool dir;

            while(getline(read,lines))
            {
                stringstream ss(lines);
                ss >> vertex0 >> vertexf >> height >> dir;
                cout << vertex0 << " " << vertexf << " " << height << " " << dir <<"\n"; 
            }
             
            read.close();
        }
    private:
        NodeSeq nodes;
        NodeIte ni;
        EdgeIte ei;
};

typedef Graph<Traits> graph;

#endif