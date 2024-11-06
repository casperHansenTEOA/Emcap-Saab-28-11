#include "Human.h"
Human::Human(const std::string& name){
    this->name = new std::string(name);
    garage = new Garage();
};

Human::~Human(){
        //TODO Memory leak

};


void Human::purchaseCar(const std::string& licensePlate){
    Car* car = new Car(licensePlate);
    addCarToGarage(car);
}

void Human::purchaseTruck(const std::string& licensePlate){
    Truck* truck = new Truck(licensePlate);
    addTruckToGarage(truck);
};
    

void Human::addCarToGarage(Car* car){
    garage->addCar(car);
};

void Human::addTruckToGarage(Truck* truck){
    garage->addTruck(truck);
};

Car* Human::takeCarFromGarage(const std::string& licensePlate){
    return garage->takeCar(licensePlate);
};

Truck* Human::takeTruckFromGarage(const std::string& licensePlate){
    return garage->takeTruck(licensePlate);
};

void Human::listOwnedVehicles() const{
    garage->listVehicles();
};

std::string Human::getName() const{
    return *name;
};



