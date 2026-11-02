#include "filehandler.h"
#include <fstream>
bool saveHistory(Stack& h, std::string filename){
    std::ofstream file(filename.c_str());   
    if(!file){
        return false;                     
    }
    file << "TripNumber,TripType,StartStop,EndStop,TimeSlot,Students\n";
    stackNode* p = h.get_top();
    while(p != NULL){
        file << p->data.tripNumber << ","
             << p->data.tripType << ","
             << p->data.startStop << ","
             << p->data.endStop << ","
             << p->data.timeSlot << ","
             << p->data.students << "\n";
        p = p->next;
    }
    file.close();
    return true;
}