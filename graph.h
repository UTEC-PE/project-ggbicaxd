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
#include <limits.h>
#include <math.h>
#include "queue.h"
#include "stack.h"

#include "node.h"
#include "edge.h"
#include "camino.h"
#include "Matrix.h"

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
				typedef Matrix<self> Matris;
				typedef Camino<self> camino;
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
				double heuristica(node* nodo, node* nodo2){
						return sqrt(pow((nodo2->getx()-nodo->getx()),2)+pow((nodo2->gety()-nodo->gety()),2));
				}

				node* minheuristic(map<node*,bool> mapa, map<node*, double> posiblesNodos, map<node*,double> heuristicas){
					node* indice=nullptr;
					double min=std::numeric_limits<double>::max();
					for(auto item: posiblesNodos){
						if(mapa[item.first]==false && posiblesNodos[item.first]!=std::numeric_limits<double>::max() && posiblesNodos[item.first]+heuristicas[item.first]<=min){
							min=posiblesNodos[item.first]+heuristicas[item.first];
							indice=item.first;
						}
					}
					return indice;
				}

				vector<double> heuristicfalsa(){
					vector<double> falsas;
					falsas.push_back(36);
					falsas.push_back(39);
					falsas.push_back(31);
					falsas.push_back(30);
					falsas.push_back(34);
					falsas.push_back(32);
					falsas.push_back(21);
					falsas.push_back(19);
					falsas.push_back(0);
					return falsas;
				}

				EdgeSeq A_asterisco(N data, N llegada){

					EdgeSeq respuesta;
					auto nodo=buscarnodo(data);
					auto final=buscarnodo(llegada);
					if(!nodo || !final){
						cout<<"nodos inexistentes"<<endl;
						throw ;
					}
					map<node*, double> heuristicas;
					//vector<double> falsas=heuristicfalsa();
					map<node*, double> posiblesNodos;
					map<node*,node*> predecesor;
					map<node*,bool> map;

					double Max=std::numeric_limits<double>::max();
					double heuristic;
					for(int i=0;i<nodes.size();i++){
						heuristic=heuristica(nodes[i],final);
						heuristicas.insert(pair<node*,double> (nodes[i],/*falsas[i]*/heuristic));
						map.insert(pair<node*,bool> (nodes[i],false));
						predecesor.insert(pair<node*,node*> (nodes[i],nullptr));
						posiblesNodos.insert(pair<node*,double> (nodes[i],Max));
					}
					predecesor[nodo]=nodo;
					posiblesNodos[nodo]=heuristicas[nodo];

					do{
						nodo=minheuristic(map,posiblesNodos,heuristicas);
						if(!nodo){
							break;
						}
						map[nodo]=true;
						for(auto item:nodo->edges){
							if(item->nodes[0]!=nodo && posiblesNodos[nodo]+item->getdata()<posiblesNodos[item->nodes[0]]){
								posiblesNodos[item->nodes[0]]=posiblesNodos[nodo]+item->getdata();
								predecesor[item->nodes[0]]=nodo;
								if(item->nodes[0]->getdata()==llegada){
									nodo=item->nodes[0];
									break;
								}
							}
							else if(item->nodes[1]!=nodo && posiblesNodos[nodo]+item->getdata()<posiblesNodos[item->nodes[1]]){
								posiblesNodos[item->nodes[1]]=posiblesNodos[nodo]+item->getdata();
								predecesor[item->nodes[1]]=nodo;
								if(item->nodes[1]->getdata()==llegada){
									nodo=item->nodes[1];
									break;
								}
							}
						}
					}
					while(nodo!=nullptr && nodo->getdata()!=llegada);
					edge* arista;
					edge* nuevaarista;
					if(nodo ){
						while(predecesor[nodo]!=nodo){
							arista=buscararista(predecesor[nodo]->getdata(),nodo->getdata());
							nuevaarista=new edge(predecesor[nodo],nodo,arista->getdata(),1);
							respuesta.push_front(nuevaarista);
							nodo=predecesor[nodo];
						}
					}
					else{
						cout<<"No existe camino de "<<data<<" a "<<llegada<<endl;
					}

					/*for(auto item: respuesta){
						cout<<"("<<item->nodes[0]->getdata()<<","<<item->nodes[1]->getdata()<<")"<<" ";
					}
					cout<<endl;*/
					return respuesta;
				}

				int indiceMin(map<node*,int> caminos, map<node*,bool> map){
					int indice=-1;
					int min=INT_MAX;
					for(int i=0; i<nodes.size();i++){
						if(map[nodes[i]]==false && caminos[nodes[i]]<=min){
							min=caminos[nodes[i]];
							indice=i;
						}
					}
					if(min==INT_MAX){
						return -1;
					}
					return indice;
				}

				map<node*,camino*> dijkstra(N data){
					auto nodo=buscarnodo(data);
					map<node*,camino*> walks;
					camino* walk;
					map<node*,int> caminos;
					map<node*,bool> map;
					for(int i=0; i<nodes.size();i++){
						map.insert(pair<node*, bool> (nodes[i],false));
						caminos.insert(pair<node*,int> (nodes[i],INT_MAX));
						walk=new camino(nodo,INT_MAX);
						walks.insert(pair<node*,camino*> (nodes[i],walk));
					}
					walks[nodo]->peso=0;
					caminos[nodo]=0;
					map[nodo]=true;
					int minimo=(int)data;
					do{
						nodo=nodes[minimo];
						map[nodo]=true;
						for(auto item:nodo->edges){
							if(item->nodes[0]!=nodo && item->getdata()+caminos[nodo]<caminos[item->nodes[0]]){
								caminos[item->nodes[0]]=item->getdata()+caminos[nodo];
								walks[item->nodes[0]]->peso=item->getdata()+caminos[nodo];
								walks[item->nodes[0]]->nodos=walks[nodo]->nodos;
								walks[item->nodes[0]]->nodos.push_back(item);
							}
							else if(item->nodes[1]!=nodo && item->getdata()+caminos[nodo]<caminos[item->nodes[1]]){
								caminos[item->nodes[1]]=item->getdata()+caminos[nodo];
								walks[item->nodes[1]]->peso=item->getdata()+caminos[nodo];
								walks[item->nodes[1]]->nodos=walks[nodo]->nodos;
								walks[item->nodes[1]]->nodos.push_back(item);
							}
						}
						minimo=indiceMin(caminos,map);
					}
					while(minimo!=-1);
					return walks;
				}



				Matris* floydwarshall(){
					//int matriz1[nodos][nodos];
					//int matriz2[nodos][nodos];
					Matris* matrix=new Matris(nodos);
					for(int i=0;i<nodos;i++){
						for(int j=0;j<nodos;j++){
							if(i==j){
								matrix->matriz1[i][j]=0;
								matrix->matriz2[i][j]=0;
							}
							else{
								matrix->matriz1[i][j]=INT_MAX;
								matrix->matriz2[i][j]=j;
							}
						}
					}

					for(int k=0;k<nodes.size();k++){
						for(auto item:nodes[k]->edges){
							if(nodes[k]!=item->nodes[0])
							matrix->matriz1[item->nodes[1]->getdata()][item->nodes[0]->getdata()]=item->getdata();
							else if(nodes[k]!=item->nodes[1])
							matrix->matriz1[item->nodes[0]->getdata()][item->nodes[1]->getdata()]=item->getdata();
						}
					}
					for(int x=0;x<nodes.size();x++){
						for(int y=0;y<nodes.size();y++){
							if(x!=y){
								for(int z=0;z<nodes.size();z++){
									if(x!=z && matrix->matriz1[y][x]!=INT_MAX && matrix->matriz1[x][z]!=INT_MAX && matrix->matriz1[y][x]+matrix->matriz1[x][z]<matrix->matriz1[y][z]){
										matrix->matriz1[y][z]=matrix->matriz1[y][x]+matrix->matriz1[x][z];
										matrix->matriz2[y][z]=x;
									}
								}
							}
						}
					}
					return matrix;
				}

				void fuertemente(node* nodo){//Comprueba la conectividad, se llama desde comprobar_conectividad
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

				EdgeSeq dfs(node* nodo){//Busqueda en profundidad, comprueba conectividad en caso dirigido cuando es llamado por comprobar_conectividad
					EdgeSeq respuesta;
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
							respuesta.push_back(arista);
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
							respuesta.push_back(arista);
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
					return respuesta;
				}

				EdgeSeq bfs(node* nodo){//Busqueda en amplitud, ademas comprueba conectividad
					EdgeSeq respuesta;
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
							respuesta.push_back(arista);
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
							respuesta.push_back(arista);
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
					return respuesta;
				}

				bool isbipartito(){//0 sin color, 1 negro, 2 rojo, turno = en false es turno de negros se pintan los nodos de rojo, en true turno de rojos se pintan los nodos de negros
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

				EdgeSeq kruskal()// Kruskal con disjoint sets
        {
					EdgeSeq respuesta;
          cout << "Kruskal: " << endl;
          if(dir==1){
            cout << "Es grafo dirigido, no puede implementarse kruskal."<< endl;
            return respuesta;
          }

          multimap<E, edge*> aristamap;
          for (int i = 0; i < nodes.size(); i++)
          {
            for (auto item: nodes[i]->edges)
            {
              aristamap.insert(pair<E, edge*>(item->getdata(), item));
            }
          }
          auto ite = aristamap.begin();
					ite->second->nodes[0]->setpadre(ite->second->nodes[0]);
          while(ite != aristamap.end()){
						if(!ite->second->nodes[0]->buscarpadre() && !ite->second->nodes[1]->buscarpadre()){
							ite->second->nodes[0]->setpadre(ite->second->nodes[0]);
							ite->second->nodes[1]->setpadre(ite->second->nodes[0]);
							respuesta.push_back(ite->second);
							cout<<"{"<<ite->second->nodes[0]->getdata()<<","<<ite->second->nodes[1]->getdata()<<","<<ite->first <<"}"<<" ";
							aristamap.erase(ite);
          		ite = aristamap.begin();
						}
						else if(ite->second->nodes[0]->buscarpadre()==ite->second->nodes[1]->buscarpadre()){
							aristamap.erase(ite);
							ite = aristamap.begin();
						}
						else if(ite->second->nodes[0]->buscarpadre()!=ite->second->nodes[1]->buscarpadre()){
							if(ite->second->nodes[0]->buscarpadre() && ite->second->nodes[1]->buscarpadre()){
								ite->second->nodes[1]->setpadre(ite->second->nodes[0]->buscarpadre());
								respuesta.push_back(ite->second);
								cout<<"{"<<ite->second->nodes[0]->getdata()<<","<<ite->second->nodes[1]->getdata()<<","<<ite->first <<"}"<<" ";
							}
							else if(!ite->second->nodes[0]->buscarpadre()){
								ite->second->nodes[0]->setpadre(ite->second->nodes[1]->buscarpadre());
								respuesta.push_back(ite->second);
								cout<<"{"<<ite->second->nodes[0]->getdata()<<","<<ite->second->nodes[1]->getdata()<<","<<ite->first <<"}"<<" ";
							}
							else if(!ite->second->nodes[1]->buscarpadre()){
								ite->second->nodes[1]->setpadre(ite->second->nodes[0]->buscarpadre());
								respuesta.push_back(ite->second);
								cout<<"{"<<ite->second->nodes[0]->getdata()<<","<<ite->second->nodes[1]->getdata()<<","<<ite->first <<"}"<<" ";
							}
							aristamap.erase(ite);
							ite = aristamap.begin();
						}
          }
          cout<<endl;
					return respuesta;
        }

				EdgeSeq prim(node* nodo){// prim con mutimap
					EdgeSeq respuesta;
					cout<<"Prim"<<endl;
					if(dir==1){
						cout<<"grafo dirigido, no hay prim"<<endl;
						return respuesta;
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
					auto ite=aristmap.begin();
					while(ite!=aristmap.end()){
						if(ite->second->nodes[0]!=nodo && map[ite->second->nodes[0]]==false){
							respuesta.push_back(ite->second);
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
							respuesta.push_back(ite->second);
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
					return respuesta;
				}

				void insertarnodo(int nombre,float x, float y){//Inserta un Nodo si existe
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

				void InsertArista(N nodo1, N nodo2,E peso){ // Inserta la arista si no existe, si es no dirigido la misma arista se inserta en ambas listas de adyacencias
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

				void removerNodo(N x){ // Remueve un nodo si existe
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
				void comprobar_conectividad(node* nodo){//Comprueba la conectividad del grafo llamando a las diferentes funciones dependiendo si es dirigido y no dirigido
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
				bool isconexo(){//Devuelve booleano si es conexo
					return conexo;
				}

				void print() {// Print del grafo
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

				node* buscarnodo(N data){//  buscar un nodo a partir de la data
					node* temp=nullptr;
					for(int i=0; i<nodes.size(); i++){
						if(data==nodes[i]->getdata()){
							temp=nodes[i];
							break;
						}
					}
					return temp;
				}

				edge* buscararista(N x, N y){//busca  una arista a partir de 2 nodos, comprueba si es dirigido o no
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

			  void tiponodos(){ //Output de tipos de nodos
					if(dir==0){
						for(int i=0; nodes.size();i++){
							cout<<nodes[i]->getdata()<<" normal"<<endl;
						}
					}
					else{
						for(int i=0; nodes.size();i++){
							cout<<nodes[i]->getdata()<<" ";
							if(nodes[i]->gradosalida()==0){
								cout<<"hundido"<<" ";
							}
							if(nodes[i]->gradollegada()==0){
								cout<<"fuente"<<" ";
							}
							cout<<endl;
						}
					}
				}

				float getDensity(float cotadensidad)// devuelve densidad
        {
          //float cotadensidad = 0.6;
          float densidad;
          if(dir==0){
            densidad = (2*(float)aristas)/(((float)nodos)*((float)nodos-1));
            if(densidad > cotadensidad)
              cout << "El grafo no dirigido es denso: ";
            else
              cout << "El grafo no dirigido es disperso: ";
          }
          else{
            densidad = (float)aristas/(((float)nodos)-((float)nodos-1));
            if(densidad > cotadensidad)
              cout << "El grafo dirigido es denso: ";
            else
              cout << "El grafo dirigido es disperso: ";
            }
						cout<<endl;
           return densidad;
          }

			  void read_file(string file)// Lee el archivo  y crea el grafo
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
