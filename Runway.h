// CLASS: Runway (Header)
//
// Author: Alanna Morris, 7748195
//
// REMARKS: This class represents a runway in an airport simulation. 
//          It has the runway's ID, its availability boolean, and the int
//          when it will next be available based on the time occupied.
//
//-----------------------------------------
#ifndef RUNWAY_H
#define RUNWAY_H

class Runway {
private:
    int runwayID; // ID for the runway (1, 2, 3, etc.)
    bool isAvailable; // Availability: true = available, false = occupied
    int occupiedUntil; // Time until the runway becomes free (if occupied)

public:
    // Constructor
    Runway(int id);

    // Getter methods
    int getRunwayID() const;
    int getOccupiedUntil() const;
    bool getAvailability() const;

    // Runway Management
    void occupyRunway(int timeNeeded, int currentTime);
    void updateAvailability(int currentTime); // updates if current time now is beyond the occupied time
};

#endif // RUNWAY_H