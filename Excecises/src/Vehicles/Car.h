#ifndef CAR_H
#define CAR_H

#include "Vehicle.h"
/**
 * @brief Represents a car, which is a type of vehicle.
 */
class Car {
public:
    /**
     * @brief Constructs a Car with the given license plate.
     * 
     * @param licensePlate The license plate of the car.
     */
    Car(const std::string& licensePlate);

    /**
     * @brief Gets the license plate of the car.
     * 
     * @return The license plate of the car.
     */
    std::string getLicensePlate();

    /**
     * @brief Moves the car.
     *
     * @return True if the car is moved successfully, false otherwise.
     */
    bool move();


    /**
     * @brief stops the car.
     *
     * @return True if the car is stopped successfully, false otherwise.
     */

    bool stop();

    /**
     * @brief Destructor for Car.
     */
    ~Car();
private:
    Vehicle vehicle; ///< The vehicle object representing the car.
    std::string* licensePlate;
};
#endif // CAR_H