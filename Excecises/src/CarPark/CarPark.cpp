/**
 * @file CarPark.cpp
 * @brief This file contains the implementation of a simple simulation of a town with cars, trucks, garages, and car parks.
 * 
 * The simulation includes classes for vehicles (Car and Truck), a Garage to store vehicles, a Human who owns vehicles and a garage, 
 * a CarPark to park vehicles, and a Town to manage all these entities. The simulation runs inifnitely in the Town class, 
 * during which random actions are performed, such as moving vehicles, interacting with vehicles, and using garages.
 */

#include <iostream>
#include <limits>
#include <memory>
#include "CarPark.h"

#include "../Location.h"

CarPark::CarPark(const Location& location, int capacity)
    : location(location), capacity(capacity), currentCars(0) {}

/**
 * @brief Generates a random license plate consisting of 3 letters followed by 3 digits.
 * 
 * @return A randomly generated license plate.
 */
const char* generateRandomLicensePlate(){
    static char licensePlate[7];
    for (int i = 0; i < 3; ++i){
        licensePlate[i] = static_cast<char>('A' + rand() % 26);
    }
    for (int i = 0; i < 3; ++i){
        licensePlate[3 + i] = static_cast<char>('0' + rand() % 10);
    }
    licensePlate[6] = '\0';
    return licensePlate;
};


bool CarPark::addCar(std::unique_ptr<Car> car){
    if (currentCars < capacity){
        car->stop();
        cars.push_back(std::move(car));
        currentCars++;
        return true;
    }
    return false;
};


bool CarPark::addTruck(std::unique_ptr<Truck>truck){
    if (currentCars < capacity){
        truck->stop();
        trucks.push_back(truck);
        currentCars++;
        return true;
    }
    return false;
};

bool CarPark::removeCar(const std::string licensePlate){
    for (auto it = cars.begin(); it != cars.end(); ++it){
        std::unique_ptr<Car>& car = *it;
        if ((car)->getLicensePlate() == licensePlate){
            // throwaway new  here which is a memory leak
            cars.erase(it);
            car->move(Direction::North);
            currentCars--;
            return true;
        }
    }
    return false;
}

bool CarPark::removeTruck(const std::string licensePlate){
    for (auto it = trucks.begin(); it != trucks.end(); ++it){
        std::unique_ptr<Truck>& truck = *it;
        if ((truck)->getLicensePlate() == licensePlate){
            // throwaway new  here which is a memory leak
            trucks.erase(it);
            truck->move(Direction::North);
            currentCars--;
            return true;
        }
    }
    return false;
}

bool CarPark::parkVehicle(std::unique_ptr<Vehicle> vehicle){
    if (Car* car_ptr = dynamic_cast<Car*>(vehicle.get())){
        vehicle.release(); // release ownership from the original unique_ptr
        return addCar(std::unique_ptr<Car>(car_ptr));
    } else if (Truck* truck_ptr = dynamic_cast<Truck*>(vehicle.get())){
        vehicle.release(); // release ownership from the original unique_ptr
        return addTruck(std::unique_ptr<Truck>(truck_ptr));
    }
    return false;
}



void CarPark::assignCarToHuman(const std::string humanName, const std::string licensePlate){
    humanCarMap[humanName] = licensePlate;
};


std::string CarPark::getCarOfHuman(const std::string& humanName){
    if (humanCarMap.find(humanName) != humanCarMap.end()){
        return humanCarMap[humanName];
    }
    return "No car assigned";
};


const Location& CarPark::getLocation() const{
    return location;
};

int CarPark::getCapacity() const {
    return capacity;
}

int CarPark::getCurrentLoad() const {
    return currentCars;
}

bool CarPark::hasSpace() const {
    return currentCars < capacity;
}




double calculateDistance(const Location& loc1, const Location& loc2){
    return sqrt(pow(loc1.x - loc2.x, 2) + pow(loc1.y - loc2.y, 2));
};


std::unique_ptr<CarPark> findNearestAvailableCarPark(const std::vector<std::unique_ptr<CarPark>>& carParks, const Location& currentLocation){
    CarPark* nearest = nullptr;
    double minDistance = std::numeric_limits<double>::max();
    for (const std::unique_ptr<CarPark>& carPark : carParks){
        double distance = calculateDistance(currentLocation, carPark->getLocation());
        if (distance < minDistance && carPark->hasSpace()){
            minDistance = distance;
            nearest = carPark.get();
        }
    }
    return std::unique_ptr<CarPark>(nearest);
};






