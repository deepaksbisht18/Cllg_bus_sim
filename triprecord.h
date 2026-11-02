#ifndef TRIPRECORD_H
#define TRIPRECORD_H
#include<string>
struct tripRecord{
    int tripNumber;
    std::string tripType;
    std::string startStop;
    std::string endStop;
    std::string timeSlot;
    int students;
};
#endif