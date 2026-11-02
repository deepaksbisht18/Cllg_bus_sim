#include <iostream>
#include "stack.h"
#include "filehandler.h"

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
    h.push(makeTrip(1, "Inbound", "Raipur", "College", "7:00 AM", 50));
    h.push(makeTrip(2, "Outbound", "College", "Raipur", "1:00 PM", 45));
    h.push(makeTrip(3, "Outbound", "College", "Rispana", "4:00 PM", 30));

    // Test 1: normal save
    std::cout << "Save: " << saveHistory(h, "trip_history.csv") << std::endl;

    // Test 2: saving must not change the stack
    sd cur;
    h.peek(cur);
    std::cout << "Size after save: " << h.size() << std::endl;
    std::cout << "Top after save: trip " << cur.tripNumber << std::endl;

    // Test 3: saving an empty stack (file should contain only the header)
    Stack empty;
    std::cout << "Empty stack save: " << saveHistory(empty, "empty.csv") << std::endl;

    // Test 4: a path that cannot be opened
    std::cout << "Bad path save: " << saveHistory(h, "nofolder/trip.csv") << std::endl;

    // Test 5: save again after adding a trip (file is overwritten)
    h.push(makeTrip(4, "Inbound", "Raipur", "College", "7:00 AM", 40));
    std::cout << "Second save: " << saveHistory(h, "trip_history.csv") << std::endl;

    return 0;
}