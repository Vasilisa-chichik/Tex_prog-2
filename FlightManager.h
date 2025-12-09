#ifndef FLIGHTMANAGER_H
#define FLIGHTMANAGER_H

#include "Aeroflot.h"

class FlightManager
{
private:
    Aeroflot *arr;
    int capacity;
    int count;

    void ensure_capacity(int c);
    void sortByFlightNumber();

public:
    FlightManager();
    ~FlightManager();

    void addFlight(const Aeroflot &f);
    void removeAt(int pos);
    void editAt(int pos);
    Aeroflot getAt(int pos) const;
    void saveToFile(const std::string &filename) const;
    void loadFromFile(const std::string &filename);
    void printAll() const;
    void printByDestination(const std::string &dest) const;
};

#endif
