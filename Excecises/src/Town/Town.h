#ifndef TOWN_H
#define TOWN_H

#include "../CarPark/CarPark.h"
#include <vector>

/**
 * @brief Represents a town that manages cars, trucks, humans, garages, and car parks.
 */
class Town {
public:
    /**
     * @brief Adds a car park to the town.
     * 
     * @param carPark Pointer to the car park to be added.
     */
    void addCarPark(CarPark* carPark);

    /**
     * @brief Adds a car to the town.
     * 
     * @param car Pointer to the car to be added.
     */
    void addCar(Car* car);
    /**
     * @brief Adds a human to the town.
     * 
     * @param human Pointer to the human to be added.
     */
    void addHuman(Human* human);
    /**
     * @brief Adds a truck to the town.
     * 
     * @param truck Pointer to the truck to be added.
     */
    void addTruck(Truck* truck);

    /**
     * @brief Adds a garage to the town.
     * 
     * @param garage Pointer to the garage to be added.
     */
    void addGarage(Garage* garage);

    /**
     * @brief Gets the car parks in the town.
     * 
     * @return A vector of pointers to the car parks in the town.
     */
    const std::vector<CarPark*>& getCarParks() const;
    /**
     * @brief Gets the cars in the town.
     * 
     * @return A vector of pointers to the cars in the town.
     */
    const std::vector<Car*>& getCars() const;
    /**
     * @brief Gets the humans in the town.
     * 
     * @return A vector of pointers to the humans in the town.
     */
    const std::vector<Human*>& getHumans() const;
    /**
     * @brief Gets the trucks in the town.
     * 
     * @return A vector of pointers to the trucks in the town.
     */
    const std::vector<Truck*>& getTrucks() const;
    /**
     * @brief Gets the garages in the town.
     * 
     * @return A vector of pointers to the garages in the town.
     */
    const std::vector<Garage*>& getGarages() const;

    /**
     * @brief Builds a garage.
     * 
     * @return Pointer to the garage that was built.
     */
    Garage* buildGarage(); 



    /**
     * @brief Runs the simulation for a specified number of time steps, performing random actions.
     */
    void run();

private:
    std::vector<CarPark*> carParks; ///< Vector of pointers to car parks in the town.
    std::vector<Car*> cars; ///< Vector of pointers to cars in the town.
    std::vector<Human*> humans; ///< Vector of pointers to humans in the town.
    std::vector<Truck*> trucks; ///< Vector of pointers to trucks in the town.
    std::vector<Garage*> garages; ///< Vector of pointers to garages in the town.

    /**
     * @brief Moves a random car in the town.
     */
    void moveRandomCar();
    /**
     * @brief Moves a random truck in the town.
     */
    void moveRandomTruck();
    /**
     * @brief A human interacts with a random car in the town.
     */
    void humanInteractsWithCar();
    /**
     * @brief A human interacts with a random truck in the town.
     */
    void humanInteractsWithTruck();

    /**
     * @brief Uses a random garage in the town.
     */
    void useRandomGarage();

    /**
     * @brief clones a random human
     *
     */
    void cloneRandomHuman();

    /**
    * @birief builds n random cars
    *
     */
     std::vector<Car * >buildNRandomCars(int n);
};

#endif // TOWN_H