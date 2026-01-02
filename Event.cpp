// CLASS: Event (Implementation)
//
// Author: Alanna Morris, 7748195
//
// REMARKS: Base class for event types.
//
//-----------------------------------------
#include "Event.h"

// Constructor
Event::Event(Plane* plane, int requestTime)
    : plane(plane), requestTime(requestTime), runwayID(-1), totalOperationalRequestTime(0), isCompleted(false), completionTime(-1) {}

// Destructor
Event::~Event() {}

// Getter methods
Plane* Event::getPlane() const { return plane; }
int Event::getRequestTime() const { return requestTime; }
int Event::getRunwayID() const { return runwayID; }
int Event::getTotalOperationalRequestTime() const { return totalOperationalRequestTime; }
bool Event::getIsCompleted() const { return isCompleted; }
int Event::getCompletionTime() const { return completionTime; }

// Setter methods
void Event::setRunwayID(int id) { runwayID = id; }
void Event::setCompleted() { isCompleted = true; }
void Event::setTotalOperationalRequestTime(int time) { totalOperationalRequestTime = time; }
void Event::setCompletionTime(int time) { completionTime = time; }