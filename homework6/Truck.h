#include <utility>

#include <utility>

#include <utility>

#ifndef HOMEWORK4_TRUCK_H
#define HOMEWORK4_TRUCK_H


#include "Vehicle.h"

class Truck : public Vehicle {
public:
    Truck(int year, int miles, double value, const std::string &manufacturer, const std::string &model,
          float value_date, std::string awd,
          double towingCapacity);

    Truck() : Vehicle(), mAwd("4x4"), mTowingCapacity(5000) {}

    ~Truck() override = default;

    const std::string &getAwd() const { return mAwd; }

    Truck &setAwd(std::string awd) {
        mAwd = std::move(awd);
        return *this;
    }

    double getTowingCapacity() const { return mTowingCapacity; }

    Truck &setTowingCapacity(double towingCapacity) {
        mTowingCapacity = towingCapacity;
        return *this;
    }

    std::ostream &serialize(std::ostream &) const override;
    std::string getName() const;
    void printTruck() const;

private:
    std::string mAwd;
    double mTowingCapacity;
};



#endif //HOMEWORK4_TRUCK_H
