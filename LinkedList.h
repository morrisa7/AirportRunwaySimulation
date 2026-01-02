// CLASS: LinkedList (Header)
//
// Author: Alanna Morris, 7748195
//
// REMARKS: This class represents a linked list storing events for the airport simulation. 
//          It adds events to the back of the list to create a line.
//          It has an option to organize events if priority is ever necessary in that list. 
//          For example only planes present at the airport require a prioritized list to decide who goes next.
//
//-----------------------------------------
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"

class LinkedList {
private:
    Node* top;
    Node* tail;
public:
    // Constructor
    LinkedList();

    // Destructor
    ~LinkedList();

    // Methods
    bool isEmpty() const;
    void addBack(Event* event);
    Event* removeFront();
    void remove(Event* event); 
    void organizePriority();
    Node* getTop() const;
    void organizeAtcID(); 
    void setTop(Node* newTop);
};

#endif