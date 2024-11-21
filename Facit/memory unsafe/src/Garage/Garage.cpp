#include "Garage.h"
#include <vector>

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


 std::vector<Vehicle*> Garage::listVehicles() const{
    std::vector <Car*> cars = this->cars;
    std::vector <Truck*> trucks = this->trucks;
    //stupid locatin pointer that doesnt make sense
    Location * location;

    std::vector<Vehicle *> vehicles;
    for (Car* car : cars){
        std::cout << "Car: " << car->getLicensePlate() << std::endl;
        location = new Location(car->getLocation().x, car->getLocation().y);
        vehicles.push_back(new Vehicle(car->getLicensePlate(), *location));
        
    }
    for (Truck* truck : trucks){
        std::cout << "Truck: " << truck->getLicensePlate() << std::endl;
        location = new Location(truck->getLocation().x, truck->getLocation().y);
        vehicles.push_back(new Vehicle(truck->getLicensePlate(), *location));
    }

    return vehicles;

};


//TODO a car starts moving when it is removed from the garage and stops when it is put back 

