#ifndef CAR_H
#define CAR_H

#include <algorithm>

#include <vector>   
#include "Vehicle.h"



/**
 * @brief Represents a car with a license plate, capable of moving and stopping.
 */
class Car {
public:
    /**
     * @brief Constructs a Car object with the given license plate.
     * @param licensePlate The license plate of the car.
     */
    Car(const std::string& licensePlate);

    /**
     * @brief Destroys the Car object.
     */
    ~Car();

    /**
     * @brief Moves the car to a new location.
     * @param direction The direction in which to move the car.
     * @return True if the car successfully moved, false otherwise.
     */
    bool move(Direction direction);

    /**
     * @brief Stops the car.
     * @return True if the car successfully stopped, false otherwise.
     */
    bool stop();

    /**
     * @brief Gets the license plate of the car.
     * @return The license plate of the car.
     */
    std::string getLicensePlate();

    /**
     * @brief Gets the total distance traveled by the car.
     * @return The distance traveled by the car.
     */
    double getDistanceTraveled() const;

    /**
     * @brief Gets the current location of the car.
     * @return The current location of the car.
     */
    Location getLocation() const;

    /**
     * @brief Sets the location of the car.
     * @param location The new location of the car.
     */

    void setLocation(Location location);

private:
    std::string* licensePlate; ///< The license plate of the car.

    Vehicle vehicle; ///< The vehicle associated with the car.
};

#endif // CAR_H