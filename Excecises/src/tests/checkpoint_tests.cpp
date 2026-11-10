// Student checkpoint test scaffold.
// These tests are intentionally incomplete. Implement one checkpoint at a time.
// After the classes are split into headers, include the project headers here.

#include <iostream>
#include <cmath>
#include <type_traits>
#include <string>
#include <vector>

#define TOWN_SIM_NO_MAIN
#include "../main.cpp"

namespace checkpoint_tests
{
    struct TestCase
    {
        std::string name;
        bool passed;
    };

    template <typename Result>
    bool has_expected_location(Result result)
    {
        if constexpr (std::is_pointer_v<Result>)
        {
            delete result;
            return false;
        }
        else
        {
            return result.x == 1.0 && result.y == 7.0;
        }
    }

    // Test 1 - Milestone 2: Remove Unnecessary Heap Allocation
    TestCase location_uses_values()
    {
        Location first{2.0, 3.0};
        const Location second{-1.0, 4.0};
        auto result = first.add(first, second);

        return {"Test 1 [Milestone 2] Location uses values",
                has_expected_location(result)};
    }

    // Test 2 - Milestone 3: Repair Vehicle and Car Lifetimes
    TestCase vehicle_location_remains_valid()
    {
        Location initial{0.0, 0.0};
        Vehicle vehicle{"ABC123", initial};
        vehicle.setLocation(Location{4.0, 5.0});

        const Location location = vehicle.getLocation();
        return {"Test 2 [Milestone 3] Vehicle location remains valid",
                location.x == 4.0 && location.y == 5.0};
    }

    // Test 3 - Milestone 5: Repair Human and Garage Relationships
    TestCase car_has_one_identity()
    {
        Car car{"ABC123"};
        Garage garage;
        garage.addCar(&car);
        Car *retrieved = garage.takeCar("ABC123");

        return {"Test 3 [Milestone 5] Car has one identity",
                retrieved == &car && car.getLicensePlate() == "ABC123"};
    }

    // Test 4 - Milestone 4: Choose One Owner for Each Domain Object
    TestCase ownership_is_explicit()
    {
        Car car{"ABC123"};
        Garage garage;
        garage.addCar(&car);

        {
            Town town;
            town.addCar(&car);
            town.addGarage(&garage);
        }

        return {"Test 4 [Milestone 4] Ownership is explicit",
                car.getLicensePlate() == "ABC123"};
    }

    // Test 5 - Milestone 5: Repair Human and Garage Relationships
    TestCase garage_transfers_without_deleting()
    {
        Car car{"ABC123"};
        Garage garage;
        garage.addCar(&car);
        Car *retrieved = garage.takeCar("ABC123");

        return {"Test 5 [Milestone 5] Garage transfers without deleting",
                retrieved == &car && car.getLicensePlate() == "ABC123"};
    }

    // Test 6 - Milestone 6: Repair CarPark
    TestCase car_park_keeps_state_consistent()
    {
        Car first{"ABC123"};
        Car second{"XYZ789"};
        CarPark carPark{Location{0.0, 0.0}, 1};

        const bool firstAdded = carPark.addCar(&first);
        const bool secondRejected = !carPark.addCar(&second);
        const bool loadAfterAdd = carPark.getCurrentLoad() == 1;
        const bool removed = carPark.removeCar("ABC123");
        const bool loadAfterRemove = carPark.getCurrentLoad() == 0;
        const bool missingRejected = !carPark.removeCar("MISSING");

        return {"Test 6 [Milestone 6] Car park keeps state consistent",
                firstAdded && secondRejected && loadAfterAdd && removed &&
                    loadAfterRemove && missingRejected};
    }

    // Test 7 - Milestone 7: Repair Town and main
    TestCase town_cleans_up_automatically()
    {
        {
            Town town;
            town.run(0);
        }

        return {"Test 7 [Milestone 7] Town cleans up automatically", true};
    }

    std::vector<TestCase> all()
    {
        return {
            location_uses_values(),
            vehicle_location_remains_valid(),
            car_has_one_identity(),
            ownership_is_explicit(),
            garage_transfers_without_deleting(),
            car_park_keeps_state_consistent(),
            town_cleans_up_automatically(),
        };
    }
}

int main()
{
    const auto tests = checkpoint_tests::all();
    std::size_t failed = 0;

    for (const auto &test : tests)
    {
        if (test.passed)
        {
            std::cout << "PASS: " << test.name << '\n';
        }
        else
        {
            std::cout << "FAIL: " << test.name << '\n';
            ++failed;
        }
    }

    std::cout << "Checkpoint tests: " << tests.size()
              << ", failed: " << failed << '\n';
    return failed == 0 ? 0 : 1;
}
