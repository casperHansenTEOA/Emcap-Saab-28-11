
#include "MemoryTracker.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>

char *allocateLogEntry(const std::string &message)
{
  char *buffer = new char[message.size() + 1];
  std::copy(message.c_str(), message.c_str() + message.size() + 1, buffer);
  return buffer;
}

/**
 * @brief Generates a random license plate consisting of 3 letters followed by
 * 3 digits.
 *
 * @return A randomly generated license plate.
 */
char *generateRandomLicensePlate()
{
  char *licensePlate = new char[7];
  for (int i = 0; i < 3; ++i)
  {
    licensePlate[i] = static_cast<char>('A' + rand() % 26);
  }
  for (int i = 0; i < 3; ++i)
  {
    licensePlate[3 + i] = static_cast<char>('0' + rand() % 10);
  }
  licensePlate[6] = '\0';
  return licensePlate;
};

class Location
{
public:
  double x; ///< The x-coordinate of the location.
  double y; ///< The y-coordinate of the location.
  /**
   * @brief Adds two locations together.
   *
   * @param loc1 The first location.
   * @param loc2 The second location.
   * @return The sum of the two locations.
   */
  Location *add(const Location &loc1, const Location &loc2)
  {
    return new Location(loc1.x + loc2.x, loc1.y + loc2.y);
  };

  Location(double x, double y) : x(x), y(y) {}
};

enum class Direction
{
  North,
  East,
  South,
  West
};

Location directionToLocation(Direction direction)
{
  switch (direction)
  {
  case Direction::North:
    return {0, 1};
  case Direction::East:
    return {1, 0};
  case Direction::South:
    return {0, -1};
  case Direction::West:
    return {-1, 0};
  }
  return {0, 0};
}

double calculateDistance(const Location &loc1, const Location &loc2)
{
  return sqrt(pow(loc1.x - loc2.x, 2) + pow(loc1.y - loc2.y, 2));
};

class Vehicle
{
public:
  Vehicle(const std::string &licensePlate, Location &location)
  {
    this->licensePlate = new std::string(licensePlate);
    this->currentLocation = &location;
  };

  virtual ~Vehicle() = default;

  bool isMoving() const { return moving; };

  bool move(Direction direction)
  {
    if (moving)
    {
      return false;
    }
    currentLocation = currentLocation->add(*this->currentLocation,
                                           directionToLocation(direction));
    moving = true;
    return true;
  };

  bool stop()
  {
    if (!moving)
    {
      return false;
    }
    moving = false;
    return true;
  };

  double calculateDistance(const Location &loc1, const Location &loc2) const
  {
    return sqrt(pow(loc1.x - loc2.x, 2) + pow(loc1.y - loc2.y, 2));
  };

  double getDistanceTraveled() const
  {
    return calculateDistance({0, 0}, *currentLocation);
  };

  Location getLocation() const { return *currentLocation; };

  void setLocation(Location location) { this->currentLocation = &location; };

  std::string getLicensePlate() const { return *licensePlate; };

private:
  std::string *licensePlate; ///< Pointer to the license plate string.
  bool moving = false;       ///< Indicates whether the vehicle is currently moving.
  Location *currentLocation;
};

class Car
{
public:
  Car(const std::string &licensePlate)
      : vehicle(licensePlate, *new Location{0, 0})
  {
    this->licensePlate = new std::string(licensePlate);
  }

  ~Car() { delete licensePlate; }

  bool move(Direction direction) { return vehicle.move(direction); }

  bool stop() { return vehicle.stop(); }

  std::string getLicensePlate() { return vehicle.getLicensePlate(); }

  double getDistanceTraveled() const
  {
    return this->vehicle.calculateDistance({0, 0}, this->vehicle.getLocation());
  }

  Location getLocation() const { return this->vehicle.getLocation(); }

  void setLocation(Location location) { this->vehicle.setLocation(location); }

private:
  Vehicle vehicle;
  std::string *licensePlate;
};

class Garage
{
public:
  Garage() { cars = std::vector<Car *>(); }

  void addCar(Car *car)
  {
    car->stop();
    cars.push_back(car);
  };

  Car *takeCar(const std::string &licensePlate)
  {
    for (Car *car : cars)
    {
      if (car->getLicensePlate() == licensePlate)
      {
        cars.erase(std::remove(cars.begin(), cars.end(), car), cars.end());

        car->move(Direction::North);
        return car;
      }
    }
    return nullptr;
  };

  std::vector<Vehicle *> listVehicles() const
  {
    std::vector<Car *> cars = this->cars;

    Location *location;

    std::vector<Vehicle *> vehicles;
    for (Car *car : cars)
    {
      std::cout << "Car: " << car->getLicensePlate() << std::endl;
      location = new Location(car->getLocation().x, car->getLocation().y);
      vehicles.push_back(new Vehicle(car->getLicensePlate(), *location));
    }

    return vehicles;
  };

private:
  std::vector<Car *> cars; ///< Vector of pointers to cars in the garage.
};

