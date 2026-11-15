#ifndef GRAPH_H
#define GRAPH_H
#include "stop.h"
struct edge{
    int to;
    edge* next;
};
class graph{
    private:
    Stop* stops[50];
    edge* adj[50];
    public:
    graph();
    ~graph();
    void addstop(Stop* s);
    void addedge(int a,int b);
    bool findpath(int from,int to,int path[],int& len);
    void display();
};
#endif