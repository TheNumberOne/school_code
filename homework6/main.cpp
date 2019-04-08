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
    float d = date(2019, 2, 6);
    std::vector<Truck> trucks{
            {2019, 0,      28155, "Ford",      "F-150",                  d,                "4WD", 6500},
            {2007, 175962, 5400,  "Chevrolet", "Silverado 1500 LS",      d,                "4WD", 5000},
            {2018, 5000,   32998, "Honda",     "Ridgeline RTL-T",        d,                "AWD", 4250},
            {2016, 47000,  28998, "Dodge",     "Ram 1500 Sport",         d,                "4x4", 6700},
            {2004, 180000, 29000, "Kenworth",  "T2000",                  d,                "rwd", 50000},
            {1986, 129500, 2600,  "Chevrolet", "Silverado C-10",         date(2019, 4, 4), "4WD", 1000},
            {1997, 122924, 5988,  "GMC",       "Sierra 1500 Ext Cab RB", date(2019, 4, 4), "RWD", 4000},
            {1976, 60191,  10900, "Jeep",      "CJ-7",                   date(2019, 4, 4), "4WD", 2000},
            {2000, 137511, 6500, "Toyota", "Tundra SR5", date(2019, 4, 4), "RWD", 7100},
            {1968, 31659, 12900, "Ford", "Ranchero", date(2019, 4, 4), "RWD", 0}
    };
    for (Truck &truck : trucks) {
        truck.updateValue(date(2019, 4, 8));
    }

    auto estimatedValues = estVal(trucks, date(2022, 4, 1));

    for (size_t i = 0; i < trucks.size(); i++) {
        std::cout << "Estimated value of " << trucks[i].getManufacturer() << " " << trucks[i].getModel() << ": $"
                  << std::setprecision(2) << std::fixed << estimatedValues[i] << std::endl;
    }

    return 0;
}