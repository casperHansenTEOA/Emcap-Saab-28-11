#include "Car.h"

Car::Car(const std::string& licensePlate) : vehicle(licensePlate) {
    this->licensePlate = new std::string(licensePlate);
}

Car::~Car(){
    //TODO memory leak in the destructor does not delete the owned vehicle also lissence plate is useless
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

