#ifndef AEROFLOT_H
#define AEROFLOT_H

#include <iostream>
#include <string>

class MyException
{
    std::string msg;

public:
    MyException(const std::string &m) : msg(m) {}
    const char *what() const { return msg.c_str(); }
};

class Aeroflot
{
private:
    static int next_id;
    int id;
    std::string destination;
    int flightNumber;
    std::string airplaneType;

public:
    Aeroflot();
    Aeroflot(const std::string &dest, int number, const std::string &type);
    Aeroflot(const Aeroflot &other);
    ~Aeroflot() = default;

    void setDestination(const std::string &dest);
    void setFlightNumber(int number);
    void setAirplaneType(const std::string &type);

    std::string getDestination() const;
    int getFlightNumber() const;
    std::string getAirplaneType() const;

    friend std::istream &operator>>(std::istream &in, Aeroflot &f);
    friend std::ostream &operator<<(std::ostream &out, const Aeroflot &f);
};

#endif
