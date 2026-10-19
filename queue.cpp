#include "queue.h"

Queue::Queue()
{
    front = NULL;
    rear = NULL;
    count = 0;
}

Queue::~Queue()
{
    QueueData temp;
    while (dequeue(temp)) {
    }
}

void Queue::enqueue(QueueData val)
{
    node *nn = new node;
    nn->data = val;
    nn->next = NULL;
    if (front == NULL)
    {
        front = nn;
        rear = nn;
    }
    else
    {
        rear->next = nn;
        rear = nn;
    }
    count++;
}

bool Queue::dequeue(QueueData &out)
{
    if (front == NULL)
    {
        return false;
    }
    out = front->data;
    node *temp = front;
    front = front->next;
    if (front == NULL)
    {
        rear = NULL;
    }
    delete temp;
    count--;
    return true;
}

bool Queue::isempty()
{
    return count == 0;
}

int Queue::size()
{
    return count;
}