# Lab: Repair the Town Simulation

## Goal

Repair the program's structural and memory-management problems without changing its basic purpose: simulate cars, people, garages, and car parks.

This is an investigation lab. The tasks describe what must be improved, but do not give the final implementation. Use the existing code, compiler diagnostics, the UML diagram, and small experiments to determine the details.

The executable checkpoint tests are in `tests/checkpoint_tests.cpp`. Each test
is numbered and names the milestone it verifies.

- Work on one milestone at a time.
- Compile after every milestone.
- Do not hide warnings by removing warning flags.
- Do not add a second ownership system alongside the first one.
- Prefer values and RAII over manually managed `new` and `delete`.
- When an object has one clear owner, investigate `std::unique_ptr` first.
- Use `std::shared_ptr` only when shared lifetime is genuinely required and you can explain why.
- Use raw pointers or references for non-owning access only after identifying the owner's lifetime.
- Do not replace every pointer with `std::shared_ptr` automatically; that can hide unclear ownership.
- Add a small test or observable check before moving to the next risky change.

## Starting Evidence

Before editing, record the results of these checks:

```text
g++ -std=c++20 -Wall -Wextra -pedantic main.cpp MemoryTracker.cpp -o town_sim
```

Then inspect compiler warnings and whether a sanitizer is available. If
supported by your toolchain, also try AddressSanitizer and
UndefinedBehaviorSanitizer.

Create a short table with these columns:

```text
Problem | Evidence | Suspected owner | Planned repair | Verification
```

Compile the checkpoint tests from the `src` directory with:

```text
g++ -std=c++20 -Wall -Wextra -pedantic tests/checkpoint_tests.cpp MemoryTracker.cpp -o checkpoint_tests
```

The tests are executable from the beginning. A failing test identifies work
that remains; it is not a request to edit the test to make it pass.

## What "Clear the Milestone" Means

A milestone is clear only when all of its listed checkpoint tests report
`PASS`, the test program reports zero failures, and the project still builds
with the warning flags. Run the test suite again after every repair; an
earlier passing test must stay passing.

## Milestone 1: Establish a Clean Baseline

### Tasks

1. Build the program with warnings enabled.
2. Run it for a small, controlled number of simulation steps.
3. Save the compiler output.
4. Identify every warning involving a pointer, lifetime, or missing include.

### Questions

- Which class creates each `Car`, `Human`, `Garage`, and `CarPark`?
- Which class is supposed to destroy it?
- Can the same object appear in more than one container?
- Which pointers are owning and which are only references?

### Checkpoint

You should be able to explain the lifetime of one car from creation through storage, movement, parking, and program exit.

Milestone 1 is clear when the baseline table is complete, the current
ownership graph is drawn, and the warnings and known failures are recorded.

## Milestone 2: Remove Unnecessary Heap Allocation

Start with data that has simple value semantics.

### Targets

- `Location`
- license plates
- human names
- distance samples
- relocation snapshots
- audit messages
- history records

### Tasks

1. Decide which members can be stored directly as values.
2. Change helper functions that return heap-allocated temporary objects to return values.
3. Replace character buffers used as strings with `std::string` where appropriate.
4. Replace heap-allocated scalar history values with containers of values.
5. Compile and compare the program's observable behavior with the baseline.

### Questions

- Does a caller need to delete the returned object?
- Does the object need identity, or only a value?
- What is the smallest lifetime required for each history entry?

### Checkpoint

Repeated movement and distance sampling should not create a new permanently stored heap object merely to hold a coordinate or number.

Clear condition: Test 1, `Location uses values`, reports `PASS`.

## Milestone 3: Repair `Vehicle` and `Car` Lifetimes

### Tasks

1. Identify every resource owned by `Vehicle` and `Car`.
2. Remove duplicated ownership of the license plate.
3. Make the current location have one clear owner.
4. Ensure a location update cannot store the address of a local function parameter.
5. Decide whether `Car` should inherit from `Vehicle` or contain a `Vehicle`.
6. Check whether copying either class is safe. If not, prevent copying or implement correct copy/move behavior.

### Questions

- What happens to the initial location allocated in the `Car` constructor?
- What is the lifetime of the parameter passed to `setLocation`?
- Should movement be exposed through inheritance or composition?

### Checkpoint

A test that moves a car, changes its location, and reads it after the update must produce a valid location under sanitizers.

Clear condition: Test 2, `Vehicle location remains valid`, reports `PASS`,
and the sanitizer run reports no lifetime error.

## Milestone 4: Choose One Owner for Each Domain Object

This is the main structural redesign.

### Tasks

1. Choose the owner of all cars.
2. Choose the owner of all humans.
3. Choose the owner of all garages.
4. Choose the owner of all car parks.
5. Represent ownership with RAII containers.
6. Represent non-owning relationships separately.
7. Document the rule in comments or the lab notes.

### Smart Pointer Investigation

For each raw pointer, classify it before changing it:

```text
single owner       -> investigate std::unique_ptr
shared lifetime    -> investigate std::shared_ptr and std::weak_ptr
borrowed access    -> reference, raw pointer, or observer-style handle
simple data value  -> store the value directly
```

Do not choose a smart pointer because it makes a warning disappear. Choose it
because its ownership semantics match the relationship. In your ownership
table, add a column called `Pointer choice` and justify every remaining pointer.

### Constraints

