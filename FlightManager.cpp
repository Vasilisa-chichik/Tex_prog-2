#include "FlightManager.h"
#include <fstream>
#include <limits>
#include <iostream>
#include <string>

FlightManager::FlightManager() : arr(nullptr), capacity(0), count(0) { ensure_capacity(4); }
FlightManager::~FlightManager() { delete[] arr; }

void FlightManager::ensure_capacity(int c)
{
    if (capacity >= c)
        return;
    int nc = capacity ? capacity * 2 : 4;
    while (nc < c)
        nc *= 2;
    Aeroflot *na = new Aeroflot[nc];
    for (int i = 0; i < count; i++)
        na[i] = arr[i];
    delete[] arr;
    arr = na;
    capacity = nc;
}

void FlightManager::sortByFlightNumber()
{
    for (int i = 0; i < count - 1; i++)
        for (int j = 0; j < count - 1 - i; j++)
            if (arr[j + 1].getFlightNumber() < arr[j].getFlightNumber())
                std::swap(arr[j], arr[j + 1]);
}

void FlightManager::addFlight(const Aeroflot &f)
{
    ensure_capacity(count + 1);
    arr[count++] = f;
    sortByFlightNumber();
}

void FlightManager::editAt(int pos)
{
    if (pos < 0 || pos >= count)
        throw MyException("Неверная позиция");
    std::cout << "Редактирование самолета [" << pos << "]:\n"
              << arr[pos];
    Aeroflot tmp;
    std::cin >> tmp;
    arr[pos] = tmp;
    sortByFlightNumber();
}

void FlightManager::removeAt(int pos)
{
    if (pos < 0 || pos >= count)
        throw MyException("Неверная позиция");
    std::cout << "Удаление самолета [" << pos << "]:\n"
              << arr[pos] << "\n";
    for (int i = pos; i < count - 1; i++)
        arr[i] = arr[i + 1];
    count--;
}

Aeroflot FlightManager::getAt(int pos) const
{
    if (pos < 0 || pos >= count)
        throw MyException("Неверная позиция");
    return arr[pos];
}

void FlightManager::printAll() const
{
    if (count == 0)
    {
        std::cout << "Список рейсов пуст\n";
        return;
    }
    for (int i = 0; i < count; i++)
    {
        std::cout << "Самолет [" << i << "]\n"
                  << arr[i] << "\n";
    }
}

void FlightManager::printByDestination(const std::string &dest) const
{
    bool found = false;
    for (int i = 0; i < count; i++)
    {
        if (arr[i].getDestination() == dest)
        {
            std::cout << "Самолет [" << i << "]\n"
                      << "Номер рейса: " << arr[i].getFlightNumber() << "\n"
                      << "Тип самолета: " << arr[i].getAirplaneType() << "\n\n";

            found = true;
        }
    }
    if (!found)
        std::cout << "Рейсов с таким пунктом назначения нет\n";
}

void FlightManager::saveToFile(const std::string &filename) const
{
    std::ofstream out(filename);
    if (!out)
        throw MyException("Не удалось открыть файл для записи");

    out << count << "\n"; // количество рейсов
    for (int i = 0; i < count; i++)
    {
        out << arr[i].getDestination() << "|"
            << arr[i].getFlightNumber() << "|"
            << arr[i].getAirplaneType() << "\n";
    }
}

void FlightManager::loadFromFile(const std::string &filename)
{
    std::ifstream in(filename);
    if (!in)
        throw MyException("Не удалось открыть файл для чтения");

    int n;
    in >> n;
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    delete[] arr;
    arr = nullptr;
    capacity = 0;
    count = 0;
    ensure_capacity(n);

    for (int i = 0; i < n; i++)
    {
        std::string line;
        std::getline(in, line);
        if (line.empty())
        {
            i--;
            continue;
        }

        size_t p1 = line.find('|');
        size_t p2 = line.find('|', p1 + 1);

        std::string dest = line.substr(0, p1);
        int num = std::stoi(line.substr(p1 + 1, p2 - p1 - 1));
        std::string type = line.substr(p2 + 1);

        arr[count++] = Aeroflot(dest, num, type);
    }

    sortByFlightNumber();
}
