// CLASS: Main Program (A2)
//
// Author: Alanna Morris, 7748195
//
// REMARKS: This program simulates an event system for plane takeoffs and landings.
//          Reads event data from the txt file and processes it using a simulation. 
//
//----------------------------------------
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Plane.h"
#include "Event.h"
#include "TakeoffEvent.h"
#include "LandingEvent.h"
#include "LinkedList.h"
#include "Simulation.h"

int main(int argc, char* argv[]) {
   if (argc != 3) {
      std::cerr << "Error: Program requires 2 arguments.\n";
      std::cerr << "Format: a2.exe <filename> <number of runways>\n";
      return 1;
   }

   std::string filename = argv[1]; // test.txt or any other plane event data here
   std::ifstream file(filename);
   if (!file.is_open()) {
       std::cerr << "Error: Unable to open file " << filename << "\n";
       return 1;
   }

   int numRunways; // user decides # of runways
   try {
       if ((numRunways = std::stoi(argv[2])) < 1) 
           throw std::invalid_argument("Invalid");
   } catch (...) {
       std::cerr << "Error: Runways must be a positive integer (>= 1).\n";
       return 1;
   }

   LinkedList eventList; // the event list of planes

   std::string line;
   while (std::getline(file, line)) { // read the file line by line
       std::stringstream sst(line);
       // Variables to Collect:
       int requestTime; 
       std::string callSign, flightNum, size, requestType;

       sst >> requestTime >> callSign >> flightNum >> size >> requestType; // take data from the line to make variables
       Plane* plane = new Plane(callSign, std::stoi(flightNum), size); // create plane object
       Event* event = nullptr; // create next event 

       if (requestType == "takeoff") {
           event = new TakeoffEvent(plane, requestTime, requestType); // (plane object, activity request time, type of activity)
       } else if (requestType == "landing") {
           event = new LandingEvent(plane, requestTime, requestType); 
       }

       if (event) { eventList.addBack(event); } // add to our event linked list
   }
   file.close();

   // Now that event list and number runways collected, pass data to Simulation:
   Simulation simulation(&eventList, numRunways);
   simulation.run(); // run the simulation 

   return 0;
}