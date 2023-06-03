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
            cout << "Car with name \"" << name << "\" not found.\n";
        }
    }

    void displayCars() {
        if (cars.empty()) {
            cout << "The list of cars is empty.\n";
            return;
        }

        for (const auto& car : cars) {
            cout << "Name: " << car.name << ", Year: " << car.year
                << ", Engine Volume: " << car.engineVolume
                << ", Price: " << car.price << "\n";
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
            cout << "Unable to open file: " << filename << "\n";
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
            cout << "Unable to open file: " << filename << "\n";
        }
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    CarDealer dealer;

    dealer.loadFromFile("cars.txt");

    while (true) {
        system("cls");
        cout << "Options:\n"
            << "0 - Exit\n"
            << "1 - Add car\n"
            << "2 - Remove car\n"
            << "3 - Display cars\n"
            << "4 - Sort by year\n"
            << "5 - Search by year\n"
            << "6 - Save to file\n"
            << "Enter your choice: ";

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

            cout << "Enter car details:\n";
            cout << "Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Year: ";
            cin >> year;
            cout << "Engine Volume: ";
            cin >> engineVolume;
            cout << "Price: ";
            cin >> price;

            Car car(name, year, engineVolume, price);
            dealer.addCar(car);
            cout << "Car successfully added.\n";
            break;
        }
        case 2: {
            string name;
            cout << "Enter the name of the car to remove: ";
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
            cout << "Cars sorted by year.\n";
            break;
        }
        case 5: {
            int year;
            cout << "Enter the year to search for: ";
            cin >> year;
            vector<Car> result = dealer.searchCarsByYear(year);
            cout << "Found cars:\n";
            for (const auto& car : result) {
                cout << "Name: " << car.name << ", Year: " << car.year
                    << ", Engine Volume: " << car.engineVolume
                    << ", Price: " << car.price << "\n";
            }
            break;
        }
        case 6: {
            dealer.saveToFile("cars.txt");
            cout << "Data saved to file.\n";
            break;
        }
        default: {
            cout << "Invalid choice. Please try again.\n";
            break;
        }
        }
        system("pause");
    }

    return 0;
}