#include <vector>
#include <algorithm>
#include <iostream>

int main()
{
    std::vector<double> celsius = {0, 10, 20, 30, 100};
    std::vector<double> fahrenheit(celsius.size());

    std::transform(celsius.begin(), celsius.end(),
                   fahrenheit.begin(),
                   [](double c)
                   { return c * 9.0 / 5.0 + 32; });

    for (double f : fahrenheit)
        std::cout << f << " ";
    std::cout << "\n";
}