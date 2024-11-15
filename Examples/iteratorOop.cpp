#include <iostream>

#include <vector>
#include <list>


template <typename T>
class Container {
public:
    Container(T& container) {
        this->container = container;
    }   

    void printElements()  {
        typename T:: iterator begin = container.begin();
        typename T:: iterator end = container.end();
        while (begin != end) {
            std::cout << *begin << " ";
            begin++;
        }
    }

private:
    T container;
};

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::list<std::string> lst = {"Hello", "World"};

    Container<std::vector<int>> vecContainer(vec);
    Container<std::list<std::string>> listContainer(lst);

    vecContainer.printElements();
    listContainer.printElements();

    return 0;
}
