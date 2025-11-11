#include "Town/Town.h"
#include "MemoryTracker.h"
#include <iostream>
#include <memory>
#include <vector>

/**
 * @brief The main function that initializes the town and runs the simulation.
 * 
 * @return Exit status of the program.
 */
int main(){
    MemoryTracker::initialize("../../memory_log.csv");
   //all the things that go in a town

   // onödiga pekare
    // Car* car;
    // Truck* truck;
    // Garage* garage;
    // CarPark* carPark;
    // Human* human;

    std::cout << "Building town entities..." << std::endl;

     std::shared_ptr<Garage> garage;

    // denna behöver inte vara på heapen enbart stacken
    Town  town = Town(); 
     //generates a bumch of random cars and car parks and garages and humans and traucks and runs the simulation
    for (int i = 0; i < 100; ++i) {
        // Create random cars

        const char* licensePlate = generateRandomLicensePlate();

        std::unique_ptr<Car> car = std::make_unique<Car>(licensePlate);

        
        licensePlate = generateRandomLicensePlate();
        // Create random trucks
        std::unique_ptr<Truck> truck = std::make_unique<Truck>(licensePlate);
   
        // Create random humans
        std::unique_ptr<Human> human = std::make_unique<Human>("Human" + std::to_string(i));

        // make every other human own the same garage  seems like town and humans need to share garages as well
        if (i % 2 == 0) {
             garage = std::make_shared<Garage>();
            
        }
        human->addGarage(garage);
        std::cout << "Human " << human->getName() << " assigned garage." << std::endl;
        town.addGarage(garage);
   

        // Create random garages that dont belong to any human
        for (int j = 0; j < 10; ++j) {
               std::shared_ptr<Garage> garage = town.buildGarage();
                town.addGarage(garage);
          
        }

        // Create random car parks
        Location location = {static_cast<double>(rand() % 100), static_cast<double>(rand() % 100)};
        std::unique_ptr<CarPark> carPark = std::make_unique<CarPark>(location, rand() % 50 + 1);
        
        // Human purchases a car and a truck
        human->purchaseCar(car->getLicensePlate());
        human->purchaseTruck(truck->getLicensePlate());
        // Human lists owned vehicles
        human->listOwnedVehicles();

        //  Run all move in the end to avoid messing with pointers
        town.addTruck(std::move(truck));
        town.addCar(std::move(car));
        town.addCarPark(std::move(carPark));
        town.addHuman(std::move(human));
    }

    // no more deletes needed
    // delete car;
    // delete truck;
    // delete garage;
    // delete carPark;
    // delete human;

    std::cout << "Starting town simulation..." << std::endl;
    town.run();
    return 0;

};