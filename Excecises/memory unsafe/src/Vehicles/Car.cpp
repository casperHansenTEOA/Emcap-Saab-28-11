#include "Car.h"

Car::Car(const std::string& licensePlate) : vehicle(licensePlate) {
    this->licensePlate = new std::string(licensePlate);
}

Car::~Car(){
    delete licensePlate;
}

bool Car::move(){
    return vehicle.move();
}

bool Car::stop(){
    return vehicle.stop();
}

std::string Car::getLicensePlate(){
    return vehicle.getLicensePlate();
}

