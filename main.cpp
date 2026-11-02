#include <iostream>
#include "stack.h"

tripRecord makeTrip(int n, std::string type, std::string s, std::string e, std::string t, int st){
    tripRecord r;
    r.tripNumber = n;
    r.tripType = type;
    r.startStop = s;
    r.endStop = e;
    r.timeSlot = t;
    r.students = st;
    return r;
}

int main()
{
    Stack h;
    sd cur;

    // Test 1: empty stack
    h.display();
    std::cout << "Empty? " << h.isempty() << std::endl;
    std::cout << "Pop on empty: " << h.pop(cur) << std::endl;
    std::cout << "Peek on empty: " << h.peek(cur) << std::endl;

    // Test 2: push three trips
    h.push(makeTrip(1, "Inbound", "Raipur", "College", "7:00 AM", 50));
    h.push(makeTrip(2, "Outbound", "College", "Raipur", "1:00 PM", 45));
    h.push(makeTrip(3, "Outbound", "College", "Rispana", "4:00 PM", 30));
    std::cout << "Size: " << h.size() << std::endl;
    h.display();

    // Test 3: peek does not remove
    h.peek(cur);
    std::cout << "Peek: trip " << cur.tripNumber << ", size still " << h.size() << std::endl;

    // Test 4: pop removes the latest
    h.pop(cur);
    std::cout << "Popped: trip " << cur.tripNumber << ", size " << h.size() << std::endl;
    h.peek(cur);
    std::cout << "New top: trip " << cur.tripNumber << std::endl;

    // Test 5: walk the stack with get_top (how the file handler will read it)
    stackNode* p = h.get_top();
    int total = 0;
    while (p != NULL)
    {
        std::cout << "Walking: trip " << p->data.tripNumber << std::endl;
        total += p->data.students;
        p = p->next;
    }
    std::cout << "Total students in history: " << total << std::endl;

    // Test 6: empty it completely, then reuse
    while (h.pop(cur)) { }
    std::cout << "Empty after popping all? " << h.isempty() << std::endl;
    h.push(makeTrip(4, "Inbound", "Raipur", "College", "7:00 AM", 40));
    h.peek(cur);
    std::cout << "Reuse: trip " << cur.tripNumber << ", size " << h.size() << std::endl;

    return 0;
}