#ifndef CARPARK_H
#define CARPARK_H
#include <unordered_map>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>
#include "../Vehicles/Car.h"
#include "../Vehicles/Truck.h"
#include "../Garage/Garage.h"
#include "../Human/Human.h"


/**
 * @brief Generates a random license plate consisting of 3 letters followed by 3 digits.
 * 
 * @return A randomly generated license plate.
 */
char* generateRandomLicensePlate();




/**
 * @brief Represents a car park with a specific location and capacity.
 */
class CarPark {
public:
    /**
     * @brief Constructs a CarPark with the given location and capacity.
     * 
     * @param location The location of the car park.
     * @param capacity The maximum number of vehicles the car park can hold.
     */
    CarPark(const Location& location, int capacity);

    /**
     * @brief Adds a car to the car park if there is space available.
     * 
     * @param car Pointer to the car to be added.
     * @return True if the car was added, false otherwise.
     */
    bool addCar(Car* car);

    /**
     * @brief Adds a truck to the car park if there is space available.
     * 
     * @param truck Pointer to the truck to be added.
     * @return True if the truck was added, false otherwise.
     */
    bool addTruck(Truck* truck);

    /**
     * @brief Removes a car from the car park based on the license plate.
     * 
     * @param licensePlate The license plate of the car to be removed.
     * @return True if the car was removed, false otherwise.
     */
    bool removeCar(const std::string& licensePlate);

    /**
     * @brief Removes a truck from the car park based on the license plate.
     * 
     * @param licensePlate The license plate of the truck to be removed.
     * @return True if the truck was removed, false otherwise.
     */
    bool removeTruck(const std::string& licensePlate);

    /**
     * @brief Parking a vehicle in the car park.
     *
     * @param vehicle Pointer to the vehicle to be parked.
     * @return True if the vehicle was parked, false otherwise.
     */

    bool parkVehicle(Vehicle* vehicle);



    /**
     * @brief Assigns a car to a human based on the human's name and the car's license plate.
     * 
     * @param humanName The name of the human.
     * @param licensePlate The license plate of the car.
     */
    void assignCarToHuman(const std::string& humanName, const std::string& licensePlate);

    /**
     * @brief Gets the license plate of the car assigned to a human based on the human's name.
     * 
     * @param humanName The name of the human.
     * @return The license plate of the car assigned to the human, or "No car assigned" if no car is assigned.
     */
    std::string getCarOfHuman(const std::string& humanName);

    /**
     * @brief Gets the location of the car park.
     * 
     * @return The location of the car park.
     */
    const Location& getLocation();

private:
    Location location; ///< The location of the car park.
    int capacity; ///< The maximum number of vehicles the car park can hold.
    int currentCars; ///< The current number of vehicles in the car park.
    std::vector<Car*> cars; ///< Vector of pointers to cars in the car park.
    std::vector<Truck*> trucks; ///< Vector of pointers to trucks in the car park.
    std::unordered_map<std::string, std::string> humanCarMap; ///< Map of human names to car license plates.
};

/**
 * @brief Calculates the distance between two locations.
 * 
 * @param loc1 The first location.
 * @param loc2 The second location.
 * @return The distance between the two locations.
 */
double calculateDistance(const Location& loc1, const Location& loc2);
/**
 * @brief Finds the nearest available car park to the current location.
 * 
 * @param carParks Vector of pointers to car parks.
 * @param currentLocation The current location.
 * @return Pointer to the nearest available car park, or nullptr if no car park is available.
 */
CarPark* findNearestAvailableCarPark(const std::vector<CarPark*>& carParks, const Location& currentLocation);

#endif // CARPARK_H