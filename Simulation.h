// CLASS: Simulation (Header)
//
// Author: Alanna Morris, 7748195
//
// REMARKS: Class for simulating airport operations, including event handling, 
//          runway management, and time tracking. 
//
//-----------------------------------------

#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include "Runway.h"
#include "LinkedList.h"
#include "Event.h"
#include "RunwayManager.h"

class Simulation {
private:
    // Event Lists
    LinkedList* eventsList; // events collected from the txt file (waiting in line)
    LinkedList* currentEvents; // events that are currently present at the airport (need a runway)
    LinkedList* completedEvents; // events that have completed and (no longer need a runway)

    // Time tracking Variables
    int currentTime;
    int totalWastedTime;

    // Runway Manager
    RunwayManager* runwayManager;

public:
    enum EventType {
        ARRIVAL,
        CLEARANCE,
        COMPLETION
    };    

    Simulation(LinkedList* initialWaitingList, int numRunways);  // Constructor
    ~Simulation();  // Destructor 

    // Main simulation methods
    void run();
    int calculateTotalWastedTime(); // gets time wasted from each plane and sums it
    void assignRunwayToEvent(Event* event, LinkedList* clearances, bool& processedAnEvent);

    //Printing:
    void printSimulationEnd(); 
    void printIncomingEvent(Event* event, int currentTime);
    void printActiveEvent(Event* event, int currentTime);
    void printCompletedEvent(Event* event, int currentTime);
    
    bool hasUncompletedEvents();
    void processNewArrivals(LinkedList* arrivals, LinkedList* clearances, bool& processedAnEvent);
    void processWaitingEvents(LinkedList* clearances, bool& processedAnEvent);
    void processCompletedEvents(LinkedList* completions, bool& processedAnEvent);
    void printEvents(LinkedList* completions, LinkedList* arrivals, LinkedList* clearances);

};

#endif