// CLASS: Plane (Implementation)
//
// Author: Alanna Morris, 7748195
//
// REMARKS: This class represents a plane. Planes have specific flight number, call sign,
//          size, current status, & wake turbulence time. 
//          Different plane sizes, use setWakeTurbulenceTime() to get unieq WTT.
//
//-----------------------------------------
#include <iostream>
#include "Plane.h"

// Static ATC ID counter initialization
int Plane::nextATCID = 1;

// Constructor:
Plane::Plane(const std::string& callSign, int flightNumber, const std::string& size)
    : atcID(nextATCID++), callSign(callSign), flightNumber(flightNumber),
      size(size), wakeTurbulenceTime(0){
    calculateWakeTurbulenceTime(); // Calculate wake turbulence time based on size
}

// Getter methods
std::string Plane::getCallSign() const { return callSign; }
int Plane::getFlightNumber() const { return flightNumber; }
std::string Plane::getSize() const { return size; }
int Plane::getAtcID() const { return atcID; }
int Plane::getWakeTurbulenceTime() const { return wakeTurbulenceTime; }

// Calculate wake turbulence time based on plane size
void Plane::calculateWakeTurbulenceTime() {
    if (size == "small") {
        wakeTurbulenceTime = 0;
    } else if (size == "large") {
        wakeTurbulenceTime = 1;
    } else if (size == "heavy") {
        wakeTurbulenceTime = 2;
    } else if (size == "super") {
        wakeTurbulenceTime = 3;
    }
}