// CLASS: Plane (Header)
//
// Author: Alanna Morris, 7748195
//
// REMARKS: This class represents a plane. Planes have specific flight number, call sign,
//          size, current status, & wake turbulence time. 
//
//-----------------------------------------
#ifndef PLANE_H
#define PLANE_H

#include <string>
using namespace std;

class Plane {
private:
    static int nextATCID; // Static ATC ID counter
    int atcID; // unique for each plane
    string callSign; // Airline call sign (ex: Delta, AirCanada, Sunwing, etc.)
    int flightNumber; 
    string size; // ex: small, large, heavy, super
    int wakeTurbulenceTime; // time for wake turbulence clearance
    void calculateWakeTurbulenceTime(); // calc WTT based on plane size

public:
    // Constructor:
    Plane(const string& callSign, int flightNumber,
          const string& size);

    // Methods
    string getCallSign() const;
    int getFlightNumber() const;
    string getSize() const;
    int getWakeTurbulenceTime() const;
    int getAtcID() const;

};

#endif