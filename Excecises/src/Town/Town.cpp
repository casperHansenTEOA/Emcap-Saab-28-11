#include "Town.h"


void Town::addCarPark(CarPark* carPark){
    carParks.push_back(carPark);
};


void Town::addCar(Car* car){
    cars.push_back(car);
};


void Town::addHuman(Human* human){
    humans.push_back(human);
};


void Town::addTruck(Truck* truck){
    trucks.push_back(truck);
};


void Town::addGarage(Garage* garage){
    garages.push_back(garage);
};


const std::vector<CarPark*>& Town::getCarParks() const{
    return carParks;
};


const std::vector<Car*>& Town::getCars() const{
    return cars;
};


const std::vector<Human*>& Town::getHumans() const{
    return humans;
};


const std::vector<Truck*>& Town::getTrucks() const{
    return trucks;
};


const std::vector<Garage*>& Town::getGarages() const{
    return garages;
};

Garage* Town::buildGarage(){ 
    Garage* garage = new Garage();
    return garage;
}





                
#include "Town.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>

void Town::run() {
    srand(static_cast<unsigned int>(time(0))); // Seed for random number generation

    while (true) {
        int action = rand() % 9; // Increase the range to accommodate new actions
        switch (action) {
            case 0:
                moveRandomCar();
                break;
            case 1:
                moveRandomTruck();
                break;
            case 2:
                humanInteractsWithCar();
                break;
            case 3:
                humanInteractsWithTruck();
                break;
            case 4:
                useRandomGarage();
                break;
            case 5:
                cloneRandomHuman();
                break;
            case 6: {
                std::vector<Car*> cars = buildNRandomCars(2);
                for (Car* car : cars) {
                    addCar(car);
                }
                break;
            }
            case 7:
                moveRandomCarToRandomLocation();
                break;
            case 8:
                moveRandomTruckToRandomLocation();
                break;
            case 9:
                parkVehicleInNearestCarPark();
                break;
            case 10:
                calculateDistanceBetweenRandomLocations();
                break;
        }
    }
}

void Town::moveRandomCarToRandomLocation() {
    if (cars.size() > 0) {
        int randomIndex = rand() % cars.size();
        Car* car = cars[randomIndex];
        Location newLocation = {static_cast<double>(rand() % 100), static_cast<double>(rand() % 100)};
        car->setLocation(newLocation);
        std::cout << "Moved car " << car->getLicensePlate() << " to new location (" << newLocation.x << ", " << newLocation.y << ")" << std::endl;
    }
}

void Town::moveRandomTruckToRandomLocation() {
    if (trucks.size() > 0) {
        int randomIndex = rand() % trucks.size();
        Truck* truck = trucks[randomIndex];
        Location newLocation = {static_cast<double>(rand() % 100), static_cast<double>(rand() % 100)};
        truck->setLocation(newLocation);
        std::cout << "Moved truck " << truck->getLicensePlate() << " to new location (" << newLocation.x << ", " << newLocation.y << ")" << std::endl;
    }
}

void Town::parkVehicleInNearestCarPark() {
    if (cars.size() > 0 && carParks.size() > 0) {
        int randomCarIndex = rand() % cars.size();
        Car* car = cars[randomCarIndex];
        Location carLocation = car->getLocation();
        CarPark* nearestCarPark = findNearestAvailableCarPark(carParks, carLocation);
        if (nearestCarPark != nullptr) {
            nearestCarPark->addCar(car);
            std::cout << "Parked car " << car->getLicensePlate() << " in nearest car park at location (" << nearestCarPark->getLocation().x << ", " << nearestCarPark->getLocation().y << ")" << std::endl;
        } else {
            std::cout << "No available car park found for car " << car->getLicensePlate() << std::endl;
        }
    }
}

void Town::calculateDistanceBetweenRandomLocations() {
    Location loc1 = {static_cast<double>(rand() % 100), static_cast<double>(rand() % 100)};
    Location loc2 = {static_cast<double>(rand() % 100), static_cast<double>(rand() % 100)};
    double distance = calculateDistance(loc1, loc2);
    std::cout << "Distance between (" << loc1.x << ", " << loc1.y << ") and (" << loc2.x << ", " << loc2.y << ") is " << distance << std::endl;
}


void Town::moveRandomCar(){
    if (cars.size() > 0){
        int randomIndex = rand() % cars.size();
        Car* car = cars[randomIndex];
        cars.erase(cars.begin() + randomIndex);
        cars.push_back(car);
    }
};


/**
    * @brief Moves a random truck in the town.
    */
void Town::moveRandomTruck(){
    if (trucks.size() > 0){
        int randomIndex = rand() % trucks.size();
        Truck* truck = trucks[randomIndex];
        trucks.erase(trucks.begin() + randomIndex);
        trucks.push_back(truck);
    }
};

/**
    * @brief A human interacts with a random car in the town.
    */
void Town::humanInteractsWithCar(){
    if (humans.size() > 0 && cars.size() > 0){
        int randomHumanIndex = rand() % humans.size();
        Human* human = humans[randomHumanIndex];
        int randomCarIndex = rand() % cars.size();
        Car* car = cars[randomCarIndex];
        human->purchaseCar(car->getLicensePlate());
    }
};


std::vector<Car*> Town::buildNRandomCars(int n){
    char * * licensePlates = new char * [n];

    for (int i = 0; i < n; ++i){
        licensePlates[i] = generateRandomLicensePlate();
    }

    std::vector<Car*> cars;

    for (int i = 0; i < n; ++i){
        Car* car = new Car(licensePlates[i]);
        cars.push_back(car);
    }

    return cars;
    
};

/**
    * @brief A human interacts with a random truck in the town.
    */
void Town::humanInteractsWithTruck(){
    if (humans.size() > 0 && trucks.size() > 0){
        int randomHumanIndex = rand() % humans.size();
        Human* human = humans[randomHumanIndex];
        int randomTruckIndex = rand() % trucks.size();
        Truck* truck = trucks[randomTruckIndex];
        human->purchaseTruck(truck->getLicensePlate());
    }
};


void Town::useRandomGarage(){
    if (garages.size() > 0){
        int randomIndex = rand() % garages.size();
        Garage* garage = garages[randomIndex];
        garage->listVehicles();
    }
};

void Town::cloneRandomHuman(){
    Human* human = new Human("Human" + std::to_string(humans.size()));
   
    if (humans.size() > 0){
        int randomIndex = rand() % humans.size();
        human = humans[randomIndex];
        human = human->clone();
        humans.push_back(human);
    }
};