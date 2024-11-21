#include "Vehicle.h" 



// turn a direction into a location
Location directionToLocation(Direction direction){
    switch (direction){
        case Direction::North:
            return {0, 1};
        case Direction::East:
            return {1, 0};
        case Direction::South:
            return {0, -1};
        case Direction::West:
            return {-1, 0};
    }
    return {0, 0};
};


Vehicle::Vehicle(const std::string& licensePlate, Location& location)
{
    this->licensePlate = new std::string(licensePlate);
    // location being a pointer is stupid
    this->currentLocation = &location;
};

std::string Vehicle::getLicensePlate() const{
    return *licensePlate;
};


bool Vehicle::isMoving() const{
    return moving;
};

bool Vehicle::move(Direction direction){
    if(moving){
        return false;
    }
    
    // this overwrites the location pointer with a new location pointer that is not deleted memory leak
    currentLocation = currentLocation->add(*this->currentLocation, directionToLocation(direction));
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