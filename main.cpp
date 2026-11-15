#include <iostream>
#include <string>
#include <cstdlib>
#include "stop.h"
#include "route.h"
#include "bus.h"
#include "stack.h"
#include "scheduler.h"
#include "filehandler.h"
#include "graph.h"

int getnum(std::string msg,int low,int high){
    int x;
    while(true){
        std::cout<<msg;
        if(std::cin>>x && x>=low && x<=high){
            std::cin.ignore(1000,'\n');
            return x;
        }
        if(std::cin.eof()){
            exit(0);
        }
        std::cin.clear();
        std::cin.ignore(1000,'\n');
        std::cout<<"Wrong input, enter "<<low<<" to "<<high<<std::endl;
    }
}

std::string getslot(bool in){
    int c;
    if(in){
        std::cout<<"1. 7:00 AM"<<std::endl;
        std::cout<<"2. 11:00 AM"<<std::endl;
        c=getnum("Choose time slot: ",1,2);
        if(c==1){
            return "7:00 AM";
        }
        return "11:00 AM";
    }
    std::cout<<"1. 1:00 PM"<<std::endl;
    std::cout<<"2. 4:00 PM"<<std::endl;
    std::cout<<"3. 6:00 PM"<<std::endl;
    c=getnum("Choose time slot: ",1,3);
    if(c==1){
        return "1:00 PM";
    }
    if(c==2){
        return "4:00 PM";
    }
    return "6:00 PM";
}

route* getroute(route& r1,route& r2){
    std::cout<<"1. ";
    r1.display();
    std::cout<<"2. ";
    r2.display();
    int c=getnum("Choose route: ",1,2);
    if(c==1){
        return &r1;
    }
    return &r2;
}

void getcount(route& r,bool in){
    routeNode* cur=r.gethead();
    while(cur->next!=NULL){
        std::string msg;
        if(in){
            msg="Students waiting at "+cur->stop->get_name()+": ";
        }
        else{
            msg="Students going to "+cur->stop->get_name()+": ";
        }
        cur->stop->set_waitingStudent(getnum(msg,0,200));
        cur=cur->next;
    }
}

void runtrip(Scheduler& sch){
    std::cout<<sch.getMessage()<<std::endl;
    bool more=true;
    while(more){
        std::cout<<"Press Enter for next stop...";
        std::cin.get();
        more=sch.step();
        std::cout<<sch.getMessage()<<std::endl;
    }
    std::cout<<"Trip added to history"<<std::endl;
}

void exportfile(Stack& h){
    if(h.isempty()){
        std::cout<<"No trips to export"<<std::endl;
        return;
    }
    if(saveHistory(h,"trip_history.csv")){
        std::cout<<"History exported to trip_history.csv"<<std::endl;
    }
    else{
        std::cout<<"Could not export history"<<std::endl;
    }
}

void showroutes(route& r1,route& r2){
    std::cout<<"Route 1: ";
    r1.display();
    std::cout<<"Route 2: ";
    r2.display();
}

int main(){
    Stop raipur(1,"Raipur",100,100);
    Stop nehru(2,"Nehrugram",200,150);
    Stop rispana(3,"Rispana",300,200);
    Stop college(4,"College",400,250);
    Stop rajpur(5,"Rajpur",100,300);
    Stop dilaram(6,"Dilaram Chowk",200,320);
    Stop ctower(7,"Clock Tower",300,340);
    Stop* st[8]={NULL,&raipur,&nehru,&rispana,&college,&rajpur,&dilaram,&ctower};

    route r1;
    r1.addstop(&raipur);
    r1.addstop(&nehru);
    r1.addstop(&rispana);
    r1.addstop(&college);

    route r2;
    r2.addstop(&rajpur);
    r2.addstop(&dilaram);
    r2.addstop(&ctower);
    r2.addstop(&college);

    graph g;
    for(int i=1;i<=7;i++){
        g.addstop(st[i]);
    }
    g.addedge(1,2);
    g.addedge(2,3);
    g.addedge(3,4);
    g.addedge(2,4);
    g.addedge(5,6);
    g.addedge(6,7);
    g.addedge(7,4);

    bus b(50);
    Stack h;
    Scheduler sch(&b,&h);

    bool run=true;
    while(run){
        std::cout<<std::endl;
        std::cout<<"===== College Bus Simulator ====="<<std::endl;
        std::cout<<"1. Inbound trip (to college)"<<std::endl;
        std::cout<<"2. Outbound trip (from college)"<<std::endl;
        std::cout<<"3. Show trip history"<<std::endl;
        std::cout<<"4. Show routes"<<std::endl;
        std::cout<<"5. Export history to CSV"<<std::endl;
        std::cout<<"6. Exit"<<std::endl;
        int ch=getnum("Enter choice: ",1,6);
        if(ch==1){
            route* rt=getroute(r1,r2);
            std::string sl=getslot(true);
            getcount(*rt,true);
            if(sch.startInbound(rt,sl)){
                runtrip(sch);
            }
            else{
                std::cout<<"Could not start trip"<<std::endl;
            }
        }
        else if(ch==2){
            route* rt=getroute(r1,r2);
            std::string sl=getslot(false);
            getcount(*rt,false);
            if(sch.startOutbound(rt,sl)){
                runtrip(sch);
            }
            else{
                std::cout<<"Could not start trip"<<std::endl;
            }
        }
        else if(ch==3){
            h.display();
        }
        else if(ch==4){
            showroutes(r1,r2);
        }
        else if(ch==5){
            exportfile(h);
        }
        else{
            run=false;
        }
    }
    return 0;
}
