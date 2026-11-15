#ifndef SCHEDULER_H
#define SCHEDULER_H
#include"route.h"
#include"bus.h"
#include"stack.h"
#include"triprecord.h"
#include"queue.h"
#include<string>
class Scheduler
{
private:
    route* r;
    bus* b;
    Stack* history;
    bool inbound;
    bool active;
    std::string slot,startName,endName,message;
    int totalStudents;
    int boardedFor[50];
    void finishTrip();
public:
    Scheduler(bus* bs,Stack* hist);
    bool startInbound(route* rt,std::string timeslot);
    bool startOutbound(route* rt,std::string timeslot);
    bool step();
    bool isActive();
    int getTotalStudents();
    std::string getMessage();
};



#endif