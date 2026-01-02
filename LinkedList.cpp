// CLASS: LinkedList (Implementation)
//
// Author: Alanna Morris, 7748195
//
// REMARKS: This class represents a linked list storing events for the airport simulation. 
//          It adds events to the back of the list to create a line.
//          It has an option to organize events if priority is ever necessary in that list. 
//          For example only planes present at the airport require a prioritized list to decide who goes next.
//
//-----------------------------------------

#include "LinkedList.h"
#include "Event.h"
#include <iostream>

// Constructor
LinkedList::LinkedList() : top(nullptr), tail(nullptr) {}

// Destructor for LinkedList
LinkedList::~LinkedList() {
    Node* current = top;
    while (current != nullptr) {
        Node* temp = current;
        current = current->getNext();
        delete temp; 
    }
}

// General Methods:
bool LinkedList::isEmpty() const {
    return top == nullptr;
}

void LinkedList::addBack(Event* event) { // add to back for FIFO
    Node* newNode = new Node(event);
    if (isEmpty()) {
        top = newNode;
        tail = newNode;
    } else {
        tail->setNext(newNode);
        tail = newNode;
    }
}

void LinkedList::organizePriority() { // will be used to order the list of currently present activies
    if (isEmpty() || !top->getNext()) return; // dont sort if empty or only 1

    bool swapped; // will bring landings first and secondly order by ATC ID (smallest to largest)
    do {
        swapped = false;
        Node* current = top;
        while (current && current->getNext()) { // while the node pair exists
            // compare current node with next node
            // swap if takeoff is before landing
            // swap if same type, but higher ATC ID in first event
            if ((current->getEvent()->getRequestType() == "takeoff" && current->getNext()->getEvent()->getRequestType() == "landing") ||
                (current->getEvent()->getRequestType() == current->getNext()->getEvent()->getRequestType() &&
                 current->getEvent()->getPlane()->getAtcID() > current->getNext()->getEvent()->getPlane()->getAtcID())) {

                // swap the nodes to correct the order
                Event* tempEvent = current->getEvent();
                current->setEvent(current->getNext()->getEvent());
                current->getNext()->setEvent(tempEvent);

                swapped = true;
            }
            current = current->getNext();
        }
    } while (swapped);  // continue looping if any swaps happened
}

Event* LinkedList::removeFront() { // take first item from list, typically to process or redirect this plane event
    if (isEmpty()) return nullptr;

    Node* temp = top;
    Event* event = temp->getEvent();

    top = top->getNext();
    if (top == nullptr) tail = nullptr;  // list became emtpy

    delete temp;  // free memory of node, but not the event
    return event; 
}

Node* LinkedList::getTop() const { return top; }

// when printing complete events at same time step, smallest atcID to largest gest printed
void LinkedList::organizeAtcID() {
    if (isEmpty() || !top->getNext()) return;

    bool swapped;
    do {
        swapped = false;
        Node* current = top;
        
        while (current && current->getNext()) {
            if (current->getEvent()->getPlane()->getAtcID() > current->getNext()->getEvent()->getPlane()->getAtcID()) {
                Event* tempEvent = current->getEvent();
                current->setEvent(current->getNext()->getEvent());
                current->getNext()->setEvent(tempEvent);
                swapped = true;
            }
            current = current->getNext();
        }
    } while (swapped);
}

void LinkedList::setTop(Node* newTop) {
    if (newTop == nullptr) {
        top = nullptr;
        tail = nullptr;  // If setting top to nullptr, the list is empty
    } else {
        top = newTop;
        if (top->getNext() == nullptr) {
            tail = top;  // If newTop is the only node, update tail as well
        }
    }
}

// Removes a specific event from the list
void LinkedList::remove(Event* event) {
    if (isEmpty()) return;

    Node* current = top;
    Node* previous = nullptr;

    while (current != nullptr) {
        if (current->getEvent() == event) { 
            if (previous == nullptr) {
                // if first node, we need to update the top
                top = current->getNext();
                if (top == nullptr) {
                    tail = nullptr; 
                }
            } else {
                // Bypass the node to remove it
                previous->setNext(current->getNext());
                if (previous->getNext() == nullptr) {
                    tail = previous;  // iif last node, update the tail
                }
            }
            delete current; //free mem
            return;
        }
        previous = current;
        current = current->getNext();
    }
}