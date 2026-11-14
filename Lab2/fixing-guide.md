# Lab 2: Student Repair Guide

## Goal

Improve the game so that it no longer leaks memory and has a clearer modern C++
design. Work in small steps and compile after each step. Do not rewrite the
whole program at once.

The course topics that are useful here are pointers and references, classes,
containers, RAII, smart pointers, exception safety, concepts, ranges, and
views.

## Step 1: Map the ownership model

Inspect the program as an ownership graph rather than as a list of individual
`delete` statements. Identify the lifetime of the wagon, each report, each row
allocation, and each name buffer.

For every resource, record:

- its owner,
- its lifetime,
- whether ownership can be copied or moved,
- its cleanup mechanism,
- and what happens if construction fails halfway through.

## Step 2: Remove accidental heap state

Search for every `new` expression. For each one, record:

- What type is allocated?
- Is it one object or an array?
- Who should own it?
- Where should it be released?
- What happens if an input operation or another operation fails?


## Step 3: Remove unnecessary pointers

The wagon's food, water, health, and miles do not need to be allocated
separately on the heap. They belong to the wagon object.

Hints:

- Keep ordinary values as ordinary fields.
- Let the `Wagon` class change its own state through methods.
- Consider moving repeated action code into small member functions.
- Avoid making every field public once the basic version works.

At this point, the game should behave the same as before, but it should use
fewer allocations.

## Step 3: Repair the per-turn classes

`CargoManifest` and `WeatherReport` allocate a matrix in their constructors.
They therefore need a clear ownership policy.

Answer these questions before editing:

1. Should a manifest own its matrix?
2. What should happen when a manifest object is destroyed?
3. Is a hand-written matrix really needed, or would a standard container be
   clearer?

You may first implement the straightforward manual fix using a destructor. Make
sure you release every row and then the array of row pointers. Treat this as a
diagnostic step, not necessarily the final design.
.

## Step 4: Replace manual ownership with RAII

After the manual destructor version works, improve the design using RAII.
Possible directions include:

- a standard container for one contiguous matrix,
- a standard container for rows,
- or a smart pointer with a suitable ownership model.

The best design is the one where cleanup happens automatically when the object
leaves scope. The game loop should not need to remember cleanup instructions.

Do not use a smart pointer just to hide the same ownership confusion. Explain
what the pointer owns and why its deleter matches the allocation.

## Step 5: Improve the class interface

The game currently exposes much of the wagon state directly. Improve it in
small increments:

- make state private where practical,
- add simple methods for reading status,
- keep action methods responsible for changing wagon state,
- replace repeated numeric literals with named constants.

Keep the interface small enough that the game loop does not know how a matrix
is stored. Return a read-only view or a calculated value instead of exposing
the owning pointer.

## Design question: Should there be a Player class?

The traveler currently exists mainly as a character buffer and the game loop
handles the player's decisions. Decide whether introducing a `Player` class
would improve the design or merely move code around.

Consider:

- Should `Player` own the traveler's name, or should another object own it?
- Should it only store identity, or should it also choose actions and track
   decisions?
- Should `Player` own the `Wagon`, refer to it, or be independent from it?
- Which operations belong to `Player`, and which belong to `Wagon`?
- Would a `Player` class make testing and future features easier?



## Step 6: Add a C++20 concept

The cargo and weather classes have similar responsibilities: they create a
report and provide a value for a day. Introduce a small generic helper only if
you can state the required interface clearly.

Hints:

- Define a concept that checks whether a report can provide the value required
   by the game.
- Constrain a report-processing function with that concept.
- Make the compiler reject a type that has the wrong return type or missing
   member function.
- Keep the concept about behavior, not about a particular class name or data
   member.

Do not use concepts merely to decorate a non-generic function. The exercise is
to demonstrate why the constraint improves the error message at the generic
boundary.


## Step 7: Separate responsibilities

`main` currently handles input, display, allocation, weather, cargo, events,
and the complete journey.

Move one responsibility at a time into small functions or classes. A useful
order is:

1. Display the wagon status.
2. Read the player's action.
3. Create and query the day's reports.
4. Apply weather, cargo, and travel events.
5. Decide whether the journey is over.

Keep the game rules unchanged while moving code. This makes regressions easier
to find.

