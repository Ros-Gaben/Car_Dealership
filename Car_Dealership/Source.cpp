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
            cout << "Автомобіль з назвою \"" << name << "\" не знайдено.\n";
        }
    }

    void displayCars() {
        if (cars.empty()) {
            cout << "Список автомобілів порожній.\n";
            return;
        }

        for (const auto& car : cars) {
            cout << "Назва: " << car.name << ", Рік: " << car.year
                << ", Об'єм двигуна: " << car.engineVolume
                << ", Ціна: " << car.price << "\n";
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
            cout << "Неможливо відкрити файл: " << filename << "\n";
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
            cout << "Неможливо відкрити файл: " << filename << "\n";
        }
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    CarDealer dealer;

    dealer.loadFromFile("cars.txt");

    while (true) {
        cout << "Опції:\n"
            << "0 - Вийти\n"
            << "1 - Додати автомобіль\n"
            << "2 - Видалити автомобіль\n"
            << "3 - Показати автомобілі\n"
            << "4 - Відсортувати за роком\n"
            << "5 - Пошук за роком\n"
            << "6 - Зберегти до файлу\n"
            << "Введіть свій вибір: ";

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

            cout << "Введіть дані про автомобіль:\n";
            cout << "Назва: ";
            cin.ignore();
            getline(cin, name);
            cout << "Рік: ";
            cin >> year;
            cout << "Об'єм двигуна: ";
            cin >> engineVolume;
            cout << "Ціна: ";
            cin >> price;

            Car car(name, year, engineVolume, price);
            dealer.addCar(car);
            cout << "Автомобіль успішно додано.\n";
            break;
        }
        case 2: {
            string name;
            cout << "Введіть назву автомобіля, який потрібно видалити: ";
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
            cout << "Автомобілі відсортовані за роком.\n";
            break;
        }
        case 5: {
            int year;
            cout << "Введіть рік для пошуку: ";
            cin >> year;
            vector<Car> result = dealer.searchCarsByYear(year);
            cout << "Знайдені автомобілі:\n";
            for (const auto& car : result) {
                cout << "Назва: " << car.name << ", Рік: " << car.year
                    << ", Об'єм двигуна: " << car.engineVolume
                    << ", Ціна: " << car.price << "\n";
            }
            break;
        }
        case 6: {
            dealer.saveToFile("cars.txt");
            cout << "Дані збережено до файлу.\n";
            break;
        }
        default: {
            cout << "Невірний вибір. Будь ласка, спробуйте ще раз.\n";
            break;
        }
        }
    }

    return 0;
}