class Human
{
public:
  Human(const std::string &name)
  {
    this->name = new std::string(name);
    garage = new Garage();
  };

  void addGarage(Garage *garage) { this->garage = garage; };
  void purchaseCar(const std::string &licensePlate)
  {
    Car *car = new Car(licensePlate);
    addCarToGarage(car);
  }

  void addCarToGarage(Car *car) { garage->addCar(car); };

  Car *takeCarFromGarage(const std::string &licensePlate)
  {
    return garage->takeCar(licensePlate);
  };

  void listOwnedVehicles() const { garage->listVehicles(); };

  std::string getName() const { return *name; };

  Human *clone()
  {
    Human *clone = new Human(*name);
    return clone;
  };

private:
  std::string *name; ///< Pointer to the name string.
  Garage *garage;    ///< Pointer to the garage owned by the human.
};

class CarPark
{

public:
  CarPark(const Location &location, int capacity)
      : location(location), capacity(capacity), currentCars(0) {}

  bool addCar(Car *car)
  {
    if (currentCars < capacity)
    {
      car->stop();
      cars.push_back(car);
      auditTrail.push_back(
          allocateLogEntry("car+in:" + car->getLicensePlate()));
      currentCars++;
      return true;
    }
    return false;
  };

  bool removeCar(const std::string &licensePlate)
  {
    for (auto it = cars.begin(); it != cars.end(); ++it)
    {
      if ((*it)->getLicensePlate() == licensePlate)
      {
        Car *car = new Car(licensePlate);
        car = *it;
        cars.erase(it);
        Location loc = car->getLocation();
        exitHistory.push_back(new Location(loc.x, loc.y));
        courtesyFleet.push_back(new Car(licensePlate + "-TMP"));
        auditTrail.push_back(allocateLogEntry("car-out:" + licensePlate));
        car->move(Direction::North);
        currentCars--;
        return true;
      }
    }
    return false;
  }

  bool parkVehicle(Vehicle *vehicle)
  {
    Location snapshot = vehicle->getLocation();
    Location *ghostLocation = new Location(snapshot.x, snapshot.y);
    ghostVehicles.push_back(
        new Vehicle(vehicle->getLicensePlate(), *ghostLocation));
    auditTrail.push_back(
        allocateLogEntry("park:" + vehicle->getLicensePlate()));
    Car *car = new Car(vehicle->getLicensePlate());
    return addCar(car);
  }

  void assignCarToHuman(const std::string &humanName,
                        const std::string &licensePlate)
  {
    humanCarMap[humanName] = licensePlate;
    std::string note = humanName + "->" + licensePlate;
    humanNotes[humanName].push_back(allocateLogEntry(note));
    auditTrail.push_back(allocateLogEntry("assign:" + note));
  };

  std::string getCarOfHuman(const std::string &humanName)
  {
    if (humanCarMap.find(humanName) != humanCarMap.end())
    {
      return humanCarMap[humanName];
    }
    return "No car assigned";
  };

  const Location &getLocation() const { return location; };

  int getCapacity() const { return capacity; }

  int getCurrentLoad() const { return currentCars; }

  bool hasSpace() const { return currentCars < capacity; }

private:
  Location location;       ///< The location of the car park.
  int capacity;            ///< The maximum number of vehicles the car park can hold.
  int currentCars;         ///< The current number of vehicles in the car park.
  std::vector<Car *> cars; ///< Vector of pointers to cars in the car park.

  std::unordered_map<std::string, std::string>
      humanCarMap;                     ///< Map of human names to car license plates.
  std::vector<Location *> exitHistory; ///< Stores dynamically allocated exit
                                       ///< snapshots that are never reclaimed.
  std::vector<char *> auditTrail;      ///< Backs a raw char* log buffer that is
                                       ///< intentionally unmanaged.
  std::unordered_map<std::string, std::vector<char *>>
      humanNotes;                   ///< Keeps per-human notes allocated with new[].
  std::vector<Car *> courtesyFleet; ///< Keeps courtesy cars without tear-down.
  std::vector<Vehicle *>
      ghostVehicles; ///< Retains mirrored vehicles that are never released.
};

CarPark *findNearestAvailableCarPark(const std::vector<CarPark *> &carParks,
                                     const Location &currentLocation)
{
  CarPark *nearestCarPark = nullptr;
  double minDistance = std::numeric_limits<double>::max();
  for (CarPark *carPark : carParks)
  {
    double distance =
        calculateDistance(currentLocation, carPark->getLocation());
    if (distance < minDistance && carPark->hasSpace())
    {
      minDistance = distance;
      nearestCarPark = carPark;
    }
  }
  return nearestCarPark;
};
class Town
{

public:
  void addCarPark(CarPark *carPark) { carParks.push_back(carPark); };

