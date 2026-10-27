#include "bus.h"
#include <string>
#include <iostream>

bus::bus(int cap){
    capacity = cap;
    load = 0;
    current = NULL;
    state = "Idle";
}

int bus::seatsLeft(){
    return capacity - load;
}

bool bus::isFull(){
    return load >= capacity;
}

int bus::getLoad(){
    return load;
}

int bus::boardFrom(Stop* s){
    int boarded = s->boardStudent(seatsLeft());
    load += boarded;
    return boarded;
}

void bus::dropStudents(int n){
    if(n <= 0){
        return;
    }
    else if(n >= load){
        n = load;
    }
    load -= n;
}

void bus::setPosition(routeNode* node){
    current = node;
}

routeNode* bus::getPosition(){
    return current;
}

bool bus::moveNext(){
    if(current == NULL || current->next == NULL){
        return false;
    }
    current = current->next;
    return true;
}

void bus::setState(std::string st){
    state = st;
}

std::string bus::getState(){
    return state;
}

void bus::display(){
    std::cout << "Bus state: " << state << " | Load: " << load
              << "/" << capacity << " | Position: ";
    if(current != NULL){
        std::cout << current->stop->get_name();
    }
    else{
        std::cout << "not set";
    }
    std::cout << std::endl;
}