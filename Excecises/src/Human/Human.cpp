#include "Human.h"
Human::Human(const std::string name){
    this->name = std::string(name);
    garage = std::make_shared<Garage>();
};


void Human::addGarage(std::shared_ptr<Garage> garage){
    this->garage = garage;
};
void Human::purchaseCar(const std::string licensePlate){
    std::unique_ptr<Car> car = std::make_unique<Car>(licensePlate);
    addCarToGarage(std::move(car));
}

void Human::purchaseTruck(const std::string licensePlate){
    std::unique_ptr<Truck> truck = std::make_unique<Truck>(licensePlate);
    addTruckToGarage(std::move(truck));
};
    

void Human::addCarToGarage(std::unique_ptr<Car> car){
    // moves the pointer ownership to the garage so its not lost
    garage->addCar(std::move(car));
};

void Human::addTruckToGarage(std::unique_ptr<Truck> truck){
    garage->addTruck(std::move(truck));
};

Car* Human::takeCarFromGarage(const std::string licensePlate){
    return garage->takeCar(licensePlate);
};

Truck* Human::takeTruckFromGarage(const std::string licensePlate){
    return garage->takeTruck(licensePlate);
};

void Human::listOwnedVehicles() const{
    garage->listVehicles();
};

std::string Human::getName() const{
    return name;
};

Human * Human::clone(){
    Human * clone = new Human(name);
    clone->garage = garage;
    return clone;
};



