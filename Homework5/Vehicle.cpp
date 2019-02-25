#include <cmath>
#include <iomanip>
#include "Vehicle.h"

std::ostream &operator<<(std::ostream &out, const Vehicle &rhs) {
    return rhs.serialize(out);
}

std::ostream &Vehicle::serialize(std::ostream &out) const {
    return out << "Vehicle{year=" << getYear()
               << ", miles=" << getMiles()
               << ", value=$" << std::setprecision(2) << std::fixed << getValue()
               << ", value_date=" << getValueDate()
               << ", manufacturer=" << getManufacturer()
               << ", model=" << getModel()
               << "}";
}

/**
 * Uses default value of february 27, 2019 for date. Since days of the year are represented as a fraction,
 * we take 31 (the days of january) + 27 (the day of february we care about) and divide by the number of
 * days in a year.
 */
Vehicle::Vehicle() : Vehicle(2015, 55000, 20000, "Chevrolet", "Colorado", 2019 + (31 + 27) / 365.0f) {}

Vehicle::Vehicle(int year, int miles, double value, std::string manufacturer, std::string model, float value_date) :
        mYear(year), mMiles(miles), mValue(value), mManufacturer(std::move(manufacturer)), value_date(value_date),
        mModel(std::move(model)) {}

/**
 * Represents the rate that value decreases.
 */
const float depreciationRate = .85f;

void Vehicle::updateValue(float currentDate) {
    mValue = estimateValue(currentDate);
    value_date = currentDate;
}

float Vehicle::estimateValue(float date) const {
    return static_cast<float>(mValue * std::pow(depreciationRate, date - value_date));
}
