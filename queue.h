#ifndef QUEUE_H
#define QUEUE_H

#include "stop.h"

typedef Stop* QueueData;

struct node {
    QueueData data;
    node* next;
};

class Queue {
private:
    node* front;
    node* rear;
    int count;

public:
    Queue();
    ~Queue();
    void enqueue(QueueData val);
    bool dequeue(QueueData& out);
    bool isempty();
    int size();
};

#endif 