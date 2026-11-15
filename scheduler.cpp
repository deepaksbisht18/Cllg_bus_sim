#include "scheduler.h"
#include <string>

Scheduler::Scheduler(bus* bs, Stack* hist){
    b = bs;
    history = hist;
    r = NULL;
    inbound = true;
    active = false;
    totalStudents = 0;
    message = "";
    for(int i = 0; i < 50; i++){
        boardedFor[i] = 0;
    }
}

bool Scheduler::isActive(){
    return active;
}

int Scheduler::getTotalStudents(){
    return totalStudents;
}

std::string Scheduler::getMessage(){
    return message;
}

void Scheduler::finishTrip(){
    tripRecord rec;
    rec.tripNumber = history->size() + 1;
    if(inbound){
        rec.tripType = "Inbound";
    }
    else{
        rec.tripType = "Outbound";
    }
    rec.startStop = startName;
    rec.endStop = endName;
    rec.timeSlot = slot;
    rec.students = totalStudents;
    history->push(rec);
}

bool Scheduler::startInbound(route* rt, std::string timeslot){
    if(active || rt == NULL || rt->size() < 2){
        return false;
    }
    r = rt;
    slot = timeslot;
    inbound = true;
    totalStudents = 0;
    for(int i = 0; i < 50; i++){
        boardedFor[i] = 0;
    }

    b->reset();
    b->setPosition(r->gethead());
    b->setState("Moving");

    routeNode* cur = r->gethead();
    startName = cur->stop->get_name();
    while(cur->next != NULL){
        cur = cur->next;
    }
    endName = cur->stop->get_name();

    active = true;
    message = "Trip started";
    return true;
}

bool Scheduler::startOutbound(route* rt, std::string timeslot){
    if(active || rt == NULL || rt->size() < 2){
        return false;
    }
    r = rt;
    slot = timeslot;
    inbound = false;
    totalStudents = 0;
    for(int i = 0; i < 50; i++){
        boardedFor[i] = 0;
    }

    b->reset();

    routeNode* cur = r->gethead();
    endName = cur->stop->get_name();

    Queue q;
    while(cur->next != NULL){
        q.enqueue(cur->stop);
        cur = cur->next;
    }
    startName = cur->stop->get_name();

    b->setState("Boarding");
    Stop* s;
    while(!b->isFull() && q.dequeue(s)){
        int n = b->boardFrom(s);
        int id = s->get_id();
        if(id >= 0 && id < 50){
            boardedFor[id] = n;
        }
        totalStudents += n;
    }

    r->reverse();
    b->setPosition(r->gethead());
    b->setState("Moving");

    active = true;
    message = "Departing " + startName + " with " + std::to_string(totalStudents) + " students";
    return true;
}

bool Scheduler::step(){
    if(!active){
        return false;
    }
    routeNode* pos = b->getPosition();
    Stop* s = pos->stop;

    if(inbound){
        if(pos->next != NULL){
            if(b->isFull()){
                message = s->get_name() + ": bus full, not stopping";
            }
            else{
                b->setState("Boarding");
                int n = b->boardFrom(s);
                totalStudents += n;
                message = s->get_name() + ": boarded " + std::to_string(n)
                          + ", load " + std::to_string(b->getLoad());
            }
            b->setState("Moving");
            b->moveNext();
            return true;
        }
        b->dropStudents(b->getLoad());
        b->setState("Arrived");
        message = "Arrived at " + s->get_name() + " with "
                  + std::to_string(totalStudents) + " students";
        finishTrip();
        active = false;
        return false;
    }

    int id = s->get_id();
    int n = 0;
    if(id >= 0 && id < 50){
        n = boardedFor[id];
    }
    if(n > 0){
        b->dropStudents(n);
        message = s->get_name() + ": dropped " + std::to_string(n)
                  + ", load now " + std::to_string(b->getLoad());
    }
    else{
        message = s->get_name() + ": no one to drop, passing";
    }

    if(pos->next == NULL){
        b->setState("Arrived");
        finishTrip();
        r->reverse();
        active = false;
        return false;
    }
    b->moveNext();
    return true;
}