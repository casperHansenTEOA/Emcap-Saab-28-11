#ifndef HUMAN_H
#define HUMAN_H

#include "../Garage/Garage.h"
/**
 * @brief Represents a human who owns a garage and can purchase vehicles.
 */
class Human {
public:
    /**
     * @brief Constructs a Human with the given name.
     * 
     * @param name The name of the human.
     */
    Human(const std::string& name);

    /**
     * @brief Destructor for Human. 
     */ 
    ~Human();

    /**
     * @brief Purchases a car with the given license plate and adds it to the human's garage.
     * 
     * @param licensePlate The license plate of the car to be purchased.
     */
    void purchaseCar(const std::string& licensePlate);
    

    /**
     * @brief Purchases a truck with the given license plate and adds it to the human's garage.
     * 
     * @param licensePlate The license plate of the truck to be purchased.
     */
    void purchaseTruck(const std::string& licensePlate);

    /**
     * @brief Adds a car to the human's garage.
     * 
     * @param car Pointer to the car to be added.
     */
    void addCarToGarage(Car* car);
    /**
     * @brief Adds a truck to the human's garage.
     * 
     * @param truck Pointer to the truck to be added.
     */
    void addTruckToGarage(Truck* truck);

    /**
     * @brief Takes a car from the human's garage based on the license plate.
     * 
     * @param licensePlate The license plate of the car to be taken.
     * @return Pointer to the car if found, nullptr otherwise.
     */
    Car* takeCarFromGarage(const std::string& licensePlate);
    /**
     * @brief Takes a truck from the human's garage based on the license plate.
     * 
     * @param licensePlate The license plate of the truck to be taken.
     * @return Pointer to the truck if found, nullptr otherwise.
     */
    Truck* takeTruckFromGarage(const std::string& licensePlate);

    /**
     * @brief Lists all vehicles currently owned by the human.
     */
    void listOwnedVehicles() const;

    /**
     * @brief Gets the name of the human.
     * 
     * @return The name of the human.
     */
    std::string getName() const;    

private:
    std::string* name; ///< Pointer to the name string.
    Garage* garage; ///< Pointer to the garage owned by the human.
};
#endif  // HUMAN_H