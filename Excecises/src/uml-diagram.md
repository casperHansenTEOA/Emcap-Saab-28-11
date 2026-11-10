# Town Simulation UML Diagram

This diagram describes the current implementation in `main.cpp`.
It documents the current pointer relationships, including unsafe ownership.

```mermaid
classDiagram
    direction TB

    class Location {
        +double x
        +double y
        +add(Location, Location) pointer
    }

    class Vehicle {
        -string licensePlatePtr
        -bool moving
        -Location currentLocationPtr
        +move(Direction) bool
        +stop() bool
        +getLocation() Location
        +setLocation(Location) void
    }

    class Car {
        -Vehicle vehicle
        -string licensePlatePtr
        +move(Direction) bool
        +stop() bool
        +getLocation() Location
    }

    class Garage {
        -vector~CarPtr~ cars
        +addCar(CarPtr) void
        +takeCar(string) CarPtr
        +listVehicles() vector~VehiclePtr~
    }

    class Human {
        -string namePtr
        -Garage garagePtr
        +purchaseCar(string) void
        +addCarToGarage(CarPtr) void
        +takeCarFromGarage(string) CarPtr
        +clone() HumanPtr
    }

    class CarPark {
        -Location location
        -int capacity
        -int currentCars
        -vector~CarPtr~ cars
        -unordered_map humanCarMap
        -vector~LocationPtr~ exitHistory
        -vector~charPtr~ auditTrail
        -unordered_map humanNotes
        -vector~CarPtr~ courtesyFleet
        -vector~VehiclePtr~ ghostVehicles
        +addCar(CarPtr) bool
        +removeCar(string) bool
        +parkVehicle(VehiclePtr) bool
    }

    class Town {
        -vector~CarParkPtr~ carParks
        -vector~CarPtr~ cars
        -vector~HumanPtr~ humans
        -vector~GaragePtr~ garages
        -vector~doublePtr~ distanceLedger
        -vector~LocationPtr~ relocationSnapshots
        +addCar(CarPtr) void
        +addHuman(HumanPtr) void
        +addGarage(GaragePtr) void
        +addCarPark(CarParkPtr) void
        +run(size_t) void
    }

    class MemoryTracker {
        <<namespace>>
        +initialize(string) void
        +logRotation(size_t) void
        +shutdown() void
        <<global new/delete overrides>>
    }

    Car *-- Vehicle : contains by value
    Vehicle ..> Location : stores pointer
    Vehicle ..> string : raw pointer no destructor
    Car ..> string : raw pointer deleted

    Garage o-- "0..*" Car : stores pointers ownership unclear
    Human ..> Garage : stores pointer overwritten
    Human ..> Car : creates pointer in purchaseCar

    CarPark o-- "0..*" Car : stores pointers ownership unclear
    CarPark ..> Location : leaked snapshots
    CarPark ..> Vehicle : leaked ghost vehicles
    CarPark ..> string : leaked char[] audit entries

    Town o-- "0..*" Car : raw pointers no destructor
    Town o-- "0..*" Human : raw pointers no destructor
    Town o-- "0..*" Garage : raw pointers no destructor
    Town o-- "0..*" CarPark : raw pointers no destructor
    Town ..> Location : leaked relocation snapshots
    Town ..> double : leaked distance samples

    MemoryTracker ..> Town : logs each rotation
```

## Relationship Legend

| Diagram notation | Meaning in this program |
|---|---|
| `*--` | Composition or value ownership. `Car` contains a `Vehicle` object directly. |
| `o--` | Collection of raw pointers. The collection stores pointers, but the code does not define safe ownership. |
| `..>` | A pointer or dependency relationship. Ownership must be checked in the source. |
| `owns ... but no destructor` | The object allocates memory but does not release it correctly. |
| `leaked ...` | The program allocates an object and stores the pointer without a cleanup path. |

## Important Ownership Problems Shown

1. `Town`, `Garage`, and `CarPark` all store `Car*` pointers. The same car can appear in multiple collections, but no class clearly owns it.
2. `Vehicle::licensePlate`, `Vehicle::currentLocation`, `Car::licensePlate`, and `Human::name` are raw pointers allocated with `new`.
3. `Vehicle::setLocation(Location)` stores the address of a local parameter, creating a dangling pointer.
4. `Garage::listVehicles()` creates `Vehicle*` and `Location*` objects that are returned without an owner.
5. `CarPark` stores several raw-pointer histories and logs without destructors.
6. `Town` stores the main objects but has no destructor to clean them up.
7. `main()` deletes the last loop variables even though those objects are also stored in `Town`, leaving dangling pointers in the town.
8. `CarPark::parkVehicle(Vehicle*)` tries to cast a `Vehicle*` to `Car*`, although `Car` does not inherit from `Vehicle` in the current design.

## Safer Future Design

A safer redesign would use:

- `Location` and `std::string` as values instead of owning raw pointers.
- `std::unique_ptr` in the class that owns each `Car`, `Human`, `Garage`, and `CarPark`.
- Raw pointers or references only for explicitly non-owning relationships.
- `std::vector<Location>`, `std::vector<double>`, and `std::vector<std::string>` for history and logs.
- A single owner for each `Car` so it cannot be owned simultaneously by `Town`, `Garage`, and `CarPark`.
