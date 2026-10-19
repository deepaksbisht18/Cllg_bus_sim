#ifndef STOP_H
#define STOP_H

#include <string>

class Stop {
private:
    int id;
    std::string name;
    int x, y;
    int waitingStudent;

public:
    Stop(int i, std::string n, int xa, int ya);

    void set_waitingStudent(int n);
    int get_id();
    std::string get_name();
    int get_x();
    int get_y();
    int get_waitingStudent();

    int boardStudent(int seatsAvailable);
    void display();
};

#endif 