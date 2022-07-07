#include "C:\Users\Chami\Stanford_Cpp_Class\organized_materials_and_my_code\my_lib\general_utils.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

// 3a)
template <typename T>
const T& findMax(const vector<T> &v, int (cmpFn)(const T&, const T&) = operatorCmp) {
    size_t max = 0;
    for (size_t i = 1; i < v.size(); i++) {
        if (cmpFn(v[i], v[max]) == 1) {
            max = i;
        }
    }
    return v[max];
}

// 3b) 
struct Car {
    string name;
    int weight;
    int numAirbags;
};

int compareCars(const Car &car1, const Car &car2);

int main() {
    vector<Car> cars;

    while (true) {
        cout << "Enter car name (RETURN to exit): ";
        Car c;
        getline(cin, c.name);
        if (c.name.empty()) {
            break;
        }
        cout << "Enter weight: ";
        cin >> c.weight;
        cout << "Enter no. airbags: ";
        cin >> c.numAirbags;
        cars.push_back(c);
        cin.ignore();
    }

    Car safest = findMax(cars, compareCars);
    cout << "Safest Car: " << safest.name << ' ' << safest.weight << ' ' << safest.numAirbags << endl;
    return 0;
}

int compareCars(const Car &car1, const Car &car2) {
    if (car1.numAirbags > car2.numAirbags || (car1.numAirbags == car2.numAirbags && car1.weight > car2.weight)) {
        return 1;
    }
    else if (car1.numAirbags < car2.numAirbags || (car1.numAirbags == car2.numAirbags && car1.weight < car2.weight)) {
        return -1;
    }
    return 0;
}



