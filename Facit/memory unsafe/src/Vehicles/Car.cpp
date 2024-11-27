#include "Car.h"

Car::Car(const std::string& licensePlate) : vehicle(licensePlate, *new Location{0, 0}) {
    this->licensePlate = new std::string(licensePlate);
    // this->vehicle = Vehicle(licensePlate, {0, 0});

}

Car::~Car(){
    //TODO memory leak in the destructor does not delete the owned vehicle also lissence plate is useless
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

