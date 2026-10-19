#include <iostream>
#include "stop.h"
#include "queue.h"

int main()
{
    Stop raipur(1, "Raipur", 100, 100);
    Stop nehrugram(2, "Nehrugram", 200, 150);
    Stop rispana(3, "Rispana", 300, 200);

    raipur.set_waitingStudent(20);
    nehrugram.set_waitingStudent(25);
    rispana.set_waitingStudent(30);

    // Test 1: normal boarding in priority order
    Queue q;
    q.enqueue(&raipur);
    q.enqueue(&nehrugram);
    q.enqueue(&rispana);
    std::cout << "Queue size: " << q.size() << std::endl;

    int seats = 50;
    QueueData cur;
    while (seats > 0 && q.dequeue(cur))
    {
        int boarded = cur->boardStudent(seats);
        seats -= boarded;
        std::cout << cur->get_name() << ": boarded " << boarded
                  << ", seats left " << seats
                  << ", still waiting " << cur->get_waitingStudent() << std::endl;
    }
    std::cout << "Queue empty? " << q.isempty() << std::endl;
    std::cout << "Dequeue on empty: " << q.dequeue(cur) << std::endl;

    // Test 2: bus gets full early, remaining stops are skipped
    raipur.set_waitingStudent(20);
    nehrugram.set_waitingStudent(25);
    rispana.set_waitingStudent(30);

    Queue q2;
    q2.enqueue(&raipur);
    q2.enqueue(&nehrugram);
    q2.enqueue(&rispana);

    seats = 20;
    while (seats > 0 && q2.dequeue(cur))
    {
        int boarded = cur->boardStudent(seats);
        seats -= boarded;
        std::cout << cur->get_name() << ": boarded " << boarded
                  << ", seats left " << seats << std::endl;
    }
    std::cout << "Stops skipped (left in queue): " << q2.size() << std::endl;

    // Test 3: enqueue again after the queue was emptied (checks the rear fix)
    q.enqueue(&nehrugram);
    q.dequeue(cur);
    std::cout << "Reuse test: " << cur->get_name() << std::endl;

    return 0;
}