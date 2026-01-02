// CLASS: TakeoffEvent (Header)
//
// Author: Alanna Morris, 7748195
//
// REMARKS: Class representing a takeoff event for a plane.
//          The operational request time is unique for takeoffs.
//
//-----------------------------------------
#ifndef TAKEOFFEVENT_H
#define TAKEOFFEVENT_H

#include "Event.h"

class TakeoffEvent : public Event {
private:
    std::string requestType; // requestType is "takeoff"

public:
    // Constructor
    TakeoffEvent(Plane* plane, int requestTime, const std::string& requestType);

    // Methods
    std::string getRequestType() const override;
    void calculateTotalOperationalRequestTime() override; // Calculate total time needed on runway
};

#endif  // TAKEOFFEVENT_H