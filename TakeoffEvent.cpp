// CLASS: TakeoffEvent (Implementation)
//
// Author: Alanna Morris, 7748195
//
// REMARKS: Implementation for a takeoff event, calculates unique operational request time.
//
//-----------------------------------------
#include "TakeoffEvent.h"

// Constructor
TakeoffEvent::TakeoffEvent(Plane* plane, int requestTime, const std::string& requestType)
    : Event(plane, requestTime), requestType(requestType) {
    calculateTotalOperationalRequestTime();  // Calculate total operational request time
}

std::string TakeoffEvent::getRequestType() const { return requestType; }

// Calculate the total operational request time for a takeoff event
void TakeoffEvent::calculateTotalOperationalRequestTime() {
    int time = 1 + getPlane()->getWakeTurbulenceTime(); 
    setTotalOperationalRequestTime(time); 
}