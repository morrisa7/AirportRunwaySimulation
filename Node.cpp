// CLASS: Node (Implementation)
//
// Author: Alanna Morris, 7748195
//
// REMARKS: This class represents a node in the linked list. 
//          A node stores a plane event and a pointer to the next node.
//
//-----------------------------------------
#include "Node.h"

// Constructor:
Node::Node(Event* event, Node* next) : theEvent(event), next(next) {}

// Methods:
Event* Node::getEvent() const { return theEvent; }
Node* Node::getNext() const { return next; }

void Node::setNext(Node* nextNode) { next = nextNode; }
void Node::setEvent(Event* event) { theEvent = event; }
