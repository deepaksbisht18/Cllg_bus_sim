#ifndef BUS_H
#define BUS_H
#include "stop.h"
#include "route.h"
#include<string>
class bus{
    private:
    int capacity;
    int load;
    routeNode* current;
    std::string state;
    public:
    bus(int cap);
    int seatsLeft();
    bool isFull();
    int getLoad();
    int boardFrom(Stop *s);
    void dropStudents(int n);
    void setPosition(routeNode* node);
    routeNode* getPosition();
    bool moveNext();
    void setState(std::string st);
    std::string getState();
    void display();

};
#endif