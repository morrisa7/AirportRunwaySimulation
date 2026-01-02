// CLASS: Runway (Header)
//
// Author: Alanna Morris, 7748195
//
// REMARKS: This class represents a runway manager. 
//          It stores a list of runways and uses methods to manage them.
//          Can collect the next free runway and update the availabilty
//          of all runways in respect to the current time. 
//
//-----------------------------------------
#ifndef RUNWAYMANAGER_H
#define RUNWAYMANAGER_H

#include <vector>
#include "Runway.h"

class RunwayManager {
private:
    const int numRunways; // from user, collected and used to set the list size
    std::vector<Runway> runways; // list of runways to manage

public:
    // Constructor
    RunwayManager(int numRunways);

    // Runway Management Methods
    void updateRunways(int currentTime); // updates availability of runways, with respect to curr time
    bool hasAvailableRunway(int currentTime); // true if any runway in the list is available at this curr time
    Runway* getNextAvailableRunway(int currentTime); // returns the next available runway 
    int getNumRunways() const { return numRunways; }
};

#endif // RUNWAYMANAGER_H