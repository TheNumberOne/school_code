#include <iostream>
#include <cmath>

double promptDouble(const std::string& prompt){
    std::cout << prompt << ": ";
    double ret;
    std::cin >> ret;
    return ret;
}

static constexpr double PI = std::acos(-1);

double calculateWasherVolume(double innerRadius, double outerRadius, double height) {
    return (outerRadius * outerRadius - innerRadius * innerRadius) * PI * height;
}

int main() {
    auto r1 = promptDouble("Please give a value for inner radius in meters");
    auto r2 = promptDouble("Please give a value for outer radius in meters");
    auto height = promptDouble("Please give a value for height in meters");

    std::cout << "The volume of the washer is " << calculateWasherVolume(r1, r2, height) << " m^2." << std::endl;
    return 0;
}