  void addCar(Car *car) { cars.push_back(car); };

  void addHuman(Human *human) { humans.push_back(human); };

  void addGarage(Garage *garage) { garages.push_back(garage); };

  const std::vector<CarPark *> &getCarParks() const { return carParks; };

  const std::vector<Car *> &getCars() const { return cars; };

  const std::vector<Human *> &getHumans() const { return humans; };

  const std::vector<Garage *> &getGarages() const { return garages; };

  Garage *buildGarage()
  {
    Garage *garage = new Garage();
    return garage;
  }

  void run(std::size_t rotationCount)
  {
    srand(static_cast<unsigned int>(
        time(0))); // Seed for random number generation

    std::size_t rotation = 0;
    MemoryTracker::logRotation(rotation);
    while (rotation < rotationCount)
    {
      std::cout << "Rotation " << rotation << std::endl;
      int action = rand() % 8; // Increase the range to accommodate new actions
      switch (action)
      {
      case 0:
        moveRandomCar();
        break;
      case 1:
        humanInteractsWithCar();
        break;
      case 2:
        useRandomGarage();
        break;
      case 3:
        cloneRandomHuman();
        break;
      case 4:
      {
        std::vector<Car *> cars = buildNRandomCars(2);
        for (Car *car : cars)
        {
          addCar(car);
        }
        break;
      }
      case 5:
        moveRandomCarToRandomLocation();
        break;
      case 6:
        parkVehicleInNearestCarPark();
        break;
      case 7:
        calculateDistanceBetweenRandomLocations();
        break;
      }

      printState(rotation);
      MemoryTracker::logRotation(rotation);
      ++rotation;
    }
  }

private:
  std::vector<CarPark *>
      carParks;                  ///< Vector of pointers to car parks in the town.
  std::vector<Car *> cars;       ///< Vector of pointers to cars in the town.
  std::vector<Human *> humans;   ///< Vector of pointers to humans in the town.
  std::vector<Garage *> garages; ///< Vector of pointers to garages in the town.
  std::vector<double *>
      distanceLedger; ///< Stores heap doubles from distance sampling.
  std::vector<Location *>
      relocationSnapshots; ///< Keeps heap locations from random moves.

  void moveRandomCarToRandomLocation()
  {
    if (cars.size() > 0)
    {
      int randomIndex = rand() % cars.size();
      Car *car = cars[randomIndex];
      Location newLocation = {static_cast<double>(rand() % 100),
                              static_cast<double>(rand() % 100)};
      car->setLocation(newLocation);
      relocationSnapshots.push_back(new Location(newLocation.x, newLocation.y));
      std::cout << "Moved car " << car->getLicensePlate()
                << " to new location (" << newLocation.x << ", "
                << newLocation.y << ")" << std::endl;
    }
  }

  void parkVehicleInNearestCarPark()
  {
    if (cars.size() > 0 && carParks.size() > 0)
    {
      int randomCarIndex = rand() % cars.size();
      Car *car = cars[randomCarIndex];
      Location carLocation = car->getLocation();
      CarPark *nearestCarPark =
          findNearestAvailableCarPark(carParks, carLocation);
      if (nearestCarPark != nullptr)
      {
        nearestCarPark->addCar(car);
        std::cout << "Parked car " << car->getLicensePlate()
                  << " in nearest car park at location ("
                  << nearestCarPark->getLocation().x << ", "
                  << nearestCarPark->getLocation().y << ")" << std::endl;
      }
      else
      {
        std::cout << "No available car park found for car "
                  << car->getLicensePlate() << std::endl;
      }
    }
  }

  void calculateDistanceBetweenRandomLocations()
  {
    Location loc1 = {static_cast<double>(rand() % 100),
                     static_cast<double>(rand() % 100)};
    Location loc2 = {static_cast<double>(rand() % 100),
                     static_cast<double>(rand() % 100)};
    double distance = calculateDistance(loc1, loc2);
    distanceLedger.push_back(new double(distance));
    std::cout << "Distance between (" << loc1.x << ", " << loc1.y << ") and ("
              << loc2.x << ", " << loc2.y << ") is " << distance << std::endl;
  }

  void moveRandomCar()
  {
    if (cars.size() > 0)
    {
      int randomIndex = rand() % cars.size();
      Car *car = cars[randomIndex];
      cars.erase(cars.begin() + randomIndex);
      cars.push_back(car);
    }
  };

