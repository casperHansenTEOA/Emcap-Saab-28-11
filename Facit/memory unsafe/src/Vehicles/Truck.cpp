#include "Truck.h"

Truck::Truck(const std::string& licensePlate) : vehicle(licensePlate, *new Location{0, 0}) {
    cargoWeights = new std::vector<double>(); // Dynamically allocate memory for cargo weights
}

std::string Truck::getLicensePlate(){
    return vehicle.getLicensePlate();
}

bool Truck::loadCargo(double weight){
    cargoWeights->push_back(weight); // Add weight to cargo weights
    return true;
}

bool Truck::unloadCargo(double weight){
    // Simulate unloading cargo by removing weight from cargo weights
    auto it = std::find(cargoWeights->begin(), cargoWeights->end(), weight);
    if (it != cargoWeights->end()) {
        cargoWeights->erase(it);
        return true;
    }
    return false;
}

double Truck::getCurrentCargoLoad() const{
    double totalWeight = 0.0;
    for (double weight : *cargoWeights) {
        totalWeight += weight;
    }
    return totalWeight;
}

bool Truck::move(){
    return vehicle.move();
}

bool Truck::stop(){
    return vehicle.stop();
}

Truck::~Truck(){
    // Memory leak: vehicle and cargoWeights are not deleted
}
