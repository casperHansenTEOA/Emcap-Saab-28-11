// /**
//  * @file CarPark.cpp
//  * @brief This file contains the implementation of a simple simulation of a town with cars, trucks, garages, and car parks.
//  * 
//  * The simulation includes classes for vehicles (Car and Truck), a Garage to store vehicles, a Human who owns vehicles and a garage, 
//  * a CarPark to park vehicles, and a Town to manage all these entities. The simulation runs inifnitely in the Town class, 
//  * during which random actions are performed, such as moving vehicles, interacting with vehicles, and using garages.
//  */

// #include <iostream>
// #include <unordered_map>
// #include <string>
// #include <vector>
// #include <cmath>
// #include <cstdlib>
// #include "Vehicle.h"

// /**
//  * @brief Generates a random license plate consisting of 3 letters followed by 3 digits.
//  * 
//  * @return A randomly generated license plate.
//  */
// std::string generateRandomLicensePlate(){
//     std::string licensePlate = "";
//     for (int i = 0; i < 3; ++i){
//         licensePlate += 'A' + rand() % 26;
//     }
//     for (int i = 0; i < 3; ++i){
//         licensePlate += '0' + rand() % 10;
//     }
//     return licensePlate;
// };


// /**
//  * @brief Represents a car, which is a type of vehicle.
//  */
// class Car {
// public:
//     /**
//      * @brief Constructs a Car with the given license plate.
//      * 
//      * @param licensePlate The license plate of the car.
//      */
//     Car(const std::string& licensePlate) : vehicle(licensePlate) {}

//     /**
//      * @brief Gets the license plate of the car.
//      * 
//      * @return The license plate of the car.
//      */
//     std::string getLicensePlate(){
//         return vehicle.getLicensePlate();
//     };

//     ~Car(){
//         //TODO memory leak in the destructor does not delete the owned vehicle also lissence plate is useless
//         delete licensePlate;
//     }

// private:
//     Vehicle vehicle; ///< The vehicle object representing the car.
//     char* licensePlate; //TODO dulicate licensePlate
// };

// /**
//  * @brief Represents a truck, which is a type of vehicle.
//  */
// class Truck {
// public:
//     /**
//      * @brief Constructs a Truck with the given license plate.
//      * 
//      * @param licensePlate The license plate of the truck.
//      */
//     Truck(const std::string& licensePlate) : vehicle(licensePlate) {}

//     /**
//      * @brief Gets the license plate of the truck.
//      * 
//      * @return The license plate of the truck.
//      */
//     std::string getLicensePlate(){
//         return vehicle.getLicensePlate();
//     }

//     ~Truck(){
//         delete &vehicle;
//     }

// private:
//     Vehicle vehicle; ///< The vehicle object representing the truck.
// };

// /**
//  * @brief Represents a garage that can store cars and trucks.
//  */
// class Garage {
// public:
//     /**
//      * @brief Adds a car to the garage.
//      * 
//      * @param car Pointer to the car to be added.
//      */
//     void addCar(Car* car){
//         cars.push_back(car);
//     };

//     /**
//      * @brief Adds a truck to the garage.
//      * 
//      * @param truck Pointer to the truck to be added.
//      */
//     void addTruck(Truck* truck){
//         trucks.push_back(truck);
//     };
//     /**
//      * @brief Takes a car from the garage based on the license plate.
//      * 
//      * @param licensePlate The license plate of the car to be taken.
//      * @return Pointer to the car if found, nullptr otherwise.
//      */
//     Car* takeCar(const std::string& licensePlate){
//         for (Car* car : cars){
//             if (car->getLicensePlate() == licensePlate){
//                 cars.erase(std::remove(cars.begin(), cars.end(), car), cars.end());
//                 return car;
//             }
//         }
//         return nullptr;
//     };

//     /**
//      * @brief Takes a truck from the garage based on the license plate.
//      * 
//      * @param licensePlate The license plate of the truck to be taken.
//      * @return Pointer to the truck if found, nullptr otherwise.
//      */
//     Truck* takeTruck(const std::string& licensePlate){
//         for (Truck* truck : trucks){
//             if (truck->getLicensePlate() == licensePlate){
//                 trucks.erase(std::remove(trucks.begin(), trucks.end(), truck), trucks.end());
//                 return truck;
//             }
//         }
//         return nullptr;
//     };

