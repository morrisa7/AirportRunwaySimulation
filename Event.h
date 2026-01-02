// CLASS: Event (Header)
//
// Author: Alanna Morris, 7748195
//
// REMARKS: This is the base class for events. There are two event types: 
//          takeoff and landing events. 
//
//-----------------------------------------
#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include "Plane.h"

class Event {
private:
    Plane* plane;  // The plane for this event
    int requestTime;  // Time when plane wants to be serviced
    int runwayID;  // ID of assigned runway (-1 initially before assigned)
    int totalOperationalRequestTime;  // Total Time the event needs a runway 
    bool isCompleted;  // Flag to indicate if the event is completed and printed (initially false)
    int completionTime;  // when this event actually completed

public:
    // Constructor
    Event(Plane* plane, int requestTime);

    // Destructor
    virtual ~Event();

    // Getter methods 
    Plane* getPlane() const;
    int getRequestTime() const;
    int getRunwayID() const;
    int getTotalOperationalRequestTime() const;  
    bool getIsCompleted() const;
    int getCompletionTime() const;

    // Setter methods
    void setRunwayID(int id);
    void setCompleted();
    void setTotalOperationalRequestTime(int time);
    void setCompletionTime(int time);

    // Virtual methods (to be overridden in derived classes)
    virtual std::string getRequestType() const = 0;
    virtual void calculateTotalOperationalRequestTime() = 0;
};

#endif  // EVENT_H