#include <iostream>
#include "stop.h"
#include "route.h"
#include "bus.h"

int main()
{
    Stop raipur(1, "Raipur", 100, 100);
    Stop nehrugram(2, "Nehrugram", 200, 150);
    Stop rispana(3, "Rispana", 300, 200);
    Stop college(4, "College", 400, 250);

    raipur.set_waitingStudent(20);
    nehrugram.set_waitingStudent(25);
    rispana.set_waitingStudent(30);
    college.set_waitingStudent(0);

    route r;
    r.addstop(&raipur);
    r.addstop(&nehrugram);
    r.addstop(&rispana);
    r.addstop(&college);

    // Test 1: fresh bus
    bus b(50);
    b.display();

    // Test 2: inbound trip, bus walks the route and boards at each stop
    b.setPosition(r.gethead());
    do {
        b.setState("Boarding");
        int boarded = b.boardFrom(b.getPosition()->stop);
        std::cout << b.getPosition()->stop->get_name()
                  << ": boarded " << boarded
                  << ", load " << b.getLoad()
                  << ", seats left " << b.seatsLeft() << std::endl;
        b.setState("Moving");
    } while (b.moveNext());
    b.setState("Arrived");
    b.display();

    // Test 3: full check and dropping students
    std::cout << "Full? " << b.isFull() << std::endl;
    b.dropStudents(20);
    std::cout << "Load after dropping 20: " << b.getLoad() << std::endl;
    b.dropStudents(100);
    std::cout << "Load after dropping 100: " << b.getLoad() << std::endl;
    b.dropStudents(-5);
    std::cout << "Load after dropping -5: " << b.getLoad() << std::endl;

    // Test 4: moving past the end, and moving with no position set
    std::cout << "Move past end: " << b.moveNext() << std::endl;
    bus b2(50);
    std::cout << "No-position moveNext: " << b2.moveNext() << std::endl;
    b2.display();

    // Test 5: outbound travel path (reversed route)
    r.reverse();
    b.setPosition(r.gethead());
    std::cout << "After reverse, start: " << b.getPosition()->stop->get_name() << std::endl;
    b.moveNext();
    std::cout << "Next stop: " << b.getPosition()->stop->get_name() << std::endl;

    return 0;
}