//#include <GL/glut.h>
#include <iostream>
#include <thread>
#include <mutex>
#include "graph.h"

#define NUM_THREADS 6
mutex mute;

vector<list<Edge<Graph<Traits>>*>> resultados;

void aesteriscothreads(Graph<Traits> *mygraph, int n, int l){
  auto asterisco=mygraph->A_asterisco(n,l);
  resultados.push_back(asterisco);
}
using namespace std;

int main(int argc, char *argv[]) {
    Graph<Traits> mygraph(1);
    Graph<Traits>* grafos=&mygraph;
    mygraph.read_file("texto8.txt");
    mygraph.print();
    cout<<"A*"<<endl;
    auto asterisco=mygraph.A_asterisco(0,4);
    for(auto item: asterisco){
      cout<<"("<<item->nodes[0]->getdata()<<","<<item->nodes[1]->getdata()<<")"<<" ";
    }
    cout<<endl;
    cout<<"A* por threads"<<endl;

    thread threads[NUM_THREADS];
    threads[0]=thread(aesteriscothreads,grafos,0,3);
    threads[1]=thread(aesteriscothreads,grafos,0,1);
    threads[2]=thread(aesteriscothreads,grafos,0,2);
    threads[3]=thread(aesteriscothreads,grafos,1,4);
    threads[4]=thread(aesteriscothreads,grafos,8,2);
    threads[5]=thread(aesteriscothreads,grafos,8,4);
    for(int i = 0; i < NUM_THREADS;i++){
      threads[i].join();
    }
    for(int j=0;j<resultados.size();j++){
      for(auto item: resultados[j]){
        cout<<"("<<item->nodes[0]->getdata()<<","<<item->nodes[1]->getdata()<<")"<<" ";
      }
      cout<<endl;
    }
    cout<<"Bellman Ford"<<endl;
    mygraph.bellmanFord(0);

    mygraph.greedybfs(0,1);
    cout<<"FLoyd Warshall"<<endl;
    auto floyd=mygraph.floydwarshall();
    floyd->print();

    cout<<"Dijkstra"<<endl;
    auto dijsktra=mygraph.dijkstra(0);
    for(auto item: dijsktra){
      cout<<item.first->getdata()<<" : "<<item.second->peso<<" -> ";
      item.second->print();
      cout<<endl;
    }


    return EXIT_SUCCESS;
}
