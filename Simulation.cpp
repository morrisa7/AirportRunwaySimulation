// CLASS: Simulation (Implementation)
//
// Author: Alanna Morris, 7748195
//
// REMARKS: Class for simulating airport operations, including event handling, 
//          runway management, and time tracking. 
//
//-----------------------------------------
#include "Simulation.h"

// Constructor
Simulation::Simulation(LinkedList* initialWaitingList, int numRunways) 
    : eventsList(initialWaitingList),  // initializer list
      currentEvents(new LinkedList()),
      completedEvents(new LinkedList()),
      currentTime(0),
      totalWastedTime(0),
      runwayManager(new RunwayManager(numRunways)) 
{
    // body
}

// Deconstructor
Simulation::~Simulation() { // clean up the lists
    delete completedEvents;
    delete currentEvents;
    delete runwayManager; 
    delete eventsList;  
}

// Printing:
void Simulation::printIncomingEvent(Event* event, int currentTime) { // message for new events
    std::cout << "TIME: " << currentTime << "-> " 
              << event->getPlane()->getCallSign() << " " 
              << event->getPlane()->getFlightNumber() << " (" 
              << event->getPlane()->getAtcID() << ") "
              << event->getPlane()->getSize() << " "
              << (event->getRequestType() == "landing" ? "inbound for landing" : "ready for takeoff")
              << ".\n";
}

void Simulation::printActiveEvent(Event* event, int currentTime) { // message for events who got clearance
    std::cout << "TIME: " << currentTime << "-> " 
              << event->getPlane()->getCallSign() << " " 
              << event->getPlane()->getFlightNumber() << " (" 
              << event->getPlane()->getAtcID() << ") "
              << event->getPlane()->getSize() 
              << (event->getRequestType() == "landing" ? 
                 " cleared for landing on runway " : 
                 " cleared for takeoff on runway ")
              << event->getRunwayID() << ". (time req. for "
              << event->getRequestType() << ": " 
              << event->getTotalOperationalRequestTime() << ")\n";
}

void Simulation::printCompletedEvent(Event* event, int currentTime) { // message for completed events
    std::cout << "TIME: " << currentTime << "-> " 
              << event->getPlane()->getCallSign() << " " 
              << event->getPlane()->getFlightNumber() << " (" 
              << event->getPlane()->getAtcID() << ") "
              << event->getPlane()->getSize() 
              << " has cleared the runway " << event->getRunwayID() << ".\n";
}

void Simulation::printSimulationEnd() { // end message of a simulation
    std::cout << "\n#######################" << std::endl;
    std::cout << " The simulation has ended." << std::endl;
    std::cout << " The number of runways was " << runwayManager->getNumRunways()<< "." << std::endl;
    std::cout << " The total amount of time wasted because runways were not available was " << totalWastedTime << " minutes." << std::endl;
    std::cout << "#######################\n" << std::endl;
}

void Simulation::run() {
    std::cout << "\nSimulation begins...\n";
    currentTime = 1;
    totalWastedTime = 0;

    // Main simulation loop continues while there are events to process
    while (!eventsList->isEmpty() || !currentEvents->isEmpty() || 
           hasUncompletedEvents()) {
        
        bool processedAnEvent = false;
        
        // Prepare lists for this time slice
        LinkedList* arrivals = new LinkedList();
        LinkedList* clearances = new LinkedList();
        LinkedList* completions = new LinkedList();
        
        // Process new arrivals at current time
        processNewArrivals(arrivals, clearances, processedAnEvent);

        // Process waiting events in current events list
        processWaitingEvents(clearances, processedAnEvent);

        // Check and mark completed events
        processCompletedEvents(completions, processedAnEvent);

        // Sort lists by ATC ID
        completions->organizeAtcID();
        arrivals->organizeAtcID();
        clearances->organizeAtcID();
        
        // Print events in specific order
        printEvents(completions, arrivals, clearances);

        // Clean up temporary lists
        delete arrivals;
        delete clearances;
        delete completions;

        // Advance time if no events processed
        if (!processedAnEvent) {
            currentTime++;
        }
    }

    // Calculate and print final simulation results
    totalWastedTime = calculateTotalWastedTime();
    printSimulationEnd();
}

// Helper method to check for uncompleted events (fully completed and print message printed)
bool Simulation::hasUncompletedEvents() {
    Node* node = completedEvents->getTop();
    while (node != nullptr) {
        if (!node->getEvent()->getIsCompleted()) {
            return true;
        }
        node = node->getNext();
    }
    return false;
}

