#ifndef TOWN_H
#define TOWN_H

#include "../CarPark/CarPark.h"
#include <memory>
#include <vector>
#include <cstddef>

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
    void addCarPark(std::unique_ptr<CarPark>carPark);

    /**
     * @brief Adds a car to the town.
     * 
     * @param car Pointer to the car to be added.
     */
    void addCar(std::unique_ptr<Car> car);
    /**
     * @brief Adds a human to the town.
     * 
     * @param human Pointer to the human to be added.
     */
    void addHuman(std::unique_ptr<Human> human);
    /**
     * @brief Adds a truck to the town.
     * 
     * @param truck Pointer to the truck to be added.
     */
    void addTruck(std::unique_ptr<Truck> truck);

    /**
     * @brief Adds a garage to the town.
     * 
     * @param garage Pointer to the garage to be added.
     */
    void addGarage(std::shared_ptr<Garage> garage);

    /**
     * @brief Gets the car parks in the town.
     * 
     * @return A vector of pointers to the car parks in the town.
     */
    const std::vector<std::unique_ptr<CarPark>>& getCarParks() const;
    /**
     * @brief Gets the cars in the town.
     * 
     * @return A vector of pointers to the cars in the town.
     */
    const std::vector<std::unique_ptr<Car>>& getCars() const;
    /**
     * @brief Gets the humans in the town.
     * 
     * @return A vector of pointers to the humans in the town.
     */
    const std::vector<std::unique_ptr<Human>>& getHumans() const;
    /**
     * @brief Gets the trucks in the town.
     * 
     * @return A vector of pointers to the trucks in the town.
     */
    const std::vector<std::unique_ptr<Truck>>& getTrucks() const;
    /**
     * @brief Gets the garages in the town.
     * 
     * @return A vector of pointers to the garages in the town.
     */
    const std::vector<std::shared_ptr<Garage>>& getGarages() const;

    /**
     * @brief Builds a garage.
     * 
     * @return Pointer to the garage that was built.
     */
    std::shared_ptr<Garage> buildGarage();



    /**
     * @brief Runs the simulation for a specified number of time steps, performing random actions.
     */
    void run();

    /**
     * @brief Prints a snapshot of the town for the given rotation.
     *
     * @param rotation Sequential number of the simulation step.
     */
    void printState(std::size_t rotation) const;

private:
    std::vector<std::unique_ptr<CarPark>> carParks; ///< Vector of pointers to car parks in the town.
    std::vector<std::unique_ptr<Car>> cars; ///< Vector of pointers to cars in the town.
    std::vector<std::unique_ptr<Human>> humans; ///< Vector of pointers to humans in the town.
    std::vector<std::unique_ptr<Truck>> trucks; ///< Vector of pointers to trucks in the town.
    std::vector<std::shared_ptr<Garage>> garages; ///< Vector of pointers to garages in the town. (shared with humans)

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
     std::vector<std::unique_ptr<Car>> buildNRandomCars(int n);

    void moveRandomCarToRandomLocation();
    void moveRandomTruckToRandomLocation();
    void parkVehicleInNearestCarPark();
    void calculateDistanceBetweenRandomLocations();
};

#endif // TOWN_H