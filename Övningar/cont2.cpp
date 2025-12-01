#include <concepts>
#include <ranges>
#include <algorithm>
#include <vector>
#include <iostream>
#include <list>
#include <string>
#include <iterator>

// Ett generiskt sorteringsinterface som endast accepterar containrar
// vars element uppfyller TotallyOrdered.
template <typename T>
concept Tordered = std::totally_ordered<T>;

// Tar en container-typ som är en range och vars element är helt ordnade.
template <Tordered Container>
void sort_in_place(Container &c)
{
    // Om containern är random access: använd effektiv in-place sortering
    if constexpr (std::ranges::random_access_range<Container>)
    {
        std::ranges::sort(c);
    }
    else
    {
        // Fallback: kopiera till en vector, sortera och skriv tillbaka.
        // Detta gör att vi kan sortera t.ex. std::list utan att kräva random access.
        using value_t = std::ranges::range_value_t<Container>;
        std::vector<value_t> tmp(std::begin(c), std::end(c));
        std::ranges::sort(tmp);
        auto it = std::begin(c);
        for (auto &v : tmp)
        {
            *it++ = v;
        }
    }
}

// Exempel på användning
int main()
{
    std::vector<int> v = {5, 1, 4, 3, 2};
    sort_in_place(v);
    for (int x : v)
        std::cout << x << ' ';
    std::cout << '\n';

    std::list<std::string> l = {"zebra", "apple", "mango"};
    sort_in_place(l);
    for (auto &s : l)
        std::cout << s << ' ';
    std::cout << '\n';

    // Följande skulle ge kompileringstidfel eftersom typen inte är helt ordnad:
    // struct NoOrder {};
    // std::vector<NoOrder> bad;
    // sort_in_place(bad); // <-- kompilerar inte: NoOrder saknar ordningsoperatorer

    return 0;
}