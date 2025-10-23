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
    std::vector<std::unique_ptr<Car>> cars = std::move(this->cars);
    std::vector<std::unique_ptr<Truck>> trucks = std::move(this->trucks);
    Location * location;

    std::vector<Vehicle*> vehicles;
    for (std::unique_ptr<Car>& car : cars){
        std::cout << "Car: " << car->getLicensePlate() << std::endl;
        location = new Location(car->getLocation().x, car->getLocation().y);
        vehicles.push_back(new Vehicle(car->getLicensePlate(), *location));
        
    }
    for (std::unique_ptr<Truck>& truck : trucks){
        std::cout << "Truck: " << truck->getLicensePlate() << std::endl;
        location = new Location(truck->getLocation().x, truck->getLocation().y);
        vehicles.push_back(new Vehicle(truck->getLicensePlate(), *location));
    }

    return vehicles;

};


//TODO a car starts moving when it is removed from the garage and stops when it is put back 

