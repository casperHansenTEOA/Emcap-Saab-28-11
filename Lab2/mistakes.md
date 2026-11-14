# Mistakes in the game

This program is intentionally written as a beginner example. The mistakes below
are included for memory-management practice and should not be copied into a
real program.

## Intentional memory leaks

1. `playerName` is created with `new char[30]` and is never released with
   `delete[]`.
2. `wagonName` is created with `new char[20]` and is never released with
   `delete[]`.
3. `oldSupplies` is created with `new int[5]` and is never released with
   `delete[]`.
4. Every `CargoManifest` object creates a 250-by-1,000 integer matrix during a
  game turn. The integer payload is about 1 MB, plus a small array of row
  pointers. The allocations are written to and never released. A seven-turn
  game therefore leaks roughly 7 MB from cargo records.
5. Every `WeatherReport` object creates a 250-by-1,000 character matrix during
  a game turn. The character payload is about 250 KB, plus row pointers. The
  allocations are written to and never released.
6. `wagon` is created with `new Wagon` and is never released with `delete`.
  The game accesses it through `wagon->`, which demonstrates pointer member
  access but adds another leak.

The operating system will usually reclaim these allocations when the program
ends, but the program still leaks memory while it is running. The correct fix
would be to release every allocation, or better, use automatic variables and
standard containers in a less restricted program.

The per-turn matrices are especially bad because memory use grows with the
length of the game. The allocations are used as part of the cargo and weather
classes, so the mistake is hidden inside genuine game features.

Neither report class has a destructor. Copying either class would copy only the
row-pointer value, not the matrix contents, which could lead to shared storage,
double deletion after a future cleanup, or dangling pointers. The classes also
do not define copy or move operations.

## Other beginner mistakes

- The program still uses raw pointers for the player name, wagon name, old
  supplies, wagon, and per-turn reports instead of expressing ownership with
  RAII.
- The `Wagon` class uses public fields, so any part of the program can change
  food, water, health, or miles directly.
- The `Wagon` constructor assigns fields inside its body instead of using a
  constructor initializer list.
- It manually declares `printf` and `scanf` instead of including the proper
  standard headers. This was done to meet the exercise requirement, but it is
  poor normal practice.
- `scanf` only reads one word for the name and wagon name.
- Input is not checked. If the player types text when a number is expected,
  the game may behave incorrectly.
- The game asks for an action every turn, but it does not check whether the
  entered number was valid.
- The travel events are based on the day number, so they are predictable.
- The balance is very simple and the player can get negative food or water.
- The five values in `oldSupplies` are mostly unused.
- There is no separate function for displaying status or handling a turn, so
  `main` is longer than it should be.
- The game uses magic numbers such as `100`, `15`, and `25` instead of named
  constants.