/**
 * @file CarPark.cpp
 * @brief This file contains the implementation of a simple simulation of a town with cars, trucks, garages, and car parks.
 * 
 * The simulation includes classes for vehicles (Car and Truck), a Garage to store vehicles, a Human who owns vehicles and a garage, 
 * a CarPark to park vehicles, and a Town to manage all these entities. The simulation runs inifnitely in the Town class, 
 * during which random actions are performed, such as moving vehicles, interacting with vehicles, and using garages.
 */

#include <iostream>
#include "CarPark.h"

#include "../Location.h"

/**
 * @brief Generates a random license plate consisting of 3 letters followed by 3 digits.
 * 
 * @return A randomly generated license plate.
 */
char* generateRandomLicensePlate(){
    char* licensePlate = "";
    for (int i = 0; i < 3; ++i){
        licensePlate += 'A' + rand() % 26;
    }
    for (int i = 0; i < 3; ++i){
        licensePlate += '0' + rand() % 10;
    }
    return licensePlate;
};


bool CarPark::addCar(Car* car){
    if (currentCars < capacity){
        car->stop();
        cars.push_back(car);
        currentCars++;
        return true;
    }
    return false;
};


bool CarPark::addTruck(Truck* truck){
    if (currentCars < capacity){
        truck->stop();
        trucks.push_back(truck);
        currentCars++;
        return true;
    }
    return false;
};

bool CarPark::removeCar(const std::string& licensePlate){
    for (auto it = cars.begin(); it != cars.end(); ++it){
        if ((*it)->getLicensePlate() == licensePlate){
            Car *car = new Car(licensePlate);
            car = *it;
            cars.erase(it);
            car->move(Direction::North);
            currentCars--;
            return true;
        }
    }
    return false;
}

bool CarPark::removeTruck(const std::string& licensePlate){
    for (auto it = trucks.begin(); it != trucks.end(); ++it){
        if ((*it)->getLicensePlate() == licensePlate){
            Truck *truck = new Truck(licensePlate);
            truck = *it;
            trucks.erase(it);
            truck->move(Direction::North);
            currentCars--;
            return true;
        }
    }
    return false;
}

bool CarPark::parkVehicle(Vehicle* vehicle){
    if (Car* car = dynamic_cast<Car*>(vehicle)){ //TODO casting is cringe
        return addCar(car);
    } else if (Truck* truck = dynamic_cast<Truck*>(vehicle)){ //TODO casting is cringe
        return addTruck(truck);
    }
    return false;
}



void CarPark::assignCarToHuman(const std::string& humanName, const std::string& licensePlate){
    humanCarMap[humanName] = licensePlate;
};


std::string CarPark::getCarOfHuman(const std::string& humanName){
    if (humanCarMap.find(humanName) != humanCarMap.end()){
        return humanCarMap[humanName];
    }
    return "No car assigned";
};


const Location& CarPark::getLocation(){
    return location;
};




double calculateDistance(const Location& loc1, const Location& loc2){
    return sqrt(pow(loc1.x - loc2.x, 2) + pow(loc1.y - loc2.y, 2));
};


CarPark* findNearestAvailableCarPark(const std::vector<CarPark*>& carParks, const Location& currentLocation){
    CarPark* nearestCarPark = nullptr;
    double minDistance = std::numeric_limits<double>::max();
    for (CarPark* carPark : carParks){
        double distance = calculateDistance(currentLocation, carPark->getLocation());
        if (distance < minDistance && carPark->addCar(new Car(generateRandomLicensePlate()))){
            minDistance = distance;
            nearestCarPark = carPark;
        }
    }
    return nearestCarPark;
};






