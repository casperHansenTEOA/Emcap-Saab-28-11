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

double Vehicle::calculateDistance(const Location& loc1, const Location& loc2) const{
    return sqrt(pow(loc1.x - loc2.x, 2) + pow(loc1.y - loc2.y, 2));
};

double Vehicle::getDistanceTraveled() const{
    return calculateDistance({0, 0}, *currentLocation);
};

Location Vehicle::getLocation() const{
    return *currentLocation;
};

void Vehicle::setLocation( Location location){
    this->currentLocation = &location;
};



