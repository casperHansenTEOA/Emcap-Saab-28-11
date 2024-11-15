#include "Town/Town.h"
#include <vector>

/**
 * @brief The main function that initializes the town and runs the simulation.
 * 
 * @return Exit status of the program.
 */
int main(){
   

    Town * town = new Town(); 
     //generates a bumch of random cars and car parks and garages and humans and traucks and runs the simulation
    for (int i = 0; i < 100; ++i) {
        // Create random cars
        Car* car = new Car(generateRandomLicensePlate());
        town->addCar(car);

        // Create random trucks
        Truck* truck = new Truck(generateRandomLicensePlate());
        town->addTruck(truck);

        // Create random humans
        Human* human = new Human("Human" + std::to_string(i));
        town->addHuman(human);



        // Create random garages that dont bleong to any human
        for (int j = 0; j < 10; ++j) {
                Garage * garage = town->buildGarage();
                town->addGarage(garage);
          
        }




        // Create random car parks
        Location location = {static_cast<double>(rand() % 100), static_cast<double>(rand() % 100)};
        CarPark* carPark = new CarPark(location, rand() % 50 + 1);
        town->addCarPark(carPark);


         // Human purchases a car and a truck
        human->purchaseCar(car->getLicensePlate());
        human->purchaseTruck(truck->getLicensePlate());

        // Human lists owned vehicles
        human->listOwnedVehicles();

        

       
    }

    town->run();
    return 0;

};