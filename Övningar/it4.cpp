#include <iostream>
#include <vector>
#include <utility>

template <typename It1, typename It2>
class ZipIterator
{
    It1 it1;
    It2 it2;

public:
    // Enkel forward iterator
    using iterator_category = std::forward_iterator_tag;

    ZipIterator(It1 i1, It2 i2) : it1(i1), it2(i2) {}

    ZipIterator &operator++()
    {
        ++it1;
        ++it2;
        return *this;
    }

    ZipIterator operator++(int)
    {
        ZipIterator tmp(*this);
        ++(*this);
        return tmp;
    }

    // Returnera par av referenser
    auto operator*() const
    {
        return std::pair<decltype(*it1), decltype(*it2)>(*it1, *it2);
    }

    bool operator==(const ZipIterator &other) const
    {
        // Stoppa när någon av iteratorerna når sitt end
        return it1 == other.it1 || it2 == other.it2;
    }

    bool operator!=(const ZipIterator &other) const
    {
        return !(*this == other);
    }
};

template <typename C1, typename C2>
class ZipRange
{
    C1 &c1;
    C2 &c2;

public:
    ZipRange(C1 &a, C2 &b) : c1(a), c2(b) {}

    auto begin()
    {
        return ZipIterator(c1.begin(), c2.begin());
    }

    auto end()
    {
        return ZipIterator(c1.end(), c2.end());
    }
};

template <typename C1, typename C2>
ZipRange<C1, C2> zip(C1 &c1, C2 &c2)
{
    return ZipRange<C1, C2>(c1, c2);
}

int main()
{
    std::vector<int> v1 = {1, 2, 3};
    std::vector<char> v2 = {'a', 'b', 'c'};

    for (auto [num, ch] : zip(v1, v2))
    {
        std::cout << num << " : " << ch << '\n';
    }
}