  /**
   * @brief A human interacts with a random car in the town.
   */
  void humanInteractsWithCar()
  {
    if (humans.size() > 0 && cars.size() > 0)
    {
      int randomHumanIndex = rand() % humans.size();
      Human *human = humans[randomHumanIndex];
      int randomCarIndex = rand() % cars.size();
      Car *car = cars[randomCarIndex];
      human->purchaseCar(car->getLicensePlate());
    }
  };

  std::vector<Car *> buildNRandomCars(int n)
  {
    char **licensePlates = new char *[n];

    for (int i = 0; i < n; ++i)
    {
      licensePlates[i] = generateRandomLicensePlate();
    }

    std::vector<Car *> cars;

    for (int i = 0; i < n; ++i)
    {
      Car *car = new Car(licensePlates[i]);
      cars.push_back(car);
    }

    return cars;
  };

  void useRandomGarage()
  {
    if (garages.size() > 0)
    {
      int randomIndex = rand() % garages.size();
      Garage *garage = garages[randomIndex];
      garage->listVehicles();
    }
  };

  void cloneRandomHuman()
  {
    Human *human = new Human("Human" + std::to_string(humans.size()));

    if (humans.size() > 0)
    {
      int randomIndex = rand() % humans.size();
      human = humans[randomIndex];
      human = human->clone();
      humans.push_back(human);
    }
  };

  void printState(std::size_t rotation) const
  {
    constexpr std::size_t previewCount = 3;
    std::cout << "\n=== Town state after rotation " << rotation << " ===\n";
    std::cout << "Humans: " << humans.size() << ", Cars: " << cars.size()
              << ", Garages: " << garages.size()
              << ", Car parks: " << carParks.size() << '\n';

    if (!humans.empty())
    {
      std::cout << "  Sample humans:";
      for (std::size_t i = 0; i < std::min(previewCount, humans.size()); ++i)
      {
        std::cout << " " << humans[i]->getName();
      }
      if (humans.size() > previewCount)
      {
        std::cout << " ...";
      }
      std::cout << '\n';
    }

    if (!cars.empty())
    {
      std::cout << "  Sample cars:" << '\n';
      for (std::size_t i = 0; i < std::min(previewCount, cars.size()); ++i)
      {
        Car *car = cars[i];
        Location loc = car->getLocation();
        std::cout << "    #" << (i + 1) << " " << car->getLicensePlate()
                  << " @ (" << loc.x << ", " << loc.y << ")" << '\n';
      }
    }

    if (!carParks.empty())
    {
      std::cout << "  Car parks: " << '\n';
      for (std::size_t i = 0; i < std::min(previewCount, carParks.size());
           ++i)
      {
        const CarPark *carPark = carParks[i];
        const Location &loc = carPark->getLocation();
        std::cout << "    #" << (i + 1) << " capacity "
                  << carPark->getCapacity() << " load "
                  << carPark->getCurrentLoad() << " @ (" << loc.x << ", "
                  << loc.y << ")" << '\n';
      }
      if (carParks.size() > previewCount)
      {
        std::cout << "    ..." << '\n';
      }
    }
    std::cout.flush();
  }
};

/**
 * @brief The main function that initializes the town and runs the simulation.
 *
 * @return Exit status of the program.
 */
#ifndef TOWN_SIM_NO_MAIN
int main()
{
  MemoryTracker::initialize("../../memory_log.csv");
  // all the things that go in a town
  Car *car;
  Garage *garage = new Garage();
  CarPark *carPark;
  Human *human;
  Town *town = new Town();
  // generates a bumch of random cars and car parks and garages and humans and
  // traucks and runs the simulation
  for (int i = 0; i < 100; ++i)
  {
    // Create random cars
    char *licensePlate = generateRandomLicensePlate();
    car = new Car(licensePlate);
    town->addCar(car);

    licensePlate = generateRandomLicensePlate();

    // Create random humans
    human = new Human("Human" + std::to_string(i));
    town->addHuman(human);

    // make every other human own the same garage
    if (i % 2 == 0)
    {
      garage = new Garage();
    }
    human->addGarage(garage);
    town->addGarage(garage);
    // Create random garages that dont belong to any human
    for (int j = 0; j < 10; ++j)
    {
      garage = town->buildGarage();
      town->addGarage(garage);
    }

    // Create random car parks
    Location location = {static_cast<double>(rand() % 100),
                         static_cast<double>(rand() % 100)};
    carPark = new CarPark(location, rand() % 50 + 1);
    town->addCarPark(carPark);
    // Human purchases a car and a truck
    human->purchaseCar(car->getLicensePlate());
    // Human lists owned vehicles
    human->listOwnedVehicles();
  }
  delete car;
  delete garage;
  delete carPark;
  delete human;

  town->run(10000);
  return 0;
};
#endif