// A very small Oregon Trail style game.
// This file intentionally does not include any header files.

extern "C" int printf(const char *format, ...);
extern "C" int scanf(const char *format, ...);

class Wagon
{
public:
    int food;
    int water;
    int health;
    int miles;

    Wagon()
    {
        food = 100;
        water = 100;
        health = 100;
        miles = 0;
    }

    void travelCarefully()
    {
        miles = miles + 15;
        food = food - 12;
        water = water - 15;
        printf("You travel carefully and find a good campsite.\n");
    }

    void travelFast()
    {
        miles = miles + 25;
        food = food - 20;
        water = water - 25;
        health = health - 8;
        printf("You travel fast, but somebody falls from the wagon.\n");
    }

    void rest()
    {
        food = food - 10;
        water = water - 10;
        health = health + 5;
        if (health > 100)
        {
            health = 100;
        }
        printf("Everybody rests. The wagon is a little stronger.\n");
    }
};

class CargoManifest
{
public:
    int **drawing;
    int rows;
    int columns;

    CargoManifest(int food, int water, int day)
    {
        rows = 250;
        columns = 1000;
        drawing = new int *[rows];

        for (int row = 0; row < rows; row++)
        {
            drawing[row] = new int[columns];
            for (int column = 0; column < columns; column++)
            {
                drawing[row][column] = food + water + day + row + column;
            }
        }
    }

    int spoiledFood(int day)
    {
        return drawing[day % rows][day % columns] % 4;
    }
};

class WeatherReport
{
public:
    char **drawing;
    int rows;
    int columns;

    WeatherReport(int day)
    {
        rows = 250;
        columns = 1000;
        drawing = new char *[rows];

        for (int row = 0; row < rows; row++)
        {
            drawing[row] = new char[columns];
            for (int column = 0; column < columns; column++)
            {
                drawing[row][column] = (row + column + day) % 3 == 0 ? 'r' : 's';
            }
        }
    }

    char weatherForDay(int day)
    {
        return drawing[day % rows][day % columns];
    }
};

int main()
{
    char *playerName = new char[30];
    char *wagonName = new char[20];
    int *oldSupplies = new int[5];
    Wagon *wagon = new Wagon;

    oldSupplies[0] = 4;
    oldSupplies[1] = 8;
    oldSupplies[2] = 15;
    oldSupplies[3] = 2;
    oldSupplies[4] = 1;

    printf("======================================\n");
    printf("       THE LONG ROAD WEST\n");
    printf("======================================\n");
    printf("What is the name of your traveler? ");
    scanf("%29s", playerName);
    printf("What should your wagon be called? ");
    scanf("%19s", wagonName);

    printf("\nWelcome, %s. Your wagon is called %s.\n", playerName, wagonName);
    printf("You must travel 100 miles before winter arrives.\n\n");

    while (wagon->miles < 100 && wagon->health > 0)
    {
        int choice;
        int day = (wagon->miles / 10) + 1;

        printf("Day %d: You have traveled %d miles.\n", day, wagon->miles);
        printf("Food: %d  Water: %d  Health: %d\n", wagon->food, wagon->water, wagon->health);

        CargoManifest *cargoManifest = new CargoManifest(wagon->food, wagon->water, day);
        WeatherReport *weatherReport = new WeatherReport(day);

        printf("The day's cargo manifest is ready.\n");
        printf("1. Travel carefully\n");
        printf("2. Travel fast\n");
        printf("3. Rest for a day\n");
        printf("Choose an action: ");
        scanf("%d", &choice);

        int spoiledFood = cargoManifest->spoiledFood(day);
        wagon->food = wagon->food - spoiledFood;
        if (spoiledFood > 0)
        {
            printf("The cargo report finds %d spoiled food units.\n", spoiledFood);
        }

        if (weatherReport->weatherForDay(day) == 'r')
        {
            printf("Rain makes the trail difficult today.\n");
            wagon->health = wagon->health - 2;
        }

        if (choice == 1)
        {
            wagon->travelCarefully();
        }
        else if (choice == 2)
        {
            wagon->travelFast();
        }
        else if (choice == 3)
        {
            wagon->rest();
        }
        else
        {
            printf("You did not choose a real option, so the wagon stays still.\n");
            wagon->food = wagon->food - 5;
            wagon->water = wagon->water - 5;
        }

        if (day == 3)
        {
            printf("A river blocks the road. You lose extra food crossing it.\n");
            wagon->food = wagon->food - 15;
        }

        if (day == 5)
        {
            printf("A wheel breaks. You lose health while repairing it.\n");
            wagon->health = wagon->health - 15;
        }

        if (wagon->food <= 0)
        {
            printf("You have no food left.\n");
            wagon->health = wagon->health - 20;
        }

        if (wagon->water <= 0)
        {
            printf("You have no water left.\n");
            wagon->health = wagon->health - 25;
        }

        printf("\n");
    }

    if (wagon->miles >= 100 && wagon->health > 0)
    {
        printf("You made it to the west, %s! Your journey is over.\n", playerName);
    }
    else
    {
        printf("Your journey is over, but you did not make it.\n");
    }

    printf("Final food: %d, final water: %d, final health: %d\n", wagon->food, wagon->water, wagon->health);
    printf("The old supplies counted %d items.\n", oldSupplies[0]);

    return 0;
}
