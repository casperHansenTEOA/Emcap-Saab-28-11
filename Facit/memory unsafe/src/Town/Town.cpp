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

Garage* buildGarage(){ // this is not memory safe because it returns a pointer to a new object that is not deleted
    Garage* garage = new Garage();
    return garage;
};


void Town::run(){
    while(true){
        int action = rand() % 5;
        switch(action){
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
        }
    }
};



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