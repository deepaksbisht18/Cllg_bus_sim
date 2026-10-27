#include "route.h"
#include <iostream>

route::route(){
    head = NULL;
    tail = NULL;
    count = 0;
}

void route::addstop(Stop *s){
    routeNode* nn = new routeNode;
    nn->stop = s;
    nn->next = NULL;
    if(head == NULL){
        head = nn;
        tail = nn;
    }
    else{
        tail->next = nn;
        tail = nn;
    }
    count++;
}

routeNode* route::gethead(){
    return head;
}

int route::size(){
    return count;
}

void route::display(){
    if(head == NULL){
        std::cout << "Route is empty" << std::endl;
        return;
    }
    routeNode* cur = head;
    while(cur != NULL){
        std::cout << cur->stop->get_name();
        if(cur->next != NULL){
            std::cout << " -> ";
        }
        cur = cur->next;
    }
    std::cout << std::endl;
}

void route::reverse(){
    routeNode* prev = NULL;
    routeNode* cur = head;
    routeNode* next = NULL;
    tail = head;
    while(cur != NULL){
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    head = prev;
}

route::~route(){
    routeNode* cur = head;
    while(cur != NULL){
        routeNode* next = cur->next;
        delete cur;
        cur = next;
    }
}