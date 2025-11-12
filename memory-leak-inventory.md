# Memory Leak Inventory

This project deliberately accumulates memory management issues so learners can practice tooling and debugging. The list below captures every leak currently present (updated 2025-11-12) along with the file locations and the trigger that surfaces each allocation.

## Geometry & Vehicle Foundation

- **L-01** – `Excecises/src/Location.h:15`: `Location::add` builds a `new Location` on every call and hands ownership to the caller, yet none of the call sites delete the pointer. Reproduce by calling `Vehicle::move` repeatedly.
- **L-02** – `Excecises/src/Vehicles/Vehicle.cpp:18`: `Vehicle::Vehicle` stores its license plate in a `new std::string` and relies on the default destructor, so the string is never reclaimed. Happens for every `Car` and `Truck` instance.
- **L-03** – `Excecises/src/Vehicles/Vehicle.cpp:32`: Setting `currentLocation` to the result of `Location::add` leaks the previous pointer forever. Trigger by calling `Vehicle::move` multiple times.
- **L-04** – `Excecises/src/Vehicles/Car.cpp:3`: The `Car` constructor dereferences `*new Location{0, 0}` to seed the embedded `Vehicle`, leaking that heap allocation at construction time.
- **L-05** – `Excecises/src/Vehicles/Truck.cpp:6`: `Truck` allocates `new std::vector<double>` for cargo weights without supplying a destructor, so the container persists until process exit.

## CarPark Subsystem

- **CP-01** – `Excecises/src/CarPark/CarPark.cpp:18`: `generateRandomLicensePlate` returns a raw `char[7]`. Callers (notably `Town::buildNRandomCars`) never delete the buffer.
- **CP-02** – `Excecises/src/CarPark/CarPark.cpp:53`: `CarPark::addCar` pushes `allocateLogEntry(...)` into `auditTrail`. `auditTrail` is never cleared, so every park event leaks a heap buffer.
- **CP-03** – `Excecises/src/CarPark/CarPark.cpp:64`: `CarPark::addTruck` mirrors CP-02 for trucks.
- **CP-04** – `Excecises/src/CarPark/CarPark.cpp:73`: `CarPark::removeCar` does `Car* car = new Car(...);` and immediately overwrites the pointer, leaking the freshly allocated `Car`.
- **CP-05** – `Excecises/src/CarPark/CarPark.cpp:76-79`: Removing a car records a `new Location` in `exitHistory`, spawns a courtesy `new Car` in `courtesyFleet`, and drops another log buffer into `auditTrail`. None of these collections are cleaned up.
- **CP-06** – `Excecises/src/CarPark/CarPark.cpp:86`: `CarPark::removeTruck` repeats the same pattern with trucks, leaking a `Truck`, a `Location`, and a log buffer per removal.
- **CP-07** – `Excecises/src/CarPark/CarPark.cpp:96-99`: `CarPark::parkVehicle` snapshots each vehicle into `ghostVehicles` by allocating both a `Vehicle` and its backing `Location`. The shadow fleet is never freed.
- **CP-08** – `Excecises/src/CarPark/CarPark.cpp:104-106`: `assignCarToHuman` allocates a `char[]` note for `humanNotes` and another for the audit trail; both grow unbounded.

## Garage & Human Ownership Layers

- **G-01** – `Excecises/src/Garage/Garage.cpp:35-46`: `Garage::listVehicles` allocates `Location` and `Vehicle` objects for reporting and returns them by value. Callers (for example `Town::useRandomGarage`) drop the returned vector, leaking every element.
- **H-01** – `Excecises/src/Human/Human.cpp:3`: `Human` owns its name via `new std::string` and creates a `new Garage`, but without a destructor both objects leak when the human is done.
- **H-02** – `Excecises/src/Human/Human.cpp:32`: `Human::clone` creates a heap `Human` that is never reclaimed because there is no ownership strategy; repeated cloning compounds the leak.

## Town-Level Simulation

- **T-01** – `Excecises/src/Town/Town.cpp:15`: `Town::addCarPark`, `addCar`, `addTruck`, `addHuman`, and `addGarage` all retain raw pointers. Because `Town` never frees these collections, every entity allocated for the town leaks at shutdown.
- **T-02** – `Excecises/src/Town/Town.cpp:132`: `Town::buildNRandomCars` allocates `char** licensePlates` and each plate via `generateRandomLicensePlate`. The helper never deletes the array or the individual buffers.
- **T-03** – `Excecises/src/Town/Town.cpp:148`: `Town::cloneRandomHuman` starts by allocating a fresh `Human` and then overwrites the pointer with an existing resident before cloning. The initial `new Human` is immediately leaked.
- **T-04** – `Excecises/src/Town/Town.cpp:45`: `moveRandomCarToRandomLocation` records each randomized location inside `relocationSnapshots` as `new Location` entries without cleanup.
- **T-05** – `Excecises/src/Town/Town.cpp:54`: `moveRandomTruckToRandomLocation` mirrors T-04 for trucks.
- **T-06** – `Excecises/src/Town/Town.cpp:71`: `calculateDistanceBetweenRandomLocations` pushes a `new double` into `distanceLedger` on every call, and the ledger is never drained.
- **T-07** – `Excecises/src/Town/Town.cpp:98`: `Town::parkVehicleInNearestCarPark` hands cars to `CarPark::addCar`, cascading into CP-02/CP-07 leaks for every operation.
- **T-08** – `Excecises/src/Town/Town.cpp:121`: `useRandomGarage` ignores the returned vehicle list, so all allocations described in G-01 leak in bulk during garage inspections.

## Cross-Cutting Patterns

- **X-01** – Any call to `Human::purchaseCar`/`purchaseTruck` or `Town::buildGarage` produces heap objects that are stored only in owning vectors without a corresponding destruction path. Long-running simulations will accumulate these indefinitely.
- **X-02** – The new `auditTrail`, `humanNotes`, `exitHistory`, `courtesyFleet`, `courtesyHaulers`, `ghostVehicles`, `distanceLedger`, and `relocationSnapshots` members all grow monotonically during a run, providing diverse leak signatures (raw buffers, STL containers, nested object graphs) for diagnostic practice.

Use this catalogue as a checklist when exercising leak detectors (AddressSanitizer, Valgrind, CRT leak reports, etc.). Each entry is reproducible through the simulation loop in `Town::run`, and together they cover a wide range of leak patterns: orphaned new/delete pairs, container growth without teardown, and ownership bugs introduced by cloning or logging helpers.
