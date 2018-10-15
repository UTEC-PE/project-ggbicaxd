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

    private:
        NodeSeq nodes;
        NodeIte ni;
        EdgeIte ei;
				bool dir;

		public:

				Graph(bool dir):dir(dir){};

				void insertarnodo(int nombre,float x, float y){
				 int var=0;
				 for (int i = 0; i < nodes.size(); i++) {
					 if(nombre==nodes[i]->getdata()){
						 var=1;
						 break;
					 }
				 }
				 if(var==0){
					 node* nodo=new node(nombre,x,y);
					 nodes.push_back(nodo);
				 }
				 else{
					cout<<"nodo existente"<<endl;
				 }
				};

				void InsertArista(int nodo1, int nodo2,int peso){
					node* temp= nullptr;
					node* temp2= nullptr;
					for (int i = 0; i < nodes.size(); i++) {
						if(nodo1==nodes[i]->getdata()){
							temp=nodes[i];
							break;
 					 	}
					}
					for (int i = 0; i < nodes.size(); i++) {
						if(nodo2==nodes[i]->getdata()){
							temp2=nodes[i];
							break;
						}
					}
					if(!temp || !temp2){
						cout<<"no existe el nodo"<<"\n";
					}
					else if(dir==0){
						for ( auto& item : temp->edges )
						{
							if(item->nodes[0]->getdata()==nodo2 || item->nodes[1]->getdata()==nodo2){
								throw "arista ya existente";
							}
						}
						edge* arista=new edge(temp,temp2,peso,dir);
						temp->edges.push_back(arista);
						temp2->edges.push_back(arista);
					}
					else{
						for ( auto& item : temp->edges )
						{
							if(item->nodes[0]->getdata()==nodo2){
								throw "arista ya existente";
							}
						}
						edge* arista=new edge(temp,temp2,peso, dir);
						temp->edges.push_back(arista);
					}

				};

				void print() {
					for (int i = 0; i < nodes.size(); i++) {
						cout<<nodes[i]->getdata()<<" -> ";
						for ( auto& item : nodes[i]->edges )
						{
							cout<<item->getdata()<<" ";
						}
						cout<<endl;
					}
				};

			  void read_file(string file)
			  {
					ifstream read(file);
          string lines;
	        float x;
			    float y;

			    getline(read,lines);
			    int new_node = stoi (lines);
			    //cout << new_node << "\n";
			    for(int i = 0; i<new_node; i++)
			    {
						//insert_nodo
	          getline(read, lines);
			      stringstream ss(lines);
			      ss >> x >> y;
						insertarnodo(i,x,y);
			      //cout << x << " " << y << "\n";
			     }

			     getline(read, lines);
			     int vertex0, vertexf;
			     E weight;

			     while(getline(read,lines))
			     {
			      stringstream ss(lines);
            ss >> vertex0 >> vertexf >> weight;
						InsertArista(vertex0,vertexf,weight);
            //cout << vertex0 << " " << vertexf << " " << weight <<"\n";
			     }

			     read.close();
			  };
};

typedef Graph<Traits> graph;

#endif