- One object must have one owner.
- A non-owning pointer must never delete its target.
- A container of pointers must not be assumed to own the pointed-to objects automatically.
- Moving an object between locations must not create a duplicate object.

### Questions

- Should `Town` own the objects and other classes observe them?
- Can a garage and a car park both store a non-owning reference to the same car?
- What should happen when a car is removed from a garage or car park?
- How will a transferred object remain alive after leaving its current container?

### Checkpoint

For every `new` remaining in the program, you should be able to name its owner and the cleanup path.

The checkpoint is incomplete if the solution uses `shared_ptr` everywhere
without explaining why each object needs shared lifetime.

Clear condition: Test 4, `Ownership is explicit`, reports `PASS`, and the
ownership table identifies one owner for every remaining allocation.

## Milestone 5: Repair `Human` and `Garage` Relationships

### Tasks

1. Decide whether a human owns a garage or merely refers to one.
2. Prevent `addGarage` from silently losing the previous allocation.
3. Make car purchasing transfer or reference an existing car instead of creating duplicate identity.
4. Make listing vehicles a read-only operation unless ownership transfer is intended.
5. Remove dynamically created display-only vehicles.
6. Define what `clone` is expected to copy: name only, garage relationship, cars, or all state.

### Questions

- What does it mean for two humans to share a garage?
- Should cloning duplicate cars or only the human record?
- Who owns a car returned by `takeCar`?
- Does a listing function need to return objects at all?

### Checkpoint

A car with one license plate must not become two independent cars merely because a human purchases or lists it.

Clear condition: Tests 3 and 5, `Car has one identity` and `Garage transfers
without deleting`, both report `PASS`.

## Milestone 6: Repair `CarPark`

### Tasks

1. Remove the allocation that is immediately overwritten in `removeCar`.
2. Decide whether removing a car should return it, transfer it, or only update park state.
3. Ensure the current load matches the number of parked cars.
4. Record history using value types unless a pointer is necessary.
5. Make audit entries automatically managed.
6. Clarify the purpose of courtesy cars and ghost vehicles. Remove them if they are only test artifacts, or give them a real owner.
7. Make failure paths leave the park unchanged.
8. Revisit `parkVehicle` after deciding on the `Vehicle`/`Car` relationship.

### Questions

- What should happen if the car park is full?
- What should happen if the requested license plate is missing?
- Does an audit entry get created before or after a successful operation?
- Can a car be added to the same car park twice?

### Checkpoint

Test these cases:

- add one car,
- add a car to a full park,
- remove an existing car,
- remove a missing car,
- attempt to park the same car twice.

The load and stored objects must remain consistent after each case.

Clear condition: Test 6, `Car park keeps state consistent`, reports `PASS`.

## Milestone 7: Repair `Town` and `main`

### Tasks

1. Remove the final manual deletes of loop variables.
2. Make `Town` cleanup happen automatically.
3. Ensure objects stored in `Town` are still alive when the simulation uses them.
4. Remove duplicated or unreachable initialization.
5. Make the simulation limit an explicit parameter.
6. Ensure normal return from `main` reaches all destructors and tracker shutdown.
7. Pass a deterministic random seed during tests.

### Questions

- Why do the four deletes at the end of `main` not clean up the whole town?
- What pointers remain inside `Town` after those deletes?
- What happens to objects created during later rotations?
- Can the simulation be run for ten steps instead of ten thousand while debugging?

### Checkpoint

The process should end normally after a chosen number of rotations, with no dangling-pointer report from sanitizers.

Clear condition: Test 7, `Town cleans up automatically`, reports `PASS`, and
the sanitizer run reports no invalid lifetime operation.

## Milestone 8: Split the Monolithic File

Do this only after behavior and ownership are stable.

### Suggested boundaries

```text
Location.h / Location.cpp
Vehicle.h / Vehicle.cpp
Car.h / Car.cpp
Garage.h / Garage.cpp
Human.h / Human.cpp
CarPark.h / CarPark.cpp
Town.h / Town.cpp
main.cpp
```

### Tasks

1. Move one class at a time.
2. Add include guards or `#pragma once` to headers.
3. Keep implementation details private.
4. Update the Makefile source list.
5. Build after every moved class.
6. Do not use global variables to reconnect classes accidentally.

### Checkpoint

The project must build from a clean directory, not only from previously generated object files.

Clear condition: All seven checkpoint tests still report `PASS` after the
classes have been moved into separate files, and a clean build succeeds.

## Final Verification

Run all of the following:

```text
g++ -std=c++20 -Wall -Wextra -pedantic ...
```

Then, where available:

```text
AddressSanitizer
UndefinedBehaviorSanitizer
```

Verify:

- no compiler warnings related to the repaired code,
- no dangling-pointer reports,
- no invalid free reports,
- no duplicated ownership assumptions,
- the final ownership diagram matches the code.
- every owning pointer has a documented smart-pointer or RAII strategy.

## Student Submission

Submit:

1. The repaired source code.
2. The updated UML diagram.
3. The ownership table from Milestone 1.
4. A short explanation of the final ownership model.
5. Test results for normal execution and sanitizer execution.
6. A list of design decisions that were intentionally left unchanged.
7. The completed checkpoint test file and its test output.

## Reflection Questions

- Which pointer was hardest to classify as owning or non-owning, and why?
- Which bug could produce the most dangerous runtime behavior?
- Which change reduced the most manual cleanup code?
- Which behavior did you preserve even though the implementation changed?
- What would you redesign differently if the program grew to several thousand entities?
