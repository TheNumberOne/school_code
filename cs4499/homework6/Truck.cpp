#include <sstream>
#include "Truck.h"

std::ostream &Truck::serialize(std::ostream &out) const
{
    out << "Truck{";
    Vehicle::serialize(out);
    return out << ", awd=" << getAwd()
               << ", towingCapacity=" << getTowingCapacity()
               << "}";
}

Truck::Truck(
    int year, int miles, double value, const std::string &manufacturer, const std::string &model,
    float value_date, std::string awd, double towingCapacity
)
    : Vehicle(year, miles, value, manufacturer, model, value_date), mAwd(std::move(awd)),
      mTowingCapacity(towingCapacity) { }

std::string Truck::getName() const
{
    std::stringstream ss;
    ss << getYear() << " "
       << getManufacturer() << " "
       << getModel() << " "
       << getAwd();
    return ss.str();
}

void Truck::printTruck() const
{
    std::cout << getName();
}
