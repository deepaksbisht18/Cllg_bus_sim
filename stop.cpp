#include "stop.h"
#include<iostream>

Stop::Stop(int i, std::string n, int xa, int ya){
    id=i;
    name=n;
    x=xa;
    y=ya;
    waitingStudent=0;
}
void Stop::set_waitingStudent(int n){
    if(n<0){
        waitingStudent=0;
    }
    else{
        waitingStudent=n;
    }
    
}
int Stop::get_id(){
    return id;
}
std::string Stop::get_name(){
    return name;
}
int Stop::get_x(){
    return x;
}
int Stop::get_y(){
    return y;
}
int Stop::get_waitingStudent(){
    return waitingStudent;
}

int Stop::boardStudent(int seatsAvailable){
    if(seatsAvailable <= 0){
        return 0;
    }
    int boarded;
    if(seatsAvailable >= waitingStudent){
        boarded = waitingStudent;
        waitingStudent = 0;
    }
    else{
        boarded = seatsAvailable;
        waitingStudent -= seatsAvailable;
    }
    return boarded;
}

void Stop::display(){
    std::cout<<"the id is: "<<id<<std::endl;
    std::cout<<"the name of stop is: "<<name<<std::endl;
    std::cout<<"students waiting are: "<<waitingStudent<<std::endl;
}