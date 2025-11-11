#include "Garage.h"
#include <memory>
#include <vector>

Garage::Garage(){
    cars = std::vector<std::unique_ptr<Car>>();
    trucks = std::vector<std::unique_ptr<Truck>>();
}

void Garage::addCar(std::unique_ptr<Car> car){
        car->stop();
        cars.push_back(std::move(car));
};

void Garage::addTruck(std::unique_ptr<Truck> truck){
    truck->stop();
    trucks.push_back(std::move(truck));
};

 Car* Garage::takeCar(const std::string& licensePlate){
    for (std::unique_ptr<Car>& car : cars){
        if (car->getLicensePlate() == licensePlate){
            cars.erase(std::remove(cars.begin(), cars.end(), car), cars.end());
            
            car->move(Direction::North);
            return car.release(); // transfer ownership to caller
        }
    }
    return nullptr;
};

Truck* Garage::takeTruck(const std::string& licensePlate){
    for (std::unique_ptr<Truck>& truck : trucks){
        if (truck->getLicensePlate() == licensePlate){
            trucks.erase(std::remove(trucks.begin(), trucks.end(), truck), trucks.end());
            truck->move(Direction::North);
            return truck.release(); // transfer ownership to caller
        }
    }
    return nullptr;
};


 std::vector<Vehicle*> Garage::listVehicles() const{
    std::cout << "Cars in garage:\n";
    for (const auto& carPtr : this->cars) {
        if (carPtr) {
            std::cout << " - " << carPtr->getLicensePlate() << '\n';
        }
    }

    std::cout << "Trucks in garage:\n";
    for (const auto& truckPtr : this->trucks) {
        if (truckPtr) {
            std::cout << " - " << truckPtr->getLicensePlate() << '\n';
        }
    }

    return std::vector<Vehicle*>{};

};

