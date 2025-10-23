#include "Town/Town.h"
#include "MemoryTracker.h"
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

    // denna behöver inte vara på heapen enbart stacken
    Town  town = Town(); 
     //generates a bumch of random cars and car parks and garages and humans and traucks and runs the simulation
    for (int i = 0; i < 100; ++i) {
        // Create random cars
        char* licensePlate = generateRandomLicensePlate();

        Car* car = new Car(licensePlate);  // changed to in scope 

        town.addCar(car); // change from arrows to dots since town is not a pointer now

        licensePlate = generateRandomLicensePlate();
        // Create random trucks
        Truck* truck = new Truck(licensePlate);
        town.addTruck(truck);

        // Create random humans
        Human* human = new Human("Human" + std::to_string(i));
        town.addHuman(human);

        // make every other human own the same garage
        if (i % 2 == 0) {
            garage = new Garage();
            human->addGarage(garage);
            town->addGarage(garage);
        }

        // Create random garages that dont belong to any human
        for (int j = 0; j < 10; ++j) {
               Garage* garage = town.buildGarage();
                town.addGarage(garage);
          
        }

        // Create random car parks
        Location location = {static_cast<double>(rand() % 100), static_cast<double>(rand() % 100)};
        CarPark* carPark = new CarPark(location, rand() % 50 + 1);
        town.addCarPark(carPark);
        // Human purchases a car and a truck
        human->purchaseCar(car->getLicensePlate());
        human->purchaseTruck(truck->getLicensePlate());
        // Human lists owned vehicles
        human->listOwnedVehicles();
    }

    // no more deletes needed
    // delete car;
    // delete truck;
    // delete garage;
    // delete carPark;
    // delete human;


    town.run();
    return 0;

};