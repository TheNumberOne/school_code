#include <iostream>
#include <vector>
#include <iterator>
#include "Vehicle.h"
#include "Truck.h"

int main() {
    Vehicle defaultVehicle;
    std::cout << "Default vehicle: " << defaultVehicle << std::endl;

    defaultVehicle.setMiles(50000).setYear(2014);
    std::cout << "Set miles and year: " << defaultVehicle << std::endl;

    std::cout << std::endl;
    Vehicle myCar{2004, 190000, 2000, "Mazda", "6"};
    std::cout << "My car: " << myCar << std::endl;

    myCar.setManufacturer("Toyota").setModel("Camry").setValue(4321);
    std::cout << "Set manufacturer and model: " << myCar << std::endl;

    std::cout << std::endl;
    Truck defaultTruck;
    std::cout << "Default truck: " << defaultTruck << std::endl;
    std::cout << "Truck cast as vehicle: " << static_cast<Vehicle&>(defaultTruck) << std::endl;

    defaultTruck.setAwd("2wd").setTowingCapacity(200);
    std::cout << "Set all wheel drive and towing capacity: " << defaultTruck << std::endl;

    std::cout << std::endl;
    std::vector<Truck> trucks {
            {2019, 0, 28155, "Ford", "F-150", "4WD", 6500},
            {2007, 175962, 5400, "Chevrolet", "Silverado 1500 LS", "4WD", 5000},
            {2018, 5000, 32998, "Honda", "Ridgeline RTL-T", "AWD", 4250},
            {2016, 47000, 28998, "Dodge", "Ram 1500 Sport", "4x4", 6700},
            {2004, 180000, 29000, "Kenworth", "T2000", "rwd", 50000}
    };

    std::cout << "Trucks:" << std::endl;
    std::copy(trucks.begin(), trucks.end(), std::ostream_iterator<Truck>(std::cout, "\n"));

    return 0;
}