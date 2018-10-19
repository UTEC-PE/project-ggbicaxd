#ifndef STACK_H
#define STACK_H

#include <iostream>
#include "nodeestruc.h"

//first in last out
using namespace std;

template <typename T>
class Stack {
private:
    Nodeestruc<T>* head;
    Nodeestruc<T>* tail;
    int nodes;

public:
    Stack(){
        head= nullptr;
        tail= nullptr;
        nodes=0;
    };
    T get(){
        if(!head){
            cout<<"vacia";
        } else{
            return head->data;
        }
    };
    void push(T value){//front
        auto* temp= new Nodeestruc<T>{value, nullptr};
        if (head==nullptr) {
            head=temp;
            tail=temp;
        }else{
            temp->next=head;
            head=temp;
        }
        nodes++;
    };
    void pop(){//front
        auto* temp=head;
        /*if(!head)
            throw "Lista vacia";*/
        if(nodes==1)
            head=tail=nullptr;
        else{
            head=temp->next;
        }
        delete temp;
        nodes--;
    };
    T get(int position){
        if(!head){
            throw "Vacio";
        }
        auto* temp=head;
        for (int i = 1; i < position; i++) {
            temp=temp->next;
        }
        return temp->data;
    };
    void print(){
        Nodeestruc<T>* actual=head;
        if(!head){
          cout<<"stack vacio"<<endl;
        }
        else{
          while(actual!=tail){
              cout<<actual->data->getdata()<<" ";
              actual=actual->next;
          }
          cout<<tail->data->getdata()<<endl;
        }    
    };
    bool empty(){
        return head == nullptr;
    };
    int size(){
        return nodes;
    };
    void clear(){
        head=nullptr;
        tail=nullptr;
        nodes=0;
    };
    ~Stack(){
        if(head){
            head->killSelf();
        }
        //delete  head;
        //delete  tail;
    };
};
#endif
