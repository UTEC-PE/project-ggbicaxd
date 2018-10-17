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
			int aristas;
			int nodos;
				Graph(bool dir):dir(dir){
					nodos=0;
					aristas=0;
				};

				~Graph(){
					for(int i=0; i<nodes.size();i++){
						for(auto& item: nodes[i]->edges){
							delete item;
						}
						delete nodes[i];
					}
				}
				void insertarnodo(int nombre,float x, float y){
				 node* temp=buscarnodo(nombre);
				 if(!temp){
					 node* nodo=new node(nombre,x,y);
					 nodes.push_back(nodo);
					 nodos++;
				 }
				 else{
					cout<<"nodo existente"<<endl;
				 }
				};

				void InsertArista(N nodo1, N nodo2,E peso){
					node* temp= buscarnodo(nodo1);
					node* temp2= buscarnodo(nodo2);
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
						temp->setgradosalida(0);
						temp->setgradollegada(0);
						temp2->edges.push_back(arista);
						temp2->setgradosalida(0);
						temp2->setgradollegada(0);
						aristas++;
					}
					else{
						for ( auto& item : temp->edges )
						{
							if(item->nodes[1]->getdata()==nodo2){
								throw "arista ya existente";
							}
						}
						edge* arista=new edge(temp,temp2,peso, dir);
						temp->edges.push_back(arista);
						temp->setgradosalida(0);
						temp2->setgradollegada(0);
						aristas++;
					}

				};

				void removerNodo(N x){
					for(int i=0;i<nodes.size();i++){
						if(nodes[i]->getdata()==x){
							ei=nodes[i]->edges.begin();
							while(ei!=nodes[i]->edges.end()){
								EdgeIte j=ei;

								removerAristaptr(*j);
								ei=nodes[i]->edges.begin();
							}
							node* temp= nodes[i];
							ni=nodes.begin();
							nodes.erase(ni+i);
							nodos--;
							break;
						}
					}
					if(dir==1){
						for(int i=0;i<nodes.size();i++){
							ei=nodes[i]->edges.begin();
							while(ei!=nodes[i]->edges.end()){
								if((*ei)->nodes[1]->getdata()==x){
									EdgeIte j=ei;
									removerAristaptr(*j);
									break;
								}
								ei++;
							}
						}
					}
				}

				void removerAristaptr(edge* ptrarista){//remueve la arista a partir de un puntero a arista
					int size=nodes.size();
					for(int i=0;i<size;i++){
						ei=nodes[i]->edges.begin();
						while(ei!=nodes[i]->edges.end()){
							if(*ei==ptrarista){
								EdgeIte j=ei;
								ei++;
								nodes[i]->edges.erase(j);
							}else{
								ei++;
							}
						}
					}
					if(dir==0){
						ptrarista->nodes[0]->setgradosalida(1);
						ptrarista->nodes[0]->setgradollegada(1);
						ptrarista->nodes[1]->setgradosalida(1);
						ptrarista->nodes[1]->setgradollegada(1);
					}else{
						ptrarista->nodes[0]->setgradosalida(1);
						ptrarista->nodes[1]->setgradollegada(1);
					}
					delete ptrarista;
					aristas--;
				}
				void removerArista(N x, N y){//remueve la arista a partir del nodo de salida al nodo de llegada
					edge *ptrarista=buscararista(x,y);
					removerAristaptr(ptrarista);
				}

				int getGradoNodo(N data){// devuelve el grado del nodo
					node* temp= buscarnodo(data);
					if(!temp)
						throw "no existe el nodo";
					else if(dir==0)
						return temp->gradosalida();
					else
						return temp->gradosalida()+temp->gradollegada();
				}
					//node* temp2=buscarnodo(y);
				int getGradoNodoS(N data){//devuelve el grado de salida de un nodo, en caso sea no dirigido los grados de salida y de llegada son iguales entre si e iguales al grado total
					node* temp= nullptr;
					for(int i=0; i<nodes.size(); i++){
						if(data==nodes[i]->getdata())
							temp=nodes[i];
					}
					if(!temp)
						throw "no existe el nodo";
					else
						return temp->gradosalida();
				}
				int getGradoNodoLL(N data){//devuelve el grado de llegada de un nodo, en caso sea no dirigido los grados de salida y de llegada son iguales entre si e iguales al grado total
					node* temp= nullptr;
					for(int i=0; i<nodes.size(); i++){
						if(data==nodes[i]->getdata())
							temp=nodes[i];
					}
					if(!temp)
						throw "no existe el nodo";
					else
						return temp->gradollegada();
				}

				void print() {
					for (int i = 0; i < nodes.size(); i++) {
						cout<<nodes[i]->getdata()<<" -> ";
						for ( auto& item : nodes[i]->edges )
						{
							if(item->nodes[0]->getdata()==nodes[i]->getdata())
								cout<<item->nodes[1]->getdata()<<" ";
							else
								cout<<item->nodes[0]->getdata()<<" ";
						}
						cout<<endl;
					}
				};

				node* buscarnodo(N data){
					node* temp=nullptr;
					for(int i=0; i<nodes.size(); i++){
						if(data==nodes[i]->getdata()){
							temp=nodes[i];
							break;
						}
					}
					return temp;
				}

				edge* buscararista(N x, N y){
					node* temp=buscarnodo(x);
					edge* ptrarista=nullptr;
					for (auto& item: temp->edges){
						if(dir==0 && (item->nodes[0]->getdata()==y || item->nodes[1]->getdata()==y)){
							ptrarista=item;
							break;
						}
						else if(dir==1 && item->nodes[1]->getdata()==y){
							ptrarista=item;
							break;
						}
					}
					return ptrarista;
				}

                float getDensity()
                {
                    float densidad;
                    if(dir==0)
                        densidad = (2*arista)/((nodos)*(nodos-1));
                    else
                        densidad = arista/((nodos)-(nodos-1));
                    return densidad;
                }

			  void read_file(string file)
			  {
					ifstream read(file);
          string lines;
	        float x;
			    float y;

			    getline(read,lines);
			    int new_node = stoi (lines);
			    for(int i = 0; i<new_node; i++)
			    {
						//insert_nodo
	          getline(read, lines);
			      stringstream ss(lines);
			      ss >> x >> y;
						insertarnodo(i,x,y);
			     }

			     getline(read, lines);
			     int vertex0, vertexf;
			     E weight;

			     while(getline(read,lines))
			     {
			      stringstream ss(lines);
            ss >> vertex0 >> vertexf >> weight;
						InsertArista(vertex0,vertexf,weight);
			     }

			     read.close();
			  };
};

typedef Graph<Traits> graph;

#endif
