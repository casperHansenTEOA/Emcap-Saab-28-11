#include "Garage.h"

Garage::Garage(){
    cars = std::vector<Car*>();
    trucks = std::vector<Truck*>();
}

void Garage::addCar(Car* car){
        cars.push_back(car);
};

void Garage::addTruck(Truck* truck){
    trucks.push_back(truck);
};

 Car* Garage::takeCar(const std::string& licensePlate){
    for (Car* car : cars){
        if (car->getLicensePlate() == licensePlate){
            cars.erase(std::remove(cars.begin(), cars.end(), car), cars.end());
            return car;
        }
    }
    return nullptr;
};

Truck* Garage::takeTruck(const std::string& licensePlate){
    for (Truck* truck : trucks){
        if (truck->getLicensePlate() == licensePlate){
            trucks.erase(std::remove(trucks.begin(), trucks.end(), truck), trucks.end());
            return truck;
        }
    }
    return nullptr;
};


 void Garage::listVehicles() const{
    for (Car* car : cars){
        std::cout << "Car: " << car->getLicensePlate() << std::endl;
    }
    for (Truck* truck : trucks){
        std::cout << "Truck: " << truck->getLicensePlate() << std::endl;
    }
};


//TODO a car starts moving when it is removed from the garage and stops when it is put back 

Garage::~Garage(){
        //TODO memory leak
        //delete cars
        
    }