//     /**
//      * @brief Lists all vehicles currently in the garage.
//      */
//     void listVehicles() const{
//         for (Car* car : cars){
//             std::cout << "Car: " << car->getLicensePlate() << std::endl;
//         }
//         for (Truck* truck : trucks){
//             std::cout << "Truck: " << truck->getLicensePlate() << std::endl;
//         }
//     };

//     ~Garage(){
//         //TODO memory leak
//         //delete cars
        
//     }

// private:
//     std::vector<Car*> cars; ///< Vector of pointers to cars in the garage.
//     std::vector<Truck*> trucks; ///< Vector of pointers to trucks in the garage.
// };

// /**
//  * @brief Represents a human who owns a garage and can purchase vehicles.
//  */
// class Human {
// public:
//     /**
//      * @brief Constructs a Human with the given name.
//      * 
//      * @param name The name of the human.
//      */
//     Human(const std::string& name){
//         this->name = new std::string(name);
//         garage = new Garage();
//     };

//     /**
//      * @brief Destructor for Human. 
//      */
//     ~Human(){
//         //TODO Memory leak

//     };

//     /**
//      * @brief Purchases a car with the given license plate and adds it to the human's garage.
//      * 
//      * @param licensePlate The license plate of the car to be purchased.
//      */
//     void purchaseCar(const std::string& licensePlate){
//         Car* car = new Car(licensePlate);
//         addCarToGarage(car);
//     }
    

//     /**
//      * @brief Purchases a truck with the given license plate and adds it to the human's garage.
//      * 
//      * @param licensePlate The license plate of the truck to be purchased.
//      */
//     void purchaseTruck(const std::string& licensePlate){
//         Truck* truck = new Truck(licensePlate);
//         addTruckToGarage(truck);
//     };

//     /**
//      * @brief Adds a car to the human's garage.
//      * 
//      * @param car Pointer to the car to be added.
//      */
//     void addCarToGarage(Car* car){
//         garage->addCar(car);
//     };

//     /**
//      * @brief Adds a truck to the human's garage.
//      * 
//      * @param truck Pointer to the truck to be added.
//      */
//     void addTruckToGarage(Truck* truck){
//         garage->addTruck(truck);
//     };

//     /**
//      * @brief Takes a car from the human's garage based on the license plate.
//      * 
//      * @param licensePlate The license plate of the car to be taken.
//      * @return Pointer to the car if found, nullptr otherwise.
//      */
//     Car* takeCarFromGarage(const std::string& licensePlate){
//         return garage->takeCar(licensePlate);
//     };

//     /**
//      * @brief Takes a truck from the human's garage based on the license plate.
//      * 
//      * @param licensePlate The license plate of the truck to be taken.
//      * @return Pointer to the truck if found, nullptr otherwise.
//      */
//     Truck* takeTruckFromGarage(const std::string& licensePlate){
//         return garage->takeTruck(licensePlate);
//     };

//     /**
//      * @brief Lists all vehicles currently owned by the human.
//      */
//     void listOwnedVehicles() const{
//         garage->listVehicles();
//     };

//     /**
//      * @brief Gets the name of the human.
//      * 
//      * @return The name of the human.
//      */
//     std::string getName() const{
//         return *name;
//     };

// private:
//     std::string* name; ///< Pointer to the name string.
//     Garage* garage; ///< Pointer to the garage owned by the human.
// };

// /**
//  * @brief Represents a geographical location with x and y coordinates.
//  */
// struct Location {
//     double x; ///< The x-coordinate of the location.
//     double y; ///< The y-coordinate of the location.
// };

// /**
//  * @brief Represents a car park with a specific location and capacity.
//  */
// class CarPark {
// public:
//     /**
//      * @brief Constructs a CarPark with the given location and capacity.
//      * 
//      * @param location The location of the car park.
//      * @param capacity The maximum number of vehicles the car park can hold.
//      */
//     CarPark(const Location& location, int capacity);

//     /**
//      * @brief Adds a car to the car park if there is space available.
//      * 
//      * @param car Pointer to the car to be added.
//      * @return True if the car was added, false otherwise.
//      */
//     bool addCar(Car* car){
//         if (currentCars < capacity){
//             cars.push_back(car);
//             currentCars++;
//             return true;
//         }
//         return false;
//     };

//     /**
//      * @brief Adds a truck to the car park if there is space available.
//      * 
//      * @param truck Pointer to the truck to be added.
//      * @return True if the truck was added, false otherwise.
//      */
//     bool addTruck(Truck* truck){
//         if (currentCars < capacity){
//             trucks.push_back(truck);
//             currentCars++;
//             return true;
//         }
//         return false;
//     };

