// CLASS: LandingEvent (Header)
//
// Author: Alanna Morris, 7748195
//
// REMARKS: Class representing a landing event for a plane.
//          The operational request time is unqiue for landings. 
//
//-----------------------------------------
#ifndef LANDINGEVENT_H
#define LANDINGEVENT_H

#include "Event.h"

class LandingEvent : public Event {
private:
    std::string requestType; // requestType is  "landing"

public:
    // Constructor
    LandingEvent(Plane* plane, int requestTime, const std::string& requestType);

    // Methods
    std::string getRequestType() const override;
    void calculateTotalOperationalRequestTime() override; // Calculate total time needed on runway
};

#endif  // LANDINGEVENT_H