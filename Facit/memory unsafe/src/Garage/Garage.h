#ifndef GARAGE_H
#define GARAGE_H

#include "../Vehicles/Car.h"
#include "../Vehicles/Truck.h"
#include <vector>
#include <algorithm>
#include <iostream>

/**
 * @brief Represents a garage that can store cars and trucks.
 */
class Garage {
public:

    Garage();

    
    /**
     * @brief Adds a car to the garage.
     * 
     * @param car Pointer to the car to be added.
     */
    void addCar(Car* car);

    /**
     * @brief Adds a truck to the garage.
     * 
     * @param truck Pointer to the truck to be added.
     */
    void addTruck(Truck* truck);
    /**
     * @brief Takes a car from the garage based on the license plate.
     * 
     * @param licensePlate The license plate of the car to be taken.
     * @return Pointer to the car if found, nullptr otherwise.
     */
    Car* takeCar(const std::string& licensePlate);
    /**
     * @brief Takes a truck from the garage based on the license plate.
     * 
     * @param licensePlate The license plate of the truck to be taken.
     * @return Pointer to the truck if found, nullptr otherwise.
     */
    Truck* takeTruck(const std::string& licensePlate);

    /**
     * @brief Lists all vehicles currently in the garage.
     */
    void listVehicles() const;

    ~Garage();

private:
    std::vector<Car*> cars; ///< Vector of pointers to cars in the garage.
    std::vector<Truck*> trucks; ///< Vector of pointers to trucks in the garage.
};
#endif // GARAGE_H