#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>

class Vehicle {
public:
    /**
     * @brief Constructs a Vehicle with the given license plate.
     * 
     * @param licensePlate The license plate of the vehicle.
     */
    Vehicle(const std::string& licensePlate);

    
    /**
     * @brief Gets the license plate of the vehicle.
     * 
     * @return The license plate of the vehicle.
     */
    std::string getLicensePlate() const;

    /**

     * @brief Gets the moving status of the vehicle.
     *
     * @return True if the vehicle is moving, false otherwise.
     */
    bool isMoving() const;

    /**
     * @brief Moves the vehicle.
     *
     * @param True if the vehicle os moved successfully, false otherwise.
     */
    bool move() throws std::runtime_error ;

    /**
     * @brief Stops the vehicle.
     *
     * @param True if the vehicle is stopped successfully, false otherwise.
     */
    bool stop();


    virtual ~Vehicle() = default; 


private:
    std::string* licensePlate; ///< Pointer to the license plate string.
    bool moving;
};

#endif // VEHICLE_H