//     /**
//      * @brief Assigns a car to a human based on the human's name and the car's license plate.
//      * 
//      * @param humanName The name of the human.
//      * @param licensePlate The license plate of the car.
//      */
//     void assignCarToHuman(const std::string& humanName, const std::string& licensePlate){
//         humanCarMap[humanName] = licensePlate;
//     };

//     /**
//      * @brief Gets the license plate of the car assigned to a human based on the human's name.
//      * 
//      * @param humanName The name of the human.
//      * @return The license plate of the car assigned to the human, or "No car assigned" if no car is assigned.
//      */
//     std::string getCarOfHuman(const std::string& humanName){
//         if (humanCarMap.find(humanName) != humanCarMap.end()){
//             return humanCarMap[humanName];
//         }
//         return "No car assigned";
//     };

//     /**
//      * @brief Gets the location of the car park.
//      * 
//      * @return The location of the car park.
//      */
//     const Location& getLocation(){
//         return location;
//     };

// private:
//     Location location; ///< The location of the car park.
//     int capacity; ///< The maximum number of vehicles the car park can hold.
//     int currentCars; ///< The current number of vehicles in the car park.
//     std::vector<Car*> cars; ///< Vector of pointers to cars in the car park.
//     std::vector<Truck*> trucks; ///< Vector of pointers to trucks in the car park.
//     std::unordered_map<std::string, std::string> humanCarMap; ///< Map of human names to car license plates.
// };

// /**
//  * @brief Calculates the distance between two locations.
//  * 
//  * @param loc1 The first location.
//  * @param loc2 The second location.
//  * @return The distance between the two locations.
//  */
// double calculateDistance(const Location& loc1, const Location& loc2){
//     return sqrt(pow(loc1.x - loc2.x, 2) + pow(loc1.y - loc2.y, 2));
// };

// /**
//  * @brief Finds the nearest available car park to the current location.
//  * 
//  * @param carParks Vector of pointers to car parks.
//  * @param currentLocation The current location.
//  * @return Pointer to the nearest available car park, or nullptr if no car park is available.
//  */
// CarPark* findNearestAvailableCarPark(const std::vector<CarPark*>& carParks, const Location& currentLocation){
//     CarPark* nearestCarPark = nullptr;
//     double minDistance = std::numeric_limits<double>::max();
//     for (CarPark* carPark : carParks){
//         double distance = calculateDistance(currentLocation, carPark->getLocation());
//         if (distance < minDistance && carPark->addCar(new Car(generateRandomLicensePlate()))){
//             minDistance = distance;
//             nearestCarPark = carPark;
//         }
//     }
//     return nearestCarPark;
// };

// /**
//  * @brief Represents a town that manages cars, trucks, humans, garages, and car parks.
//  */
// class Town {
// public:
//     /**
//      * @brief Adds a car park to the town.
//      * 
//      * @param carPark Pointer to the car park to be added.
//      */
//     void addCarPark(CarPark* carPark){
//         carParks.push_back(carPark);
//     };

//     /**
//      * @brief Adds a car to the town.
//      * 
//      * @param car Pointer to the car to be added.
//      */
//     void addCar(Car* car){
//         cars.push_back(car);
//     };

//     /**
//      * @brief Adds a human to the town.
//      * 
//      * @param human Pointer to the human to be added.
//      */
//     void addHuman(Human* human){
//         humans.push_back(human);
//     };

//     /**
//      * @brief Adds a truck to the town.
//      * 
//      * @param truck Pointer to the truck to be added.
//      */
//     void addTruck(Truck* truck){
//         trucks.push_back(truck);
//     };

//     /**
//      * @brief Adds a garage to the town.
//      * 
//      * @param garage Pointer to the garage to be added.
//      */
//     void addGarage(Garage* garage){
//         garages.push_back(garage);
//     };

//     /**
//      * @brief Gets the car parks in the town.
//      * 
//      * @return A vector of pointers to the car parks in the town.
//      */
//     const std::vector<CarPark*>& getCarParks() const{
//         return carParks;
//     };

//     /**
//      * @brief Gets the cars in the town.
//      * 
//      * @return A vector of pointers to the cars in the town.
//      */
//     const std::vector<Car*>& getCars() const{
//         return cars;
//     };

//     /**
//      * @brief Gets the humans in the town.
//      * 
//      * @return A vector of pointers to the humans in the town.
//      */
//     const std::vector<Human*>& getHumans() const{
//         return humans;
//     };

