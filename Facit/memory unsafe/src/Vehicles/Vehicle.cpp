#include "Vehicle.h" 


Vehicle::Vehicle(const std::string& licensePlate){
    this->licensePlate = new std::string(licensePlate);
};

std::string Vehicle::getLicensePlate() const{
    return *licensePlate;
};


bool Vehicle::isMoving() const{
    return moving;
};

bool Vehicle::move(){
    if(moving){
        return false;
    }
    moving = true;
    return true;
};

bool Vehicle::stop(){
    if(!moving){
        return false;
    }
    moving = false;
    return true;
};
//TODO memory leak there is no destructor implementation