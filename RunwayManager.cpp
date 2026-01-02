// CLASS: Runway (Implementation)
//
// Author: Alanna Morris, 7748195
//
// REMARKS: This class represents a runway manager. 
//          It stores a list of runways and uses methods to manage them.
//          Can collect the next free runway and update the availabilty
//          of all runways in respect to the current time. 
//
//-----------------------------------------
#include <iostream>
#include "RunwayManager.h"

// Constructor
RunwayManager::RunwayManager(int numRunways)  : numRunways(numRunways) {
    for (int i = 1; i <= numRunways; ++i) {
        runways.push_back(Runway(i)); // Add each runway
    }
}

// Runway Management Methods
void RunwayManager::updateRunways(int currentTime) { // update availability of runways based on current time
    for (auto& runway : runways) {
        runway.updateAvailability(currentTime); // uses method in runway class, applies all runways in list
    }
}

Runway* RunwayManager::getNextAvailableRunway(int currentTime) { // get the next available runway based on curr time
    updateRunways(currentTime); // make sure runways are up to date

    for (auto& runway : runways) { // search the list of runways
        if (runway.getAvailability()) { // if a open availaibitly 
            return &runway; // return the first open one
        }
    }
    return nullptr; // if none, return null
}

bool RunwayManager::hasAvailableRunway(int currentTime) { // check if any runway is available
    updateRunways(currentTime); // ensure they are up to date

    for (const auto& runway : runways) { // search the list
        if (runway.getAvailability()) { // if one is true (aka available)
            return true; // return true
        }
    }
    return false; // if none were open, return false (aka none available)
}