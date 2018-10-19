#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>
#include "queue.h"
#include "stack.h"

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
				bool conexo;
				bool bipartito;


		public:
			int aristas;
			int nodos;
				Graph(bool dir):dir(dir){
					nodos=0;
					aristas=0;
					conexo=false;
					bipartito=true;
				};

				~Graph(){
					for(int i=0; i<nodes.size();i++){
						for(auto& item: nodes[i]->edges){
							delete item;
						}
						delete nodes[i];
					}
				}

				void fuertemente(node* nodo){
					/*map<node*, bool> map;      //Hallar el orden de cierre
					Stack<node*> sta;
					for(int i=0; i<nodes.size();i++){
						map.insert(pair<node*, bool> (nodes[i],false));
					}
					NodeSeq nuevos;
					map[nodo]=true;
					auto temp=nodo;
					sta.push(nodo);
					while(!sta.empty()){
						nodo=sta.get();
						//nodo=temp;
						for(auto& item:nodo->edges){
							if(map[item->nodes[1]]==false){
								nodo=item->nodes[1];
								sta.push(nodo);
								break;
							}
						}
						if(nodo==temp){
							nuevos.push_back(nodo);
							sta.pop();
						}
						else{
							map[nodo]=true;
						}
						temp=nodo;
					}
					for(int i=0; i<nuevos.size();i++){
						cout<<nuevos[i]->getdata()<<" ";
					}
					cout<<endl;*/
					float xy=1.0;
					Graph<Tr> traspuesto(1);
					for(int i=0;i<nodes.size();i++){
						traspuesto.insertarnodo(nodes[i]->getdata(),xy,xy);
					}
					node* temp=nullptr;
					for(int i=0; i<nodes.size();i++){
						for(auto& item:nodes[i]->edges){
							traspuesto.InsertArista(item->nodes[1]->getdata(),item->nodes[0]->getdata(), item->getdata());
						}
					}
					//traspuesto.print();

					dfs(nodo);
					nodo=traspuesto.buscarnodo(nodo->getdata());
					traspuesto.dfs(nodo);
					if(conexo && traspuesto.isconexo()){
						conexo=true;
						cout<<"fuertemente conexo"<<endl;
					}
					else{
						conexo=false;
						cout<<"no es fuertemente conexo"<<endl;
					}
				}

				void dfs(node* nodo){
					cout<<"DFS"<<endl;
					map<node*, bool> map;
					Stack<edge*> sta;
					int xnodos=1;
					for(int i=0; i<nodes.size();i++){
						map.insert(pair<node*, bool> (nodes[i],false));
					}
					for(auto& item:nodo->edges){
						edge* arista =item;
						sta.push(arista);
					}
					map[nodo]=true;
					cout<<nodo->getdata()<<" ";
					while(!sta.empty()){
						edge* arista=sta.get();
						if(arista->nodes[0]!=nodo && map[arista->nodes[0]]==false){
							nodo=arista->nodes[0];
							map[nodo]=true;
							cout<<nodo->getdata()<<" ";
							xnodos++;
							for(auto& item:nodo->edges){
								edge* arist =item;
								sta.push(arist);
							}
						}
						else if(arista->nodes[1]!=nodo && map[arista->nodes[1]]==false){
							nodo=arista->nodes[1];
							map[nodo]=true;
							cout<< nodo->getdata()<<" ";
							xnodos++;
							for(auto& item:nodo->edges){
								edge* arist =item;
								sta.push(arist);
							}
						}
						else{
							sta.pop();
						}
					}
					if(xnodos==nodos){
						conexo=true;
					}
					cout<<endl;

				}

				void bfs(node* nodo){
					cout<<"BFS"<<endl;
					int xnodos=1;
					map<node*, bool> map;
					Queue<edge*> que;
					for(int i=0; i<nodes.size();i++){
						map.insert(pair<node*, bool> (nodes[i],false));
					}
					for(auto& item:nodo->edges){
						edge* arista =item;
						que.push(arista);
					}
					map[nodo]=true;
					cout<<nodo->getdata()<<" ";
					while(!que.empty()){
						edge* arista=que.get();
						if(arista->nodes[0]!=nodo && map[arista->nodes[0]]==false){
							nodo=arista->nodes[0];
							map[nodo]=true;
							cout<<nodo->getdata()<<" ";
							xnodos++;
							for(auto& item:nodo->edges){
								edge* arist =item;
								que.push(arist);
							}
						}
						else if(arista->nodes[1]!=nodo && map[arista->nodes[1]]==false){
							nodo=arista->nodes[1];
							map[nodo]=true;
							cout<< nodo->getdata()<<" ";
							xnodos++;

							for(auto& item:nodo->edges){
								edge* arist =item;
								que.push(arist);
							}
						}
						que.pop();
					}
					if(xnodos==nodos){
						conexo=true;
					}
					else{
						conexo=false;
					}
					cout<<endl;
				}

				bool isbipartito(){//0 sin color, 1 negro, 2 rojo
					auto nodo=buscarnodo(0);
					cout<<endl;
					map<node* , int> colores;
					map<node*, bool> map;
					bool turno=false;
					Queue<edge*> que;
					for(int i=0; i<nodes.size();i++){
						map.insert(pair<node*, bool> (nodes[i],false));
						colores.insert(pair<node*, int> (nodes[i],0));
					}
					for(auto& item:nodo->edges){
						edge* arista =item;
						que.push(arista);
					}
					map[nodo]=true;
					colores[nodo]=1;
					while(!que.empty()){
						edge* arista=que.get();
						if(arista->nodes[0]!=nodo && map[arista->nodes[0]]==false){
							nodo=arista->nodes[0];
							map[nodo]=true;
							if(!turno){
								colores[nodo]=2;
							}
							else if(turno){
								colores[nodo]=1;
							}
							for(auto& item:nodo->edges){
								edge* arist =item;
								que.push(arist);
							}
						}
						else if(arista->nodes[1]!=nodo && map[arista->nodes[1]]==false){
							nodo=arista->nodes[1];
							map[nodo]=true;
							if(!turno){
								colores[nodo]=2;
							}
							else if(turno){
								colores[nodo]=1;
							}
							for(auto& item:nodo->edges){
								edge* arist =item;
								que.push(arist);
							}
						}
						if(colores[arista->nodes[1]]== colores[arista->nodes[0]] ){
							bipartito=false;
							break;
						}
						turno=!turno;
						que.pop();
					}
					if(bipartito){
						cout<<"es bipartito"<<endl;
					}
					else{
						cout<<"no es bipartito"<<endl;
					}
					return bipartito;
				}

				void prim(node* nodo){
					cout<<"Prim"<<endl;
					if(dir==1){
						cout<<"grafo dirigido, no hay prim"<<endl;
						return;
					}
					multimap<E, edge*> aristmap;
					map<node*,bool> map;
					for(int i=0; i<nodes.size();i++){
						map.insert(pair<node*, bool> (nodes[i],false));
					}
					for(auto item: nodo->edges){
						aristmap.insert(pair<E,edge*> (item->getdata(), item));
					}
					map[nodo]=true;
					//cout<<nodo->getdata()<<" ";
					auto ite=aristmap.begin();
					while(ite!=aristmap.end()){
						if(ite->second->nodes[0]!=nodo && map[ite->second->nodes[0]]==false){
							cout<<"{"<<ite->second->nodes[1]->getdata()<<","<<ite->second->nodes[0]->getdata()<<","<<ite->first <<"}"<<" ";
							nodo=ite->second->nodes[0];
							map[nodo]=true;
							aristmap.erase(ite);
							for(auto& item:nodo->edges){
								aristmap.insert(pair<E,edge*> (item->getdata(), item));
							}
							ite=aristmap.begin();
						}
						else if(ite->second->nodes[1]!=nodo && map[ite->second->nodes[1]]==false){
							cout<<"{"<<ite->second->nodes[0]->getdata()<<","<<ite->second->nodes[1]->getdata()<<","<<ite->first <<"}"<<" ";
							nodo=ite->second->nodes[1];
							map[nodo]=true;
							aristmap.erase(ite);
							for(auto& item:nodo->edges){
								aristmap.insert(pair<E,edge*> (item->getdata(), item));
							}
							ite=aristmap.begin();
						}
						else{
							aristmap.erase(ite);
							ite=aristmap.begin();
						}
					}
					cout<<endl;
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
								cout<<"arista existente"<<endl;
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
								cout<<"arista ya existente"<<endl;
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
				void comprobar_conectividad(node* nodo){
					if(dir==0){
						dfs(nodo);
						if(conexo)
							cout<<"conexo"<<endl;
						else
							cout<<"no conexo"<<endl;
					}else{
						fuertemente(nodo);
					}
				}
				bool isconexo(){
					return conexo;
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
            densidad = (2*(float)aristas)/(((float)nodos)*((float)nodos-1));
          else
            densidad = (float)aristas/(((float)nodos)-((float)nodos-1));
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
