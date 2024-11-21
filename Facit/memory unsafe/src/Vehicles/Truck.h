#ifndef TRUCK_H
#define TRUCK_H

    #include <string>
#include <vector>
    #include "Vehicle.h"

/**
 * @brief Represents a truck, which is a type of vehicle.
 */
class Truck {
public:
    /**
     * @brief Constructs a Truck with the given license plate.
     * 
     * @param licensePlate The license plate of the truck.
     */
    Truck(const std::string& licensePlate);

    /**
     * @brief Gets the license plate of the truck.
     * 
     * @return The license plate of the truck.
     */
    std::string getLicensePlate();

   /**
     * @brief Loads cargo onto the truck.
     * 
     * @param weight The weight of the cargo to load.
     * @return True if the cargo was loaded successfully, false otherwise.
     */
    bool loadCargo(double weight);

    /**
     * @brief Unloads cargo from the truck.
     * 
     * @param weight The weight of the cargo to unload.
     * @return True if the cargo was unloaded successfully, false otherwise.
     */
    bool unloadCargo(double weight);

    /**
     * @brief Gets the current cargo load of the truck.
     * 
     * @return The current cargo load of the truck.
     */
    double getCurrentCargoLoad() const;



    /**
     * @brief Moves the truck.
     *
     * @return True if the truck is moved successfully, false otherwise.
     */
    bool move();


    /**
     * @brief stops the truck.
     *
     * @return True if the truck is stopped successfully, false otherwise.
     */

    bool stop();


        /**
     * @brief Gets the total distance traveled by the car.
     * @return The distance traveled by the car.
     */
    double getDistanceTraveled() const;

    Location getLocation() const;



    ~Truck();

private:
    Vehicle vehicle; ///< The vehicle object representing the truck.
    std::vector<double>* cargoWeights; ///< Pointer to a vector of cargo weights.
};
#endif // TRUCK_H