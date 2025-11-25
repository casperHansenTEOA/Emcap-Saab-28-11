# Town Simulation Program

## Overview

The simulation models a fictional town populated with humans, vehicles, garages, and car parks. It continuously performs random actions to mimic day-to-day activity such as moving vehicles, assigning ownership, and parking. The program is written in C++ and is driven from `main.cpp`, which seeds the town with entities and then hands off control to an infinite simulation loop inside `Town::run`.

## Core Components

- `Town`: Owns collections of cars, trucks, humans, garages, and car parks. It schedules random actions every half second and prints periodic summaries of the town state.
- `Human`: Represents a resident that can purchase vehicles and share garages. Humans can clone themselves and manage the vehicles stored in their assigned garages.
- `Vehicle`, `Car`, `Truck`: `Vehicle` provides basic movement and location tracking. `Car` and `Truck` wrap a `Vehicle` instance and expose domain-specific behavior and data.
- `Garage`: Stores vehicles for humans. When used, it lists the current inventory and can release vehicles back into the simulation.
- `CarPark`: Represents public parking locations. It can park and release vehicles, track per-human assignments, and compute distances to support nearest car park searches.
- `MemoryTracker`: Overrides global new/delete to count allocations and logs the totals to `memory_log.csv` for each simulation rotation.

## Simulation Lifecycle

1. **Bootstrap (`main.cpp`)**
   - Initializes the memory tracker with `memory_log.csv`.
   - Allocates a `Town` and populates it with 100 iterations of randomly generated cars, trucks, humans, garages, and car parks.
   - Each human purchases the vehicles created in that iteration and lists their inventory.
2. **Main Loop (`Town::run`)**
   - Loops forever with a 500 ms delay between iterations.
   - Picks one of several actions at random: move vehicles, interact with vehicles, use garages, clone humans, build extra cars, relocate vehicles, park in the nearest car park, or sample distances between random points.
   - Logs the current allocation counters and prints a snapshot of the town (sample humans, vehicles, and car parks).
3. **Entity Behavior**
   - Vehicles maintain their position in the plane and track distance traveled.
   - Garages stop vehicles that enter and start them moving when released.
   - Car parks maintain capacity limits, audit trails, and distance calculations to support proximity queries.

## Observability and Logs

- Console output shows the action results and town snapshots each rotation.
- CSV logs written by `MemoryTracker` accumulate allocation statistics that can be opened in a spreadsheet or plotted.

## Building and Running

- Make sure make is installed
- Run the python file

- `python mem_comp.py`

The python file qwill run the simulation for a minute then gather the memory info and then graph it using matplotlib
