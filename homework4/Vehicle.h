#ifndef HOMEWORK4_VEHICLE_H
#define HOMEWORK4_VEHICLE_H


#include <utility>
#include <string>
#include <iostream>

class Vehicle {
public:
    Vehicle() : Vehicle(2015, 55000, 20000, "Chevrolet", "Colorado") {}
    virtual ~Vehicle() = default;

    Vehicle(int year, int miles, double value, std::string manufacturer, std::string model) :
            mYear(year), mMiles(miles), mValue(value), mManufacturer(std::move(manufacturer)),
            mModel(std::move(model)) {}

    Vehicle &setYear(int year) {
        mYear = year;
        return *this;
    }

    int getYear() const { return mYear; }

    Vehicle &setMiles(int miles) {
        mMiles = miles;
        return *this;
    }

    int getMiles() const { return mMiles; }

    Vehicle &setValue(double value) {
        mValue = value;
        return *this;
    }

    double getValue() const { return mValue; }

    Vehicle &setManufacturer(std::string manufacturer) {
        mManufacturer = std::move(manufacturer);
        return *this;
    }

    const std::string &getManufacturer() const { return mManufacturer; }

    Vehicle &setModel(std::string model) {
        mModel = std::move(model);
        return *this;
    }

    const std::string &getModel() const { return mModel; }

    virtual std::ostream &serialize(std::ostream&) const;

private:
    int mYear;
    int mMiles;
    double mValue;
    std::string mManufacturer;
    std::string mModel;
};

std::ostream& operator<<(std::ostream&, const Vehicle&);


#endif //HOMEWORK4_VEHICLE_H
