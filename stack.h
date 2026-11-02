#ifndef STACK_H
#define STACK_H
#include "triprecord.h"
typedef tripRecord sd;
struct stackNode{
    sd data;
    stackNode* next;
};
class Stack{
    private:
    stackNode* top;
    int count;
    public:
    Stack();
    ~Stack();
    void push(sd val);
    bool pop(sd& out);
    bool peek(sd& out);
    bool isempty();
    int size();
    stackNode* get_top();
    void display();
};
#endif