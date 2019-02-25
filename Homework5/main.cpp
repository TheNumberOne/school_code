#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include "Vehicle.h"
#include "Truck.h"

std::vector<float> estVal(std::vector<Truck> const &trucks, float const &date) {
    std::vector<float> estimatedValues;
    std::transform(trucks.begin(), trucks.end(), std::back_inserter(estimatedValues),
                   [=](const Truck &truck) { return truck.estimateValue(date); });
    return estimatedValues;
}

float date(int year, int month, int day) {
    static std::vector<int> months{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    bool leapYear = year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);

    // Add the days of all the months before it. Subtract 1 because months is 0-indexed
    for (int i = 0; i < month - 1; i++) {
        day += months[i];

        // Add 1 for february on leap years
        if (leapYear && i == 1) day++;
    }

    // Subtract 1 so that Jan 1 has no fractional part in a year.
    return year + (day - 1) / (leapYear ? 366.0f : 365.0f);
}

int main() {
    int x;
    int y;
    int *p1 = &x;
    *p1 = 99;
    std::cout << "x: " << x << std::endl;
    std::cout << "x (through p1): " << *p1 << std::endl;
    p1 = &y;
    *p1 = -300;

    // July 1, 2015
    Truck chevy{2015, 0, 37000, "Chevrolet", "Colorado", date(2015, 7, 1), "4x4", 5000};
    chevy.updateValue(date(2019, 2, 27));

    std::cout << "Chevy Colorado's value after update: $"
              << std::setprecision(2) << std::fixed << chevy.getValue() << std::endl;
    std::cout << "Chevy Colorado's updated value date: " << chevy.getValueDate() << std::endl;

    float d = date(2019, 2, 6);
    std::vector<Truck> trucks{
            {2019, 0,      28155, "Ford",      "F-150",             d, "4WD", 6500},
            {2007, 175962, 5400,  "Chevrolet", "Silverado 1500 LS", d, "4WD", 5000},
            {2018, 5000,   32998, "Honda",     "Ridgeline RTL-T",   d, "AWD", 4250},
            {2016, 47000,  28998, "Dodge",     "Ram 1500 Sport",    d, "4x4", 6700},
            {2004, 180000, 29000, "Kenworth",  "T2000",             d, "rwd", 50000}
    };

    auto estimatedValues = estVal(trucks, date(2022, 4, 1));

    for (size_t i = 0; i < trucks.size(); i++) {
        std::cout << "Estimated value of " << trucks[i].getManufacturer() << " " << trucks[i].getModel() << ": $"
                  << std::setprecision(2) << std::fixed << estimatedValues[i] << std::endl;
    }

    return 0;
}