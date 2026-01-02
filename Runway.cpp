// CLASS: Runway (Implementation)
//
// Author: Alanna Morris, 7748195
//
// REMARKS: This class represents a runway in an airport simulation. 
//          It manages the runway’s ID, availability, and occupied time.
//
//-----------------------------------------
#include <iostream>
#include "Runway.h"

// Constructor: 
Runway::Runway(int id) : runwayID(id), isAvailable(true), occupiedUntil(0) {}

// Getter methods
int Runway::getRunwayID() const { return runwayID; }
int Runway::getOccupiedUntil() const { return occupiedUntil; }
bool Runway::getAvailability() const { return isAvailable; }

// Runway Management methods
void Runway::occupyRunway(int timeNeeded, int currentTime) { // curr time + time needed = new "occupied until" time
    if (!isAvailable) {
        std::cout << "Error: Runway " << runwayID << " is currently in use. Occupation request denied." << std::endl;
        return;
    }
    occupiedUntil = currentTime + timeNeeded; // set new occupied time based on current time
    isAvailable = false; // Marks the runway as occupied
}

void Runway::updateAvailability(int currentTime) {
    if (currentTime >= occupiedUntil) {
        isAvailable = true; // Runway becomes available if current time exceeds the occupied time
    }
}