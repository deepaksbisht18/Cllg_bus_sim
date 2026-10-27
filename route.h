#ifndef ROUTE_H
#define ROUTE_H
#include "stop.h"
struct routeNode{
    Stop *stop;
    routeNode *next;
};
class route{
    private:
    routeNode *head;
    routeNode *tail;
    int count;
    public:
    route();
    ~route();
    void addstop(Stop *s);
    routeNode* gethead();
    int size();
    void reverse();
    void display();
};
#endif 
