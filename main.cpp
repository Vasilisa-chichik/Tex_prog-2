#include <iostream>
#include "Aeroflot.h"
#include "FlightManager.h"

void menu()
{
    std::cout << "1. Добавить рейс\n"
                 "2. Редактировать рейс\n"
                 "3. Удалить рейс\n"
                 "4. Показать все рейсы\n"
                 "5. Поиск по пункту назначения\n"
                 "6. Сохранить рейсы в файл\n"
                 "7. Загрузить рейсы из файла\n"
                 "0. Выход\n";
}

int main()
{
    FlightManager manager;
    while (true)
    {
        try
        {
            menu();
            int op;
            std::cin >> op;
            if (!std::cin)
            {
                std::cin.clear();
                std::string t;
                std::getline(std::cin, t);
                throw MyException("Ошибка ввода");
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (op == 0)
                break;
            else if (op == 1)
            {
                Aeroflot f;
                std::cin >> f;
                manager.addFlight(f);
            }
            else if (op == 2)
            {
                int pos;
                std::cout << "Введите индекс рейса для редактирования: ";
                std::cin >> pos;
                std::cin.ignore();
                manager.editAt(pos);
            }
            else if (op == 3)
            {
                int pos;
                std::cout << "Введите индекс рейса для удаления: ";
                std::cin >> pos;
                std::cin.ignore();
                manager.removeAt(pos);
            }
            else if (op == 4)
            {
                manager.printAll();
            }
            else if (op == 5)
            {
                std::string dest;
                std::cout << "Введите пункт назначения для поиска: ";
                std::getline(std::cin, dest);
                std::cout << "\n";
                manager.printByDestination(dest);
            }
            else if (op == 6)
            {
                std::string fname;
                std::cout << "Введите имя файла для сохранения: ";
                std::getline(std::cin, fname);
                manager.saveToFile(fname);
            }
            else if (op == 7)
            {
                std::string fname;
                std::cout << "Введите имя файла для загрузки: ";
                std::getline(std::cin, fname);
                manager.loadFromFile(fname);
            }
        }
        catch (const MyException &e)
        {
            std::cout << "Ошибка: " << e.what() << "\n";
        }
    }
    return 0;
}
