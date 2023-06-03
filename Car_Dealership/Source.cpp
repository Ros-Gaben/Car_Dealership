#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <Windows.h>

using namespace std;

struct Car {
    string name;
    int year;
    double engineVolume;
    double price;

    Car(const string& n, int y, double ev, double p)
        : name(n), year(y), engineVolume(ev), price(p) {}

    bool operator==(const Car& other) const {
        return name == other.name && year == other.year && engineVolume == other.engineVolume && price == other.price;
    }
};

class CarDealer {
private:
    vector<Car> cars;

public:
    void addCar(const Car& car) {
        cars.push_back(car);
    }

    void removeCar(const string& name) {
        auto it = find_if(cars.begin(), cars.end(), [name](const Car& car) {
            return car.name == name;
            });

        if (it != cars.end()) {
            cars.erase(it);
        }
        else {
            cout << "��������� � ������ \"" << name << "\" �� ��������.\n";
        }
    }

    void displayCars() {
        if (cars.empty()) {
            cout << "������ ��������� �������.\n";
            return;
        }

        for (const auto& car : cars) {
            cout << "�����: " << car.name << ", г�: " << car.year
                << ", ��'�� �������: " << car.engineVolume
                << ", ֳ��: " << car.price << "\n";
        }
    }

    void sortCarsByYear() {
        sort(cars.begin(), cars.end(), [](const Car& a, const Car& b) {
            return a.year < b.year;
            });
    }

    vector<Car> searchCarsByYear(int targetYear) {
        vector<Car> result;
        copy_if(cars.begin(), cars.end(), back_inserter(result),
            [targetYear](const Car& car) {
                return car.year == targetYear;
            });
        return result;
    }

    void saveToFile(const string& filename) {
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto& car : cars) {
                file << car.name << "," << car.year << ","
                    << car.engineVolume << "," << car.price << "\n";
            }
            file.close();
        }
        else {
            cout << "��������� ������� ����: " << filename << "\n";
        }
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            cars.clear();
            string line;
            while (getline(file, line)) {
                istringstream iss(line);
                string name;
                int year;
                double engineVolume, price;
                if (getline(iss, name, ',') &&
                    iss >> year &&
                    iss.ignore() &&
                    iss >> engineVolume &&
                    iss.ignore() &&
                    iss >> price) {
                    cars.emplace_back(name, year, engineVolume, price);
                }
            }
            file.close();
        }
        else {
            cout << "��������� ������� ����: " << filename << "\n";
        }
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    CarDealer dealer;

    dealer.loadFromFile("cars.txt");

    while (true) {
        cout << "�����:\n"
            << "0 - �����\n"
            << "1 - ������ ���������\n"
            << "2 - �������� ���������\n"
            << "3 - �������� ��������\n"
            << "4 - ³���������� �� �����\n"
            << "5 - ����� �� �����\n"
            << "6 - �������� �� �����\n"
            << "������ ��� ����: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 0: {
            return 0;
        }
        case 1: {
            string name;
            int year;
            double engineVolume, price;

            cout << "������ ��� ��� ���������:\n";
            cout << "�����: ";
            cin.ignore();
            getline(cin, name);
            cout << "г�: ";
            cin >> year;
            cout << "��'�� �������: ";
            cin >> engineVolume;
            cout << "ֳ��: ";
            cin >> price;

            Car car(name, year, engineVolume, price);
            dealer.addCar(car);
            cout << "��������� ������ ������.\n";
            break;
        }
        case 2: {
            string name;
            cout << "������ ����� ���������, ���� ������� ��������: ";
            cin.ignore();
            getline(cin, name);
            dealer.removeCar(name);
            break;
        }
        case 3: {
            dealer.displayCars();
            break;
        }
        case 4: {
            dealer.sortCarsByYear();
            cout << "�������� ���������� �� �����.\n";
            break;
        }
        case 5: {
            int year;
            cout << "������ �� ��� ������: ";
            cin >> year;
            vector<Car> result = dealer.searchCarsByYear(year);
            cout << "������� ��������:\n";
            for (const auto& car : result) {
                cout << "�����: " << car.name << ", г�: " << car.year
                    << ", ��'�� �������: " << car.engineVolume
                    << ", ֳ��: " << car.price << "\n";
            }
            break;
        }
        case 6: {
            dealer.saveToFile("cars.txt");
            cout << "��� ��������� �� �����.\n";
            break;
        }
        default: {
            cout << "������� ����. ���� �����, ��������� �� ���.\n";
            break;
        }
        }
    }

    return 0;
}