//     /**
//      * @brief Gets the trucks in the town.
//      * 
//      * @return A vector of pointers to the trucks in the town.
//      */
//     const std::vector<Truck*>& getTrucks() const{
//         return trucks;
//     };

//     /**
//      * @brief Gets the garages in the town.
//      * 
//      * @return A vector of pointers to the garages in the town.
//      */
//     const std::vector<Garage*>& getGarages() const{
//         return garages;
//     };

//     /**
//      * @brief Runs the simulation for a specified number of time steps, performing random actions.
//      */
//     void run(){
//         while(true){
//             int action = rand() % 5;
//             switch(action){
//                 case 0:
//                     moveRandomCar();
//                     break;
//                 case 1:
//                     moveRandomTruck();
//                     break;
//                 case 2:
//                     humanInteractsWithCar();
//                     break;
//                 case 3:
//                     humanInteractsWithTruck();
//                     break;
//                 case 4:
//                     useRandomGarage();
//                     break;
//             }
//         }
//     };

// private:
//     std::vector<CarPark*> carParks; ///< Vector of pointers to car parks in the town.
//     std::vector<Car*> cars; ///< Vector of pointers to cars in the town.
//     std::vector<Human*> humans; ///< Vector of pointers to humans in the town.
//     std::vector<Truck*> trucks; ///< Vector of pointers to trucks in the town.
//     std::vector<Garage*> garages; ///< Vector of pointers to garages in the town.

//     /**
//      * @brief Moves a random car in the town.
//      */
//     void moveRandomCar(){
//         if (cars.size() > 0){
//             int randomIndex = rand() % cars.size();
//             Car* car = cars[randomIndex];
//             cars.erase(cars.begin() + randomIndex);
//             cars.push_back(car);
//         }
//     };

//     /**
//      * @brief Moves a random truck in the town.
//      */
//     void moveRandomTruck(){
//         if (trucks.size() > 0){
//             int randomIndex = rand() % trucks.size();
//             Truck* truck = trucks[randomIndex];
//             trucks.erase(trucks.begin() + randomIndex);
//             trucks.push_back(truck);
//         }
//     };

//     /**
//      * @brief A human interacts with a random car in the town.
//      */
//     void humanInteractsWithCar(){
//         if (humans.size() > 0 && cars.size() > 0){
//             int randomHumanIndex = rand() % humans.size();
//             Human* human = humans[randomHumanIndex];
//             int randomCarIndex = rand() % cars.size();
//             Car* car = cars[randomCarIndex];
//             human->purchaseCar(car->getLicensePlate());
//         }
//     };

//     /**
//      * @brief A human interacts with a random truck in the town.
//      */
//     void humanInteractsWithTruck(){
//         if (humans.size() > 0 && trucks.size() > 0){
//             int randomHumanIndex = rand() % humans.size();
//             Human* human = humans[randomHumanIndex];
//             int randomTruckIndex = rand() % trucks.size();
//             Truck* truck = trucks[randomTruckIndex];
//             human->purchaseTruck(truck->getLicensePlate());
//         }
//     };

//     /**
//      * @brief Uses a random garage in the town.
//      */
//     void useRandomGarage(){
//         if (garages.size() > 0){
//             int randomIndex = rand() % garages.size();
//             Garage* garage = garages[randomIndex];
//             garage->listVehicles();
//         }
//     };
// };

// /**
//  * @brief The main function that initializes the town and runs the simulation.
//  * 
//  * @return Exit status of the program.
//  */
// int main(){
   

//     Town town = Town();
//      //generates a bumch of random cars and car parks and garages and humans and traucks and runs the simulation
//     for (int i = 0; i < 100; ++i) {
//         // Create random cars
//         Car* car = new Car(generateRandomLicensePlate());
//         town.addCar(car);

//         // Create random trucks
//         Truck* truck = new Truck(generateRandomLicensePlate());
//         town.addTruck(truck);

//         // Create random humans
//         Human* human = new Human("Human" + std::to_string(i));
//         town.addHuman(human);

//         // Create random garages
//         Garage* garage = new Garage();
//         town.addGarage(garage);

//         // Create random car parks
//         Location location = {static_cast<double>(rand() % 100), static_cast<double>(rand() % 100)};
//         CarPark* carPark = new CarPark(location, rand() % 50 + 1);
//         town.addCarPark(carPark);
//     }
//     town.run();
//     return 0;

// };