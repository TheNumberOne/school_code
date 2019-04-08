#include "Truck.h"

std::ostream &Truck::serialize(std::ostream &out) const {
    out << "Truck{";
    Vehicle::serialize(out);
    return out << ", awd=" << getAwd()
               << ", towingCapacity=" << getTowingCapacity()
               << "}";
}

Truck::Truck(int year, int miles, double value, const std::string &manufacturer, const std::string &model,
             float value_date, std::string awd, double towingCapacity)
        : Vehicle(year, miles, value, manufacturer, model, value_date), mAwd(std::move(awd)),
          mTowingCapacity(towingCapacity) {}
