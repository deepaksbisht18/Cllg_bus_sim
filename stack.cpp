#include"stack.h"
#include<iostream>
Stack::Stack(){
    top=NULL;
    count=0;
}
void Stack::push(sd val){
    stackNode* nn=new stackNode;
    nn->data=val;
    if(top==NULL){
        nn->next=NULL;
        top=nn;
        count++;
        return;
    }
    nn->next=top;
    top=nn;
    count++;
}
bool Stack::pop(sd &out){
    if(top==NULL){
        return false;
    }
    stackNode* temp=top;
    out=temp->data;
    top=top->next;
    count--;
    delete temp;
    return true;
}
bool Stack::peek(sd &out){
    if(top==NULL){
        return false;
    }
    out=top->data;
    return true;
}
bool Stack::isempty(){
    return count==0;
}
int Stack::size(){
    return count;
}
stackNode* Stack::get_top(){
    return top;
}
void Stack::display(){
    if(top==NULL){
        std::cout<<"No trips yet"<<std::endl;
        return;
    }
    stackNode* cur=top;
    while(cur!=NULL){
        std::cout<<cur->data.tripNumber<<" |"<<cur->data.tripType<<" |"<<cur->data.startStop<<" |"<<cur->data.endStop<<" |"<<cur->data.timeSlot<<" |"<<cur->data.students;
        std::cout<<std::endl;
        cur=cur->next;
    }
}
Stack::~Stack(){
    sd temp;
    while(pop(temp)){
    }
}