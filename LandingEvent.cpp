// CLASS: LandingEvent (Implementation)
//
// Author: Alanna Morris, 7748195
//
// REMARKS: Implementation for a landing event, calculates unique operational request time.
//
//-----------------------------------------
#include "LandingEvent.h"

// Constructor
LandingEvent::LandingEvent(Plane* plane, int requestTime, const std::string& requestType)
    : Event(plane, requestTime), requestType(requestType) {
    calculateTotalOperationalRequestTime();  // Calculate total operational request time
}

std::string LandingEvent::getRequestType() const { return requestType; }

// Calculate the total operational request time for a landing event
void LandingEvent::calculateTotalOperationalRequestTime() {
    int time = 3 + getPlane()->getWakeTurbulenceTime();  
    setTotalOperationalRequestTime(time); 
}