#include "graph.h"
#include "queue.h"
#include <iostream>
graph::graph(){
    for(int i=0;i<50;i++){
        stops[i]=NULL;
        adj[i]=NULL;
    }
}
graph::~graph(){
    for(int i=0;i<50;i++){
        edge* cur=adj[i];
        while(cur!=NULL){
            edge* temp=cur->next;
            delete cur;
            cur=temp;
        }
    }
}
void graph::addstop(Stop* s){
    int id=s->get_id();
    if(id>=0 && id<50){
        stops[id]=s;
    }
}
void graph::addedge(int a,int b){
    if(a<0 || a>=50 || b<0 || b>=50 || stops[a]==NULL || stops[b]==NULL){
        return;
    }
    edge* e1=new edge;
    e1->to=b;
    e1->next=adj[a];
    adj[a]=e1;
    edge* e2=new edge;
    e2->to=a;
    e2->next=adj[b];
    adj[b]=e2;
}
bool graph::findpath(int from,int to,int path[],int& len){
    len=0;
    if(from<0 || from>=50 || to<0 || to>=50 || stops[from]==NULL || stops[to]==NULL){
        return false;
    }
    bool vis[50];
    int par[50];
    for(int i=0;i<50;i++){
        vis[i]=false;
        par[i]=-1;
    }
    Queue q;
    q.enqueue(stops[from]);
    vis[from]=true;
    QueueData cur;
    bool found=false;
    while(q.dequeue(cur)){
        int u=cur->get_id();
        if(u==to){
            found=true;
            break;
        }
        edge* e=adj[u];
        while(e!=NULL){
            if(!vis[e->to]){
                vis[e->to]=true;
                par[e->to]=u;
                q.enqueue(stops[e->to]);
            }
            e=e->next;
        }
    }
    if(!found){
        return false;
    }
    int temp[50];
    int n=0;
    int x=to;
    while(x!=-1){
        temp[n]=x;
        n++;
        x=par[x];
    }
    for(int i=0;i<n;i++){
        path[i]=temp[n-1-i];
    }
    len=n;
    return true;
}
void graph::display(){
    for(int i=0;i<50;i++){
        if(stops[i]!=NULL){
            std::cout<<stops[i]->get_name()<<": ";
            edge* e=adj[i];
            while(e!=NULL){
                std::cout<<stops[e->to]->get_name();
                if(e->next!=NULL){
                    std::cout<<", ";
                }
                e=e->next;
            }
            std::cout<<std::endl;
        }
    }
}