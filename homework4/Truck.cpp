#include "Truck.h"

std::ostream &Truck::serialize(std::ostream &out) const {
    out << "Truck{";
    Vehicle::serialize(out);
    return out << ", awd=" << getAwd()
               << ", towingCapacity=" << getTowingCapacity()
               << "}";
}