// Extract new arrival processing to a separate method
void Simulation::processNewArrivals(LinkedList* arrivals, LinkedList* clearances, bool& processedAnEvent) {
    Node* currentNode = eventsList->getTop();
    while (currentNode != nullptr && currentNode->getEvent()->getRequestTime() == currentTime) {
        Event* event = eventsList->removeFront();
        arrivals->addBack(event);
        
        runwayManager->updateRunways(currentTime);
        if (runwayManager->hasAvailableRunway(currentTime)) {
            Runway* assignedRunway = runwayManager->getNextAvailableRunway(currentTime);
            event->setRunwayID(assignedRunway->getRunwayID());
            
            int completionTime = currentTime + event->getTotalOperationalRequestTime();
            event->setCompletionTime(completionTime);
            
            assignedRunway->occupyRunway(event->getTotalOperationalRequestTime(), currentTime);
            clearances->addBack(event);
            
            completedEvents->addBack(event);
            processedAnEvent = true;
        } else {
            currentEvents->addBack(event);
        }
        
        currentNode = eventsList->getTop();
    }
}

// Extract waiting events processing to a separate method
void Simulation::processWaitingEvents(LinkedList* clearances, bool& processedAnEvent) {
    if (!currentEvents->isEmpty()) {
        currentEvents->organizePriority();
        runwayManager->updateRunways(currentTime);
        
        while (!currentEvents->isEmpty() && runwayManager->hasAvailableRunway(currentTime)) {
            Event* event = currentEvents->removeFront();
            assignRunwayToEvent(event, clearances, processedAnEvent);
        }
    }
}

// Extract completed events processing to a separate method
void Simulation::processCompletedEvents(LinkedList* completions, bool& processedAnEvent) {
    Node* completedNode = completedEvents->getTop();
    while (completedNode != nullptr) {
        Event* completedEvent = completedNode->getEvent();
        if (completedEvent->getCompletionTime() == currentTime && !completedEvent->getIsCompleted()) {
            completions->addBack(completedEvent);
            completedEvent->setCompleted();
            processedAnEvent = true;
        }
        completedNode = completedNode->getNext();
    }
}

// Extract event printing to a separate method
void Simulation::printEvents(LinkedList* completions, LinkedList* arrivals, LinkedList* clearances) {
    // Print completions first
    Node* node = completions->getTop();
    while (node != nullptr) {
        printCompletedEvent(node->getEvent(), currentTime);
        node = node->getNext();
    }

    // Print arrivals and clearances for each ATC ID
    for (int atcID = 1; atcID <= 9; atcID++) {
        // Check for and print arrival
        node = arrivals->getTop();
        while (node != nullptr) {
            Event* event = node->getEvent();
            if (event->getPlane()->getAtcID() == atcID) {
                printIncomingEvent(event, currentTime);
                break;
            }
            node = node->getNext();
        }

        // Check for and print clearance
        node = clearances->getTop();
        while (node != nullptr) {
            Event* event = node->getEvent();
            if (event->getPlane()->getAtcID() == atcID) {
                printActiveEvent(event, currentTime);
                break;
            }
            node = node->getNext();
        }
    }
}

int Simulation::calculateTotalWastedTime() { // iterates each event and sums up waiting times 
    int totalWasted = 0;
    Node* current = completedEvents->getTop();
    
    while (current != nullptr) { // cycled through all completed events
        Event* event = current->getEvent();
        // Calculate wait time = actual completion time - event operational time - original request time
        int waitTime = event->getCompletionTime() - 
                      event->getTotalOperationalRequestTime() - 
                      event->getRequestTime();
        if (waitTime > 0) {
            totalWasted += waitTime; // add to the wait times running sum
        }
        current = current->getNext(); // move to the next event to check
    }
    return totalWasted; // return the final sum of all wait times
}

// Assigns arunway to an event, sets occupation time to runway, updates an events true completion time
void Simulation::assignRunwayToEvent(Event* event, LinkedList* clearances, bool& processedAnEvent) {
    Runway* assignedRunway = runwayManager->getNextAvailableRunway(currentTime);
    event->setRunwayID(assignedRunway->getRunwayID());
    
    int completionTime = currentTime + event->getTotalOperationalRequestTime();
    event->setCompletionTime(completionTime);
    
    assignedRunway->occupyRunway(event->getTotalOperationalRequestTime(), currentTime);
    clearances->addBack(event);
    
    completedEvents->addBack(event);
    processedAnEvent = true;
}