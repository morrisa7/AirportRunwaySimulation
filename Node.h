// CLASS: Node (Header)
//
// Author: Alanna Morris, 7748195
//
// REMARKS: This class represents a node in the linked list. 
//          A node stores a plane event and a pointer to the next node.
//
//-----------------------------------------
#ifndef NODE_H
#define NODE_H

#include "Event.h"

class Node {
private:
    Event* theEvent;
    Node* next;

public:
    // Constructor:
    Node(Event* event, Node* next = nullptr);

    // Constructor: (type specific for printing in simulation class)
    Node(Event* event, int type, Node* next = nullptr); 

    // Methods:
    Event* getEvent() const;
    Node* getNext() const;

    void setNext(Node* nextNode);
    void setEvent(Event* event);

};

#endif