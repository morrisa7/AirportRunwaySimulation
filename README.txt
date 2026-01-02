Airport Event-Driven Simulation

Description:
This project runs an airport runway simulation. 
It coordinates takeoff & landing events across multiple runways. 


Instructions:
1. All files should have object files but if not,
compile all source files into object files.

g++ -c Plane.cpp -o Plane.o
g++ -c TakeoffEvent.cpp -o TakeoffEvent.o
g++ -c LandingEvent.cpp -o LandingEvent.o
g++ -c Event.cpp -o Event.o
g++ -c Node.cpp -o Node.o
g++ -c LinkedList.cpp -o LinkedList.o
g++ -c Simulation.cpp -o Simulation.o
g++ -c Runway.cpp -o Runway.o
g++ -c RunwayManager.cpp -o RunwayManager.o

2. Link all object files with teh main program a2.cpp

g++ a2.cpp Plane.o TakeoffEvent.o LandingEvent.o Event.o Node.o LinkedList.o Simulation.o Runway.o RunwayManager.o -o a2.exe

3. Run the simulation program with the given input file and the number of runways

./a2.exe [input_file] [number_of_runways]

Or for Example:

Simulate with 1 runway
./a2.exe test.txt 1

Simulate with 2 runways
./a2.exe test.txt 2