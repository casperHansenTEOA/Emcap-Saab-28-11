#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include "../Location.h"
#include "../Direction.h"

class Vehicle {
public:
    /**
     * @brief Constructs a Vehicle with the given license plate.
     * 
     * @param licensePlate The license plate of the vehicle.
     */
    Vehicle(const std::string& licensePlate, Location& location);

    
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
     * @param direction The direction in which the vehicle should move.
     *
     * @return True if the vehicle os moved successfully, false otherwise.
     */
    bool move(Direction direction); ;

    /**
     * @brief Stops the vehicle.
     *
     * @param True if the vehicle is stopped successfully, false otherwise.
     */
    bool stop();


    double calculateDistance(const Location& loc1, const Location& loc2) const;
    double getDistanceTraveled() const;
  
    Location getLocation() const;
    void setLocation(Location location);


    virtual ~Vehicle() = default; 


private:
    std::string* licensePlate; ///< Pointer to the license plate string.
    bool moving;
    Location* currentLocation;

};

#endif // VEHICLE_H