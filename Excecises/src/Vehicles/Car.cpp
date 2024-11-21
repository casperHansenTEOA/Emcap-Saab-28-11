#include "Car.h"

Car::Car(const std::string& licensePlate) : vehicle(licensePlate, *new Location{0, 0}) {
    this->licensePlate = new std::string(licensePlate);
    // this->vehicle = Vehicle(licensePlate, {0, 0});

}

Car::~Car(){
    delete licensePlate;
}

bool Car::move(Direction direction){
    return vehicle.move(direction);
}

bool Car::stop(){
    return vehicle.stop();
}

std::string Car::getLicensePlate(){
    return vehicle.getLicensePlate();
}

double Car::getDistanceTraveled() const {
    return this->vehicle.calculateDistance({0, 0}, this->vehicle.getLocation());
}

Location Car::getLocation() const {
    return this->vehicle.getLocation();
}

void Car::setLocation(Location location) {
    this->vehicle.setLocation(location);
}