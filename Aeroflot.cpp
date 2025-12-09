#include "Aeroflot.h"
#include <iostream>
#include <limits>

int Aeroflot::next_id = 1;

Aeroflot::Aeroflot() : id(next_id++), destination(""), flightNumber(0), airplaneType("") {}

Aeroflot::Aeroflot(const std::string &dest, int number, const std::string &type)
    : id(next_id++), destination(dest), flightNumber(number), airplaneType(type) {}

Aeroflot::Aeroflot(const Aeroflot &other)
    : id(next_id++), destination(other.destination), flightNumber(other.flightNumber), airplaneType(other.airplaneType) {}

void Aeroflot::setDestination(const std::string &dest) { destination = dest; }
void Aeroflot::setFlightNumber(int number) { flightNumber = number; }
void Aeroflot::setAirplaneType(const std::string &type) { airplaneType = type; }

std::string Aeroflot::getDestination() const { return destination; }
int Aeroflot::getFlightNumber() const { return flightNumber; }
std::string Aeroflot::getAirplaneType() const { return airplaneType; }

std::istream &operator>>(std::istream &in, Aeroflot &f)
{
    std::cout << "Введите пункт назначения рейса: ";
    std::getline(in >> std::ws, f.destination);
    if (f.destination.empty())
        throw MyException("Пустой пункт назначения");

    std::cout << "Введите номер рейса: ";
    if (!(in >> f.flightNumber))
        throw MyException("Неверный номер рейса");

    std::cout << "Введите тип самолета: ";
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(in, f.airplaneType);
    if (f.airplaneType.empty())
        throw MyException("Пустой тип самолета");

    return in;
}

std::ostream &operator<<(std::ostream &out, const Aeroflot &f)
{
    out << "ID рейса: " << f.id << "\n"
        << "Пункт назначения: " << f.destination << "\n"
        << "Номер рейса: " << f.flightNumber << "\n"
        << "Тип самолета: " << f.airplaneType << "\n";
    return out;
}
