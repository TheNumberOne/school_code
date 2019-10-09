//
// Created by thenumberone on 2/6/19.
//

#include "Vehicle.h"

std::ostream &operator<<(std::ostream &out, const Vehicle &rhs) {
    return rhs.serialize(out);
}

std::ostream &Vehicle::serialize(std::ostream &out) const {
    return out << "Vehicle{year=" << getYear()
               << ", miles=" << getMiles()
               << ", value=" << getValue()
               << ", manufacturer=" << getManufacturer()
               << ", model=" << getModel()
               << "